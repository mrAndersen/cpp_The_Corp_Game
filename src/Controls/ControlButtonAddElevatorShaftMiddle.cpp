#include <climits>
#include <cmath>
#include "ControlButtonAddElevatorShaftMiddle.h"
#include "System/ViewHandler.h"
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"
#include "System/System.h"
#include "Text/TextEntity.h"

ControlButtonAddElevatorShaftMiddle::ControlButtonAddElevatorShaftMiddle() {
    setName("button.add.elevator.shaft.middle");
    setDrawOrder(INT_MAX);

    setWidth(142);
    setHeight(47);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ButtonAddElevatorShaftMiddle)));
    createAnimationFrames();

    EntityContainer::add(this);
}

void ControlButtonAddElevatorShaftMiddle::updateLogic() {
    bool spawnCondition = attachedShaft &&
                          System::cash >= attachedShaft->getCost() &&
                          !attachedShaft->isBelowGround() &&
                          !attachedShaft->intersectsWithObjects() &&
                          (attachedShaft->isOnTheGround() || attachedShaft->hasMiddleShaftOnTheBottom());

    if (leftClicked() && !attachedShaft && !System::spawningUnit) {
        attachedShaft = new ElevatorShaftMiddle(sf::Vector2f(System::g_x, System::g_y));
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

        auto *spent = new TextEntity(System::c_red, 30);
        auto position = attachedShaft->getWorldCoordinates();
        position.y += attachedShaft->getHeight() / 2;

        spent->setLiveTimeSeconds(4);
        spent->setWorldCoordinates(position);
        spent->setString("-" + System::f_to_string(attachedShaft->getCost()) + "$");

//        //change to top shaft
//        if(!attachedShaft->isOnTheGround()){
//
//            auto topShaftPosition = attachedShaft->getWorldCoordinates();
//            topShaftPosition.y += attachedShaft->getHeight() / 2;
//
//            auto topShaft = new ElevatorShaft(topShaftPosition);
//            topShaft->setType(ElevatorShafts::EL_Top);
//
//            attachedShaft->setTopShaft(topShaft);
//        }

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
            if (attachedShaft &&
                (attachedShaft->intersectsWithObjects() || attachedShaft->getNeighborOffices().empty() ||
                 !attachedShaft->isOnTheGround())) {
                attachedShaft->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedShaft->getCost()) {
                attachedShaft
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(fabs(System::cash - attachedShaft->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedShaft->setTransparent();
        }
    }
}
