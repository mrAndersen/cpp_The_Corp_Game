#include "../System/ViewHandler.h"
#include "../System/System.h"
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"
#include "MoneyIndicator.h"

MoneyIndicator::MoneyIndicator(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Indicator_Money);
    setDrawOrder(D_Ui);
    setWidth(MoneyIndicator::width);
    setHeight(MoneyIndicator::height);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    moneyString.setFont(*System::titleFont);
    moneyString.setCharacterSize(40);
    moneyString.setFillColor(sf::Color::White);

    EntityContainer::add(this);
}

void MoneyIndicator::update() {
    BasicUi::update();

    moneyString.setPosition(System::cToGl(ViewHandler::left + 20, ViewHandler::top - 1));
    moneyString.setString("$ " + System::f_to_string(System::cash));
    System::window->draw(moneyString);
}