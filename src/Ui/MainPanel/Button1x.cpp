#include "Button1x.h"

Button1x::Button1x(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Button1x);
    setDrawOrder(D_Ui_Over);

    setWidth(Button1x::width);
    setHeight(Button1x::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void Button1x::update() {
    selectAnimation(S_Button_Normal);

    if(leftClicked() && !System::spawningUnit){
        selectAnimation(S_Button_Pressed);
    }

    BasicUi::update();
}
