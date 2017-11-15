
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
    auto b1x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button1x]);
    auto b5x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button5x]);
    auto b10x = dynamic_cast<BasicUi *>(ControlPanel::getControls()[E_Button10x]);

    if(pressed){
        selectAnimation(S_Button_Pressed);
    }else{
        selectAnimation(S_Button_Normal);
    }

    if(leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
        pressed = !pressed;
        liveClock.restart();

        b1x->setPressed(false);
        b5x->setPressed(false);
        b10x->setPressed(false);

        System::timeFactor = 0;
    }

    BasicUi::update();
}