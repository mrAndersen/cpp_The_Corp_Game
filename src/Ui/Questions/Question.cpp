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

    helpText.setFont(*System::debugFont);
    helpText.setCharacterSize(14);
    helpText.setFillColor(sf::Color::Black);

    titleText.setFont(*System::gameFont);
    titleText.setCharacterSize(56);
    titleText.setFillColor(sf::Color::Black);

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
        popup->setVisible(true);
        popup->update();

        auto tBounds = titleText.getLocalBounds();
        auto hBounds = helpText.getLocalBounds();

        helpText.setString(helpTextString);
        titleText.setString(titleTextString);

        helpText.setOrigin(roundf((hBounds.width / 2)), roundf((hBounds.height / 2)));
        titleText.setOrigin(roundf((tBounds.width / 2)), roundf((tBounds.height / 2)));

        sf::Vector2f hPosition = {roundf(popup->getWorldCoordinates().x), roundf(popup->getWorldCoordinates().y)};
        sf::Vector2f tPosition = {roundf(popup->getWorldCoordinates().x), roundf((popup->getWorldCoordinates().y - 190))};

        helpText.setPosition(System::cToGl(hPosition));
        titleText.setPosition(System::cToGl(tPosition));

        System::window->draw(helpText);
        System::window->draw(titleText);
    } else {
        state = S_Button_Normal;
        popup->setVisible(false);
    }

    BasicUi::update();
}

const std::string &Question::getHelpTextString() const {
    return helpTextString;
}

void Question::setHelpTextString(const std::string &helpTextString) {
    Question::helpTextString = helpTextString;
}

const std::string &Question::getTitleTextString() const {
    return titleTextString;
}

void Question::setTitleTextString(const std::string &titleTextString) {
    Question::titleTextString = titleTextString;
}
