//
// Created by mrAndersen on 13.10.2017.
//

#include "../../includes/Controls/ControlCashIndicator.h"
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"

ControlCashIndicator::ControlCashIndicator(const sf::Color &color, int size) : TextEntity(color, size) {
    setName("cash.indicator");

    setLiveTimeSeconds(0);
    setDirection(Direction::None);
}

void ControlCashIndicator::update() {
    worldCoordinates.x = ViewHandler::left + 12;
    worldCoordinates.y = ViewHandler::top + 10;

    setString(System::f_to_string(System::cash) + "$");
    TextEntity::update();
}