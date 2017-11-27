#include "Destination.h"
#include "../Basic/Movable.h"
#include "../Characters/Clerk.h"
#include "../Characters/Accountant.h"

const sf::Vector2f &Destination::getCoordinates() const {
    return coordinates;
}

void Destination::setCoordinates(const sf::Vector2f &coordinates) {
    Destination::coordinates = coordinates;
}

Destination::Destination(const sf::Vector2f &coordinates, DestinationType type) : coordinates(coordinates), type(type) {

}

DestinationType Destination::getType() const {
    return type;
}

void Destination::setType(DestinationType type) {
    Destination::type = type;
}

int Destination::getFloor() {
    return ((int) coordinates.y - ((int) coordinates.y % System::gridSize)) / System::gridSize / 3;
}

Destination Destination::createElevatorWaitingDST(Elevator *elevator, Movable *movable) {
    auto scatter = 100;

    if (movable->getWorldCoordinates().x <= elevator->getLeft()) {
        return {{elevator->getLeft() - movable->getWidth() / 2 - System::getRandom(0, scatter),
                 movable->getWorldCoordinates().y}, DST_Elevator_Waiting};
    }

    if (movable->getWorldCoordinates().x > elevator->getRight()) {
        return {{elevator->getRight() + movable->getWidth() / 2 + System::getRandom(0, scatter),
                 movable->getWorldCoordinates().y}, DST_Elevator_Waiting};
    }
}

Destination Destination::createElevatorCabinDST(Elevator *elevator, Movable *movable) {
    return {{(float) System::getRandom(
            (int) elevator->getCabin()->getWorldCoordinates().x - 75 + movable->getWidth() / 2,
            (int) elevator->getCabin()->getWorldCoordinates().x + 75 - movable->getWidth() / 2),
             movable->getWorldCoordinates().y}, DST_Elevator_Inside_Cabin};
}

Destination Destination::createElevatorExitingDST(Elevator *elevator, Movable *movable, sf::Vector2f finalDestination) {
    if (finalDestination.x <= elevator->getLeft()) {
        return {{elevator->getLeft(), movable->getFloorBottom(finalDestination) + movable->getHeight() / 2},
                DST_Elevator_Exiting};
    }

    if (finalDestination.x > elevator->getRight()) {
        return {{elevator->getRight(), movable->getFloorBottom(finalDestination) + movable->getHeight() / 2},
                DST_Elevator_Exiting};
    }
}

Destination Destination::createWorkplaceDST(Clerk *movable) {
    return {{movable->getCurrentWorkPlace()->getWorldCoordinates().x,
             movable->getCurrentWorkPlace()->getParentOffice()->getBottom() + movable->getHeight() / 2}, DST_Workplace};
}

Destination Destination::createWorkplaceDST(Accountant *movable) {
    return {{movable->getCurrentWorkPlace()->getWorldCoordinates().x,
             movable->getCurrentWorkPlace()->getParentOffice()->getBottom() + movable->getHeight() / 2}, DST_Workplace};
}

Destination Destination::createBuffPlaceDST(Clerk *movable) {
    return {{movable->getCurrentWorkPlace()->getWorldCoordinates().x - 35,
             movable->getCurrentWorkPlace()->getParentOffice()->getBottom() + movable->getHeight() / 2}, DST_Buff_Position};
}

Destination Destination::createBuffPlaceDST(Accountant *movable) {
    return {{movable->getCurrentWorkPlace()->getWorldCoordinates().x - 35,
             movable->getCurrentWorkPlace()->getParentOffice()->getBottom() + movable->getHeight() / 2}, DST_Buff_Position};
}


Destination Destination::createSmokeAreaDST(Movable *movable, sf::Vector2f &smokeArea) {
    auto scatter = 300;

    return {{(float) System::getRandom((int) smokeArea.x - scatter / 2, (int) smokeArea.x + scatter / 2),
             System::groundLevel + Ground::height + movable->getHeight() / 2}, DST_SmokeArea};
}

Destination Destination::createHomeDST(Movable *movable, sf::Vector2f &home) {
    return {{home.x, System::groundLevel + Ground::height + movable->getHeight() / 2}, DST_Home};
}


