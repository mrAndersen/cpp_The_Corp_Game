#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "Cog.h"

Cog::Cog(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Cog);
    setDrawOrder(D_Ui_Over);

    setWidth(Cog::width);
    setHeight(Cog::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void Cog::update() {
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

        //@todo fix
        System::changeScene(SC_Main_Menu);
    }

    if (liveClock.getElapsedTime().asMilliseconds() >= 100) {
        pressed = false;
    }

    BasicUi::update();
}


