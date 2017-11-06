#include "ControlButtonAddManager.h"

ControlButtonAddManager::ControlButtonAddManager(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddManager);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddManager::width);
    setHeight(ControlButtonAddManager::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddManager::update() {
    selectAnimation(S_Button_Normal);

    BasicUi::update();
}
