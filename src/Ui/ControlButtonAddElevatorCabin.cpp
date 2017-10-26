#include <climits>
#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <System/System.h>
#include <Text/TextEntity.h>
#include <cmath>
#include "ControlButtonAddElevatorCabin.h"

ControlButtonAddElevatorCabin::ControlButtonAddElevatorCabin() {
    setEType(E_ButtonAddElevatorShaftMiddle);
    setDrawOrder(INT_MAX);

    setWidth(142);
    setHeight(47);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    EntityContainer::add(this);

}

void ControlButtonAddElevatorCabin::updateLogic() {
    bool spawnCondition = attachedCabin &&
                          System::cash >= attachedCabin->getCost() &&
                          attachedCabin->isInsideShaftBoundaries();

    if (leftClicked() && !attachedCabin && !System::spawningUnit) {
        attachedCabin = new ElevatorCabin({System::g_x, System::g_y});
        attachedCabin->setTransparent();
    }

    if (rightClickedOutside() && attachedCabin) {
        EntityContainer::remove(attachedCabin);

        System::spawningUnit = false;
        attachedCabin = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedCabin->setNormal();
        attachedCabin->spawn();

        System::spawningUnit = false;
        attachedCabin = nullptr;
    }

    if (attachedCabin) {
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();

        float normalizedX = global.x - ((int) global.x % System::gridSize) + System::gridSize / 2;
        float normalizedY = global.y - ((int) global.y % System::gridSize) + System::gridSize / 2;

        attachedCabin->setWorldCoordinates(sf::Vector2f(normalizedX, normalizedY));

        if (!spawnCondition) {
            attachedCabin->setInvalid();

            //placement error
            if (attachedCabin && !attachedCabin->isInsideShaftBoundaries()) {
                attachedCabin->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedCabin->getCost()) {
                attachedCabin
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(std::abs(System::cash - attachedCabin->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedCabin->setTransparent();
        }
    }
}




