#include "ButtonPause.h"

ButtonPause::ButtonPause(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonPause);
    setDrawOrder(D_Ui_Over);

    setWidth(ButtonPause::width);
    setHeight(ButtonPause::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ButtonPause::update() {
    selectAnimation(S_Button_Normal);

    if(leftClicked() && !System::spawningUnit){
        selectAnimation(S_Button_Pressed);
    }

    BasicUi::update();
}