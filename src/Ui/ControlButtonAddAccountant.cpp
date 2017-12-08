#include "ControlButtonAddAccountant.h"
#include "../System/EntityContainer.h"

ControlButtonAddAccountant::ControlButtonAddAccountant(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddAccountant);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddAccountant::width);
    setHeight(ControlButtonAddAccountant::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddAccountant::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedAccountant &&
                          System::cash >= attachedAccountant->getCost() &&
                          !attachedAccountant->isBelowGround() &&
                          (attachedAccountant->isCrossingOffices() || attachedAccountant->isOnTheGround(30));

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

    if (leftClicked() && !attachedAccountant && !System::spawningUnit) {
        attachedAccountant = new Accountant({System::g_x, System::g_y});
    }

    if (rightClickedOutside() && attachedAccountant) {
        EntityContainer::remove(attachedAccountant);

        System::spawningUnit = false;
        attachedAccountant = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedAccountant->setNormal();
        attachedAccountant->setDirection(Direction::Down);
        attachedAccountant->spawn();

        System::spawningUnit = false;

        attachedAccountant = nullptr;
    }

    if (attachedAccountant) {
        System::selectionCooldown.restart();
        state = S_Button_Pressed;
        System::spawningUnit = true;
        attachedAccountant->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedAccountant->setInvalid();

            if(leftClickedOutside() && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
                liveClock.restart();
                auto error = new TextEntity(System::c_red, 20);

                error->setSpeed(100);
                error->setLiveTimeSeconds(2);
                error->setWorldCoordinates({attachedAccountant->getWorldCoordinates().x, attachedAccountant->getWorldCoordinates().y + attachedAccountant->getHeight() / 2 + 10});

                if (attachedAccountant->isBelowGround() || attachedAccountant->isCrossingOffices() || !attachedAccountant->isOnTheGround(30)) {
                    error->setString(ResourceLoader::getTranslation("error.invalid_position"));
                }

                if (System::cash < attachedAccountant->getCost()) {
                    error->setString(
                            ResourceLoader::getTranslation("error.no_cash") + ", " +
                            ResourceLoader::getTranslation("error.hint.cash") + " " +
                            System::f_to_string(attachedAccountant->getCost() - System::cash, 0) + "$"
                    );
                }
            }
        } else {
            attachedAccountant->setTransparent();
        }
    }

    BasicUi::update();
}
