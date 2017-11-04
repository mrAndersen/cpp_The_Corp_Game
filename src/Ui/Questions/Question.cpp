#include <System/System.h>
#include "Question.h"

Question::Question(float leftOffset, float topOffset, Entities type) : BasicUi(leftOffset, topOffset) {
    setEType(type);
    setDrawOrder(D_Ui);

    setWidth(Question::width);
    setHeight(Question::height);

    addAnimation(S_Button_Normal,
                 Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed,
                 Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    helpText.setFont(*System::gameFont);
    helpText.setCharacterSize(26);
    helpText.setFillColor(sf::Color::Black);
    helpText.setString(helpTextString);

    initEntity();
    EntityContainer::add(this);
}

void Question::update() {
    if (leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
        pressed = !pressed;
        liveClock.restart();
    }

    if (pressed) {
        selectAnimation(S_Button_Pressed);
        auto color = sf::Color(160, 87, 14);

        auto size = sf::Vector2f(500, 300);


        helpText.setPosition(System::cToGl({ViewHandler::left + 100, ViewHandler::top - 500 + size.y}));

        popup[0].position = System::cToGl({ViewHandler::left + 100, ViewHandler::top - 500});
        popup[0].color = color;

        popup[1].position = System::cToGl({ViewHandler::left + 100, ViewHandler::top - 500 + size.y});
        popup[1].color = color;

        popup[2].position = System::cToGl({ViewHandler::left + 100 + size.x, ViewHandler::top - 500 + size.y});
        popup[2].color = color;

        popup[3].position = System::cToGl({ViewHandler::left + 100 + size.x, ViewHandler::top - 500});
        popup[3].color = color;

        System::window->draw(popup, 4, sf::Quads);
        System::window->draw(helpText);
    } else {
        selectAnimation(S_Button_Normal);
    }

    BasicUi::update();
}
