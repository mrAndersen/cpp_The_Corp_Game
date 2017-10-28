#include "Button5x.h"

Button5x::Button5x(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Button5x);
    setDrawOrder(D_Ui_Over);

    setWidth(Button5x::width);
    setHeight(Button5x::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void Button5x::update() {
    selectAnimation(S_Button_Normal);

    if(leftClicked() && !System::spawningUnit){
        selectAnimation(S_Button_Pressed);
    }

    BasicUi::update();
}
