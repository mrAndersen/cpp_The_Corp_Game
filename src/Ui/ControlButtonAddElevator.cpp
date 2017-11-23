
#include "ControlButtonAddElevator.h"

ControlButtonAddElevator::ControlButtonAddElevator(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddElevator);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddElevator::width);
    setHeight(ControlButtonAddElevator::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddElevator::update() {
    auto bc = ControlPanel::getControls()[E_ButtonAddElevatorCabin];
    auto bs = ControlPanel::getControls()[E_ButtonAddElevatorShaftMiddle];
    auto bst = ControlPanel::getControls()[E_ButtonAddElevatorShaftTop];

    if (leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
        pressed = !pressed;
        liveClock.restart();
    }

    if (pressed) {
        state = S_Button_Pressed;

        bc->setVisible(true);
        bs->setVisible(true);
        bst->setVisible(true);
    } else {
        state = S_Button_Normal;

        bc->setVisible(false);
        bs->setVisible(false);
        bst->setVisible(false);
    }

    BasicUi::update();
}
