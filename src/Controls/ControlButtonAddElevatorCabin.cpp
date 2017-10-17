#include <climits>
#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <System/System.h>
#include <Text/TextEntity.h>
#include <cmath>
#include "ControlButtonAddElevatorCabin.h"

ControlButtonAddElevatorCabin::ControlButtonAddElevatorCabin() {
    setName("button.add.elevator.cabin");
    setDrawOrder(INT_MAX);

    setWidth(142);
    setHeight(47);

    setTotalFrames(1);
    addTexture(ResourceLoader::getTexture(Entities::E_ButtonAddElevatorShaftMiddle));
    createAnimationFrames();

    EntityContainer::add(this);

}

void ControlButtonAddElevatorCabin::updateLogic() {
    bool spawnCondition = attachedCabin &&
                          System::cash >= attachedCabin->getCost() &&
                          attachedCabin->isInsideShaftBoundaries();

    if (leftClicked() && !attachedCabin && !System::spawningUnit) {
        attachedCabin = new ElevatorCabin(sf::Vector2f(System::g_x, System::g_y));
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

        auto *spent = new TextEntity(System::c_red, 30);
        auto position = attachedCabin->getWorldCoordinates();
        position.y += attachedCabin->getHeight() / 2;

        spent->setLiveTimeSeconds(4);
        spent->setWorldCoordinates(position);
        spent->setString("-" + System::f_to_string(attachedCabin->getCost()) + "$");

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
                                System::f_to_string(fabs(System::cash - attachedCabin->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedCabin->setTransparent();
        }
    }
}




