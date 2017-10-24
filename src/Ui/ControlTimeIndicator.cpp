#include "ControlTimeIndicator.h"
#include "System/System.h"
#include "System/ViewHandler.h"

ControlTimeIndicator::ControlTimeIndicator(const sf::Color &color, int size) : TextEntity(color, size) {
    setName("time.indicator");

    setLiveTimeSeconds(0);
    setDirection(Direction::None);
}

void ControlTimeIndicator::update() {
    worldCoordinates.x = ViewHandler::left + 12;
    worldCoordinates.y = ViewHandler::top - 40;

    setString("Time: x" + System::f_to_string(System::timeFactor));

    TextEntity::update();
}
