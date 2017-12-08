#include <SFML/System.hpp>
#include "ControlButtonAddClerk.h"
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"
#include "..\System\ViewHandler.h"
#include "..\System\System.h"

ControlButtonAddClerk::ControlButtonAddClerk(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddClerk);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddClerk::width);
    setHeight(ControlButtonAddClerk::height);

    addAnimation(S_Button_Normal,
                 Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed,
                 Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddClerk::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedClerk &&
                          System::cash >= attachedClerk->getCost() &&
                          !attachedClerk->isBelowGround() &&
                          (attachedClerk->isCrossingOffices() || attachedClerk->isOnTheGround(30));

    if (mouseIn()) {
        System::selectionCooldown.restart();
    }

    if (leftClicked() && !attachedClerk && !System::spawningUnit) {
        attachedClerk = new Clerk({System::g_x, System::g_y});
    }

    if (rightClickedOutside() && attachedClerk) {
        EntityContainer::remove(attachedClerk);

        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedClerk->setNormal();
        attachedClerk->setDirection(Direction::Down);
        attachedClerk->spawn();

        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    if (attachedClerk) {
        System::selectionCooldown.restart();
        state = S_Button_Pressed;
        System::spawningUnit = true;
        attachedClerk->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedClerk->setInvalid();

            if (leftClickedOutside() && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
                liveClock.restart();
                auto error = new TextEntity(System::c_red, 20);

                error->setSpeed(100);
                error->setLiveTimeSeconds(2);
                error->setWorldCoordinates({attachedClerk->getWorldCoordinates().x, attachedClerk->getWorldCoordinates().y + attachedClerk->getHeight() / 2 + 10});

                //placement error
                if (attachedClerk->isBelowGround() || attachedClerk->isCrossingOffices() || !attachedClerk->isOnTheGround(30)) {
                    error->setString(ResourceLoader::getTranslation("error.invalid_position"));
                }

                if (System::cash < attachedClerk->getCost()) {
                    error->setString(
                            ResourceLoader::getTranslation("error.no_cash") + ", " +
                            ResourceLoader::getTranslation("error.hint.cash") + " " +
                            System::f_to_string(attachedClerk->getCost() - System::cash, 0)
                            + "$"
                    );
                }
            }
        } else {
            attachedClerk->setTransparent();
        }
    }

    BasicUi::update();
}
