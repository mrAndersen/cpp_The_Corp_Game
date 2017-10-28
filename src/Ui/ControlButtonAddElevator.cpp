
#include "ControlButtonAddElevator.h"

ControlButtonAddElevator::ControlButtonAddElevator(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddElevator);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddElevator::width);
    setHeight(ControlButtonAddElevator::height);

    addAnimation(S_Button_Normal,
                 Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed,
                 Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddElevator::update() {
    auto addCabin = ControlPanel::getControls()[E_ButtonAddElevatorCabin];

    if (leftClicked() && !System::spawningUnit) {
        pressed = !pressed;
    }

    if (pressed) {
        selectAnimation(S_Button_Pressed);
        addCabin->setVisible(true);
    } else {
        selectAnimation(S_Button_Normal);
        addCabin->setVisible(false);
    }

    BasicUi::update();
}
