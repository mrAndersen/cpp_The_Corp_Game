#include <climits>
#include <cmath>
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "..\System\System.h"
#include "ControlButtonAddElevatorShaftTop.h"

ControlButtonAddElevatorShaftTop::ControlButtonAddElevatorShaftTop(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddElevatorShaftTop);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddElevatorShaftTop::width);
    setHeight(ControlButtonAddElevatorShaftTop::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    setVisible(false);
    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddElevatorShaftTop::update() {
    if (!visible) {
        return;
    }

    state = S_Button_Pressed;

    bool spawnCondition = attachedShaft &&
                          System::cash >= attachedShaft->getCost() &&
                          !attachedShaft->isBelowGround() &&
                          !attachedShaft->intersectsWithObjects() &&
                          attachedShaft->hasMiddleShaftOnTheBottom();

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

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

        float x = roundf(global.x - ((int) global.x % System::gridSize) + width / 2);
        float y = roundf(global.y - ((int) global.y % System::gridSize) + System::gridSize / 2);

        x = System::roundToMultiple(x);
        y = System::roundToMultiple(y);

        attachedShaft->setWorldCoordinates({x, y});

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

    BasicUi::update();
}














