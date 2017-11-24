#include <math.h>
#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "Popup.h"

Popup::Popup(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Popup);

    setDrawOrder(D_Ui);
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

    auto tBounds = popupTitle.getLocalBounds();
    auto hBounds = popupText.getLocalBounds();

    popupText.setString(popupTextString);
    popupTitle.setString(popupTitleString);

    popupText.setOrigin(roundf((hBounds.width / 2)), roundf((hBounds.height / 2)));
    popupTitle.setOrigin(roundf((tBounds.width / 2)), roundf((tBounds.height / 2)));

    sf::Vector2f hPosition = worldCoordinates;
    sf::Vector2f tPosition = {roundf(worldCoordinates.x), roundf((worldCoordinates.y - 190))};

    popupText.setPosition(System::cToGl(hPosition));
    popupTitle.setPosition(System::cToGl(tPosition));

    System::window->draw(popupText);
    System::window->draw(popupTitle);
}

const sf::Text &Popup::getPopupText() const {
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

const sf::Text &Popup::getPopupTitle() const {
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
