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
                          !attachedAccountant->isBelowGround();

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
        state = S_Button_Pressed;
        System::spawningUnit = true;
        attachedAccountant->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedAccountant->setInvalid();

            //placement error
            if (attachedAccountant && attachedAccountant->isBelowGround() &&
                attachedAccountant->getErrorString().getString().isEmpty()) {
                attachedAccountant->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedAccountant->getCost() && attachedAccountant->getErrorString().getString().isEmpty()) {
                attachedAccountant->getErrorString().setString("Not enough cash");
            }
        } else {
            attachedAccountant->setTransparent();
        }
    }

    BasicUi::update();
}
