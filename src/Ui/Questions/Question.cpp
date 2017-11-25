#include "..\Popup.h"
#include <cmath>
#include "..\..\System\System.h"
#include "Question.h"

Question::Question(float leftOffset, float topOffset, Entities type) : BasicUi(leftOffset, topOffset) {
    setEType(type);
    setDrawOrder(D_Ui);
    setGroupName("questions");

    setWidth(Question::width);
    setHeight(Question::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    popup = new Popup(300, 400);

    initEntity();
    EntityContainer::add(this);
}

void Question::update() {
    if (leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
        pressed = !pressed;
        liveClock.restart();
    }

    if (pressed) {
        auto questions = EntityContainer::getGroupItems("questions");

        for (auto &e:questions) {
            auto q = dynamic_cast<Question *>(e);

            if (q && q != this) {
                q->setPressed(false);
            }
        }

        state = S_Button_Pressed;
        System::selectionCooldown.restart();

        popup->setVisible(true);
        popup->update();


    } else {
        state = S_Button_Normal;
        popup->setVisible(false);
    }

    BasicUi::update();
}