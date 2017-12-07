#include <climits>
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "..\System\System.h"
#include <cmath>
#include "ControlButtonAddElevatorCabin.h"

ControlButtonAddElevatorCabin::ControlButtonAddElevatorCabin(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddElevatorCabin);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddElevatorCabin::width);
    setHeight(ControlButtonAddElevatorCabin::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    setVisible(false);
    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddElevatorCabin::update() {
    if (!visible) {
        return;
    }

    state = S_Button_Normal;

    bool spawnCondition = attachedCabin &&
                          System::cash >= attachedCabin->getCost() &&
                          attachedCabin->isInsideShaftBoundaries() &&
                          attachedCabin->hasElevatorShaftTopAbove()
    ;

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

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
        System::selectionCooldown.restart();
        state = S_Button_Pressed;
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();

        float x = roundf(global.x - ((int) global.x % System::gridSize) + width / 2);
        float y = roundf(global.y - ((int) global.y % System::gridSize) + System::gridSize / 2);

        x = System::roundToMultiple(x);
        y = System::roundToMultiple(y);

        attachedCabin->setWorldCoordinates({x, y});

        if (!spawnCondition) {
            attachedCabin->setInvalid();

            //placement error
            if (attachedCabin && !attachedCabin->isInsideShaftBoundaries()) {
//                attachedCabin->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedCabin->getCost()) {
//                attachedCabin
//                        ->getErrorString()
//                        .setString(
//                                "Not enough cash, need " +
//                                System::f_to_string(std::abs(System::cash - attachedCabin->getCost())) +
//                                "$ more"
//                        );
            }
        } else {
            attachedCabin->setTransparent();
        }
    }

    BasicUi::update();
}




