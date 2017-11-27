#include <math.h>
#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "Popup.h"

Popup::Popup(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Popup);

    setDrawOrder(D_Popup);
    setVisible(false);

    setWidth(Popup::width);
    setHeight(Popup::height);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    popupText.setFont(*System::debugFont);
    popupText.setCharacterSize(14);
    popupText.setFillColor(sf::Color::Black);

    popupTitle.setFont(*System::gameFont);
    popupTitle.setCharacterSize(56);
    popupTitle.setFillColor(sf::Color::Black);

    EntityContainer::add(this);
}

void Popup::update() {
    if (!visible) {
        return;
    }

    BasicUi::update();

    if (mouseIn()) {
        //preventSelection if mouse inside popup
        System::selectionCooldown.restart();
    }

    auto tBounds = popupTitle.getLocalBounds();
    auto hBounds = popupText.getLocalBounds();

    popupText.setString(popupTextString);
    popupTitle.setString(popupTitleString);

    popupText.setOrigin({0, 0});
    popupTitle.setOrigin(roundf((tBounds.width / 2)), roundf((tBounds.height / 2)));

    sf::Vector2f hPosition = {left + 10, top - 150};
    sf::Vector2f tPosition = {roundf(worldCoordinates.x), roundf((worldCoordinates.y - 190))};

    popupText.setPosition(System::cToGl(hPosition));
    popupTitle.setPosition(System::cToGl(tPosition));

    System::window->draw(popupText);
    System::window->draw(popupTitle);
}

sf::Text &Popup::getPopupTitle() {
    return popupTitle;
}

void Popup::setPopupTitle(const sf::Text &popupTitle) {
    Popup::popupTitle = popupTitle;
}

const std::string &Popup::getPopupTitleString() const {
    return popupTitleString;
}

void Popup::setPopupTitleString(const std::string &popupTitleString) {
    Popup::popupTitleString = popupTitleString;
}

sf::Text &Popup::getPopupText() {
    return popupText;
}

void Popup::setPopupText(const sf::Text &popupText) {
    Popup::popupText = popupText;
}

const std::string &Popup::getPopupTextString() const {
    return popupTextString;
}

void Popup::setPopupTextString(const std::string &popupTextString) {
    Popup::popupTextString = popupTextString;
}

Popup::~Popup() {
    for (auto &b:buttons) {
        delete b.second;
    }

    buttons.clear();
}
