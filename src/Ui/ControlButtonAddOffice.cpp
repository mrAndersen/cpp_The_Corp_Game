#include <climits>
#include <cmath>
#include <iostream>
#include "ControlButtonAddOffice.h"
#include "..\System\EntityContainer.h"
#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "..\Office\OfficeClerk.h"
#include "../System/ResourceLoader.h"

ControlButtonAddOffice::ControlButtonAddOffice(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddOffice);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddOffice::width);
    setHeight(ControlButtonAddOffice::height);

    addAnimation(S_Button_Normal,
                 Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed,
                 Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddOffice::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedOffice &&
                          System::cash >= attachedOffice->getCost() &&
                          !attachedOffice->isBelowGround() &&
                          !attachedOffice->intersectsWithObjects() &&
                          (!attachedOffice->getNeighborOffices().empty() || attachedOffice->isOnTheGround());

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

    if (leftClicked() && !attachedOffice && !System::spawningUnit) {
        attachedOffice = new OfficeClerk(sf::Vector2f(System::g_x, System::g_y));
        attachedOffice->setTransparent();
    }

    if (rightClickedOutside() && attachedOffice) {
        EntityContainer::remove(attachedOffice);

        System::spawningUnit = false;
        attachedOffice = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedOffice->setNormal();
        attachedOffice->spawn();

        System::spawningUnit = false;
        attachedOffice = nullptr;
    }

    if (attachedOffice) {
        System::selectionCooldown.restart();
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();
        state = S_Button_Pressed;

        float x = roundf(global.x - ((int) global.x % System::gridSize) + System::gridSize);
        float y = roundf(global.y - ((int) global.y % System::gridSize) + System::gridSize / 2);

        x = System::roundToMultiple(x);
        y = System::roundToMultiple(y);

        attachedOffice->setWorldCoordinates({x, y});

        if (!spawnCondition) {
            attachedOffice->setInvalid();

            if(leftClickedOutside() && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
                liveClock.restart();
                auto error = new TextEntity(System::c_red, 20);

                error->setSpeed(100);
                error->setLiveTimeSeconds(2);
                error->setWorldCoordinates({attachedOffice->getWorldCoordinates().x,
                                            attachedOffice->getWorldCoordinates().y +
                                                    attachedOffice->getHeight() / 2 + 10});

                if (attachedOffice && (attachedOffice->intersectsWithObjects() || attachedOffice->getNeighborOffices().empty() || !attachedOffice->isOnTheGround())) {
                    error->setString(ResourceLoader::getTranslation("error.invalid_position"));
                }

                if (System::cash < attachedOffice->getCost()) {
                    error->setString(
                            ResourceLoader::getTranslation("error.no_cash") + ", " +
                            ResourceLoader::getTranslation("error.hint.cash") + " " +
                            System::f_to_string(attachedOffice->getCost() - System::cash, 0) + "$"
                    );
                }
            }
        } else {
            attachedOffice->setTransparent();
        }
    }

    BasicUi::update();
}
