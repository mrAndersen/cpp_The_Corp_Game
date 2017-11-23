#include "Button1x.h"

Button1x::Button1x(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Button1x);
    setDrawOrder(D_Ui_Over);

    setWidth(Button1x::width);
    setHeight(Button1x::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    setPressed(true);
    initEntity();
    EntityContainer::add(this);
}

void Button1x::update() {
    auto pause = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_ButtonPause]);;
    auto b5x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button5x]);
    auto b10x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button10x]);

    if(pressed){
        state = S_Button_Pressed;
    }else{
        state = S_Button_Normal;
    }

    if(leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
        pressed = !pressed;
        liveClock.restart();

        pause->setPressed(false);
        b5x->setPressed(false);
        b10x->setPressed(false);

        System::timeFactor = 1;
    }

    BasicUi::update();
}
