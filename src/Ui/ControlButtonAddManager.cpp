#include "ControlButtonAddManager.h"

ControlButtonAddManager::ControlButtonAddManager(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddManager);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddManager::width);
    setHeight(ControlButtonAddManager::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddManager::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedManager &&
                          System::cash >= attachedManager->getCost() &&
                          !attachedManager->isBelowGround() &&
                          (attachedManager->isCrossingOffices() || attachedManager->isOnTheGround(30))
    ;

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

    if (leftClicked() && !attachedManager && !System::spawningUnit) {
        attachedManager = new Manager({System::g_x, System::g_y});
    }

    if (rightClickedOutside() && attachedManager) {
        EntityContainer::remove(attachedManager);

        System::spawningUnit = false;
        attachedManager = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedManager->setNormal();
        attachedManager->setDirection(Direction::Down);
        attachedManager->spawn();

        System::spawningUnit = false;
        attachedManager = nullptr;
    }

    if (attachedManager) {
        System::selectionCooldown.restart();
        state = S_Button_Pressed;
        System::spawningUnit = true;
        attachedManager->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedManager->setInvalid();

            if(leftClickedOutside() && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
                liveClock.restart();
                auto error = new TextEntity(System::c_red, 20);

                error->setSpeed(100);
                error->setLiveTimeSeconds(2);
                error->setWorldCoordinates({attachedManager->getWorldCoordinates().x, attachedManager->getWorldCoordinates().y + attachedManager->getHeight() / 2 + 10});

                if (attachedManager->isBelowGround() || attachedManager->isCrossingOffices() || !attachedManager->isOnTheGround(30)) {
                    error->setString(ResourceLoader::getTranslation("error.invalid_position"));
                }

                if (System::cash < attachedManager->getCost()) {
                    error->setString(
                            ResourceLoader::getTranslation("error.no_cash") + ", " +
                            ResourceLoader::getTranslation("error.hint.cash") + " " +
                            System::f_to_string(attachedManager->getCost() - System::cash, 0) + "$"
                    );
                }
            }
        } else {
            attachedManager->setTransparent();
        }
    }

    BasicUi::update();
}
