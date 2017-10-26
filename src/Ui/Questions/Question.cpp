#include <System/System.h>
#include "Question.h"

Question::Question(float leftOffset, float topOffset, Entities type) : BasicUi(leftOffset, topOffset) {
    setEType(type);
    setDrawOrder(D_Ui);

    setWidth(Question::width);
    setHeight(Question::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void Question::update() {
    selectAnimation(S_Button_Normal);

    worldCoordinates.x = ViewHandler::left + leftOffset;
    worldCoordinates.y = ViewHandler::top - topOffset;

    if (leftClicked() && !System::spawningUnit) {
        selectAnimation(S_Button_Pressed);
    }

    if (currentAnimation) {
        currentAnimation->update();
    }
}
