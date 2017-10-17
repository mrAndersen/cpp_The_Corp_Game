#include "WorkPlace.h"

WorkPlace::WorkPlace(const sf::Vector2f &worldCoordinates) : worldCoordinates(worldCoordinates) {

}

const sf::Vector2f &WorkPlace::getWorldCoordinates() const {
    return worldCoordinates;
}

void WorkPlace::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    WorkPlace::worldCoordinates = worldCoordinates;
}

Office *WorkPlace::getParentOffice() const {
    return parentOffice;
}

void WorkPlace::setParentOffice(Office *parentOffice) {
    WorkPlace::parentOffice = parentOffice;
}

Movable *WorkPlace::getWorker() const {
    return worker;
}

void WorkPlace::setWorker(Movable *worker) {
    WorkPlace::worker = worker;
}
