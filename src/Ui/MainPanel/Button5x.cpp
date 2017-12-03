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
    auto pause = dynamic_cast<BasicUi *>(ControlPanel::controls[E_ButtonPause]);;
    auto b1x = dynamic_cast<BasicUi *>(ControlPanel::controls[E_Button1x]);
    auto b10x = dynamic_cast<BasicUi *>(ControlPanel::controls[E_Button10x]);

    if(pressed){
        state = S_Button_Pressed;
    }else{
        state = S_Button_Normal;
    }

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

    if(leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload){
        pressed = !pressed;
        liveClock.restart();

        pause->setPressed(false);
        b1x->setPressed(false);
        b10x->setPressed(false);

        System::timeFactor = 10;
    }

    BasicUi::update();
}
