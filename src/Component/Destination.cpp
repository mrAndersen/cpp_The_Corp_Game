#include "Destination.h"

const sf::Vector2f &Destination::getCoordinates() const {
    return coordinates;
}

void Destination::setCoordinates(const sf::Vector2f &coordinates) {
    Destination::coordinates = coordinates;
}

Destination::Destination(const sf::Vector2f &coordinates, DestinationType type) : coordinates(coordinates),
                                                                                  type(type) {}

DestinationType Destination::getType() const {
    return type;
}

void Destination::setType(DestinationType type) {
    Destination::type = type;
}

bool Destination::reached(Movable *movable) {
    return movable->getWorldCoordinates() == coordinates;
}

int Destination::getFloor() {
    return ((int) coordinates.y - ((int) coordinates.y % System::gridSize)) / System::gridSize / 3;
}
