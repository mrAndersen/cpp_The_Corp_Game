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

    popupTitle.setFont(*System::gameFont2);
    popupTitle.setCharacterSize(52);
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

    popupText.setOrigin({0, 0});
    popupTitle.setOrigin(roundf((tBounds.width / 2)), roundf((tBounds.height / 2)));

    sf::Vector2f hPosition = {left + 10, top - 150};
    sf::Vector2f tPosition = {roundf(worldCoordinates.x), roundf((worldCoordinates.y - 200))};

    popupText.setPosition(System::cToGl(hPosition));
    popupTitle.setPosition(System::cToGl(tPosition));

    System::window->draw(popupText);
    System::window->draw(popupTitle);
}

sf::Text &Popup::getPopupTitle() {
    return popupTitle;
}

sf::Text &Popup::getPopupText() {
    return popupText;
}

const std::map<std::string, PopupButton *> &Popup::getButtons() const {
    return buttons;
}

void Popup::setButtons(const std::map<std::string, PopupButton *> &buttons) {
    Popup::buttons = buttons;
}