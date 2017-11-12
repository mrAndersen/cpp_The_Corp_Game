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
    selectAnimation(S_Button_Normal);

    bool spawnCondition = attachedManager &&
                          System::cash >= attachedManager->getCost() &&
                          !attachedManager->isBelowGround();

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
        selectAnimation(S_Button_Pressed);
        System::spawningUnit = true;
        attachedManager->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedManager->setInvalid();

            //placement error
            if (attachedManager && attachedManager->isBelowGround() &&
                attachedManager->getErrorString().getString().isEmpty()) {
                attachedManager->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedManager->getCost() && attachedManager->getErrorString().getString().isEmpty()) {
                attachedManager->getErrorString().setString("Not enough cash");
            }
        } else {
            attachedManager->setTransparent();
        }
    }

    BasicUi::update();
}
