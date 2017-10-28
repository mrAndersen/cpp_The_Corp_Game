#include "Button10x.h"

Button10x::Button10x(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Button10x);
    setDrawOrder(D_Ui_Over);

    setWidth(Button10x::width);
    setHeight(Button10x::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void Button10x::update() {
    selectAnimation(S_Button_Normal);

    if(leftClicked() && !System::spawningUnit){
        selectAnimation(S_Button_Pressed);
    }

    BasicUi::update();
}
