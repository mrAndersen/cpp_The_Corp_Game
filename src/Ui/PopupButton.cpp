#include <System/ResourceLoader.h>
#include <System/System.h>
#include <System/EntityContainer.h>
#include <math.h>
#include "PopupButton.h"

PopupButton::PopupButton() : BasicUi(leftOffset, topOffset) {
    setEType(E_Popup_Button);

    setDrawOrder(D_Popup_Button);
    setWidth(PopupButton::width);
    setHeight(PopupButton::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));
    initEntity();

    text.setFont(*System::debugFont);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    EntityContainer::add(this);
}

const sf::Text &PopupButton::getText() const {
    return text;
}

void PopupButton::setText(const sf::Text &text) {
    PopupButton::text = text;
}

const std::string &PopupButton::getString() const {
    return string;
}

void PopupButton::setString(const std::string &string) {
    PopupButton::string = string;
}

void PopupButton::update() {
    if (!visible) {
        return;
    }

    BasicUi::update();

    if (pressed) {
        state = S_Button_Pressed;
    } else {
        state = S_Button_Normal;
    }

    //click
    if (leftClicked() && !System::spawningUnit && liveClock.getElapsedTime().asMilliseconds() >= System::buttonReload) {
        pressed = true;
        liveClock.restart();
    }

    if (liveClock.getElapsedTime().asMilliseconds() >= 100) {
        pressed = false;
    }

    auto tBounds = text.getLocalBounds();

    text.setString(string);
    text.setOrigin(roundf((tBounds.width / 2)), roundf((tBounds.height / 2)));
    text.setPosition(System::cToGl(worldCoordinates));
    currentAnimation->getSprite().setColor(color);

    System::window->draw(text);
}

const sf::Color &PopupButton::getColor() const {
    return color;
}

void PopupButton::setColor(const sf::Color &color) {
    PopupButton::color = color;
}
