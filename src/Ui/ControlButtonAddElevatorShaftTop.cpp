#include <climits>
#include <cmath>
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"
#include "System/System.h"
#include "ControlButtonAddElevatorShaftTop.h"

ControlButtonAddElevatorShaftTop::ControlButtonAddElevatorShaftTop() {
    setEType(E_ButtonAddElevatorShaftTop);
    setDrawOrder(INT_MAX);

    setWidth(142);
    setHeight(47);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    EntityContainer::add(this);
}

void ControlButtonAddElevatorShaftTop::updateLogic() {
    bool spawnCondition = attachedShaft &&
                          System::cash >= attachedShaft->getCost() &&
                          !attachedShaft->isBelowGround() &&
                          !attachedShaft->intersectsWithObjects() &&
                          attachedShaft->hasMiddleShaftOnTheBottom();

    if (leftClicked() && !attachedShaft && !System::spawningUnit) {
        attachedShaft = new ElevatorShaftTop(sf::Vector2f(System::g_x, System::g_y));
        attachedShaft->setTransparent();
    }

    if (rightClickedOutside() && attachedShaft) {
        EntityContainer::remove(attachedShaft);

        System::spawningUnit = false;
        attachedShaft = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedShaft->setNormal();
        attachedShaft->spawn();

        System::spawningUnit = false;
        attachedShaft = nullptr;
    }

    if (attachedShaft) {
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();

        float normalizedX = global.x - ((int) global.x % System::gridSize) + System::gridSize / 2;
        float normalizedY = global.y - ((int) global.y % System::gridSize) + System::gridSize / 2;

        attachedShaft->setWorldCoordinates(sf::Vector2f(normalizedX, normalizedY));

        if (!spawnCondition) {
            attachedShaft->setInvalid();

            //placement error
            if (
                    attachedShaft &&
                    (attachedShaft->intersectsWithObjects() || attachedShaft->getNeighborOffices().empty() ||
                     !attachedShaft->isOnTheGround())) {
                attachedShaft->getErrorString().setString(
                        "Invalid placement position\nmust be placed on top of the shaft");
            }

            //cash error
            if (System::cash < attachedShaft->getCost()) {
                attachedShaft
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(std::abs(System::cash - attachedShaft->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedShaft->setTransparent();
        }
    }
}














