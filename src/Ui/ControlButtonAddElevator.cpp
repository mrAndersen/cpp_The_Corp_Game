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
    selectAnimation(S_Button_Normal);

    worldCoordinates.x = ViewHandler::left + leftOffset;
    worldCoordinates.y = ViewHandler::top - topOffset;

    if (leftClicked() && !System::spawningUnit) {
        selectAnimation(S_Button_Pressed);
    }

    if (currentAnimation) {
        currentAnimation->update();
    }
}
