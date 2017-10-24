#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <System/ViewHandler.h>
#include <System/System.h>
#include "MoneyIndicator.h"

MoneyIndicator::MoneyIndicator(sf::Vector2f coordinates) {
    setName("indicator.money");

    setWidth(MoneyIndicator::width);
    setHeight(MoneyIndicator::height);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_Indicator_Money)));

    setDrawOrder(D_Ui);
    initEntity();

    moneyString.setFont(*System::gameFont);
    moneyString.setCharacterSize(40);
    moneyString.setFillColor(sf::Color(254, 221, 109));

    EntityContainer::add(this);
}

void MoneyIndicator::update() {
    selectAnimation(state);

    worldCoordinates.x = ViewHandler::left + width / 2;
    worldCoordinates.y = ViewHandler::top - height / 2;

    if (currentAnimation) {
        currentAnimation->update();
    }

    moneyString.setPosition(System::cToGl(ViewHandler::left + 20, ViewHandler::top - 1));
    moneyString.setString("$ " + System::f_to_string(System::cash));
    System::window->draw(moneyString);

    recalculateBoundaries();
}
