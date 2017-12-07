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
                          attachedCabin->hasElevatorShaftTopAbove();

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

            if(leftClickedOutside() && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
                liveClock.restart();
                auto error = new TextEntity(System::c_red, 20);

                error->setSpeed(100);
                error->setLiveTimeSeconds(2);
                error->setWorldCoordinates({attachedCabin->getWorldCoordinates().x, attachedCabin->getWorldCoordinates().y + attachedCabin->getHeight() / 2 + 10});

                if (attachedCabin && (!attachedCabin->isInsideShaftBoundaries() || !attachedCabin->hasElevatorShaftTopAbove())) {
                    error->setString(
                            ResourceLoader::getTranslation("error.invalid_position") + ", " +
                            ResourceLoader::getTranslation("error.hint.cabin")
                    );
                }

                if (System::cash < attachedCabin->getCost()) {
                    error->setString(
                            ResourceLoader::getTranslation("error.no_cash") + ", " +
                            ResourceLoader::getTranslation("error.hint.cash") + " " +
                            System::f_to_string(attachedCabin->getCost() - System::cash, 0) + "$"
                    );
                }
            }
        } else {
            attachedCabin->setTransparent();
        }
    }

    BasicUi::update();
}




