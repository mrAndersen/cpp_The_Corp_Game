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
    auto pause = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_ButtonPause]);;
    auto b1x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button1x]);
    auto b5x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button5x]);

    if(pressed){
        state = S_Button_Pressed;
    }else{
        state = S_Button_Normal;
    }

    if(leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
        pressed = !pressed;
        liveClock.restart();

        b1x->setPressed(false);
        b5x->setPressed(false);
        pause->setPressed(false);

        System::timeFactor = 20;
    }

    BasicUi::update();
}
