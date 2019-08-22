#include "../System/System.h"
#include "../Office/Chair.h"
#include "../System/EntityContainer.h"
#include "WorkPlace.h"

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

WorkPlace::WorkPlace(const sf::Vector2f &worldCoordinates, Office *parentOffice) {
    this->worldCoordinates = worldCoordinates;
    this->parentOffice = parentOffice;
}

void WorkPlace::drawDebug() {
    sf::RectangleShape rect;

    rect.setPosition(System::cToGl(worldCoordinates));
    rect.setSize({15, 15});

    if (worker) {
        rect.setFillColor(sf::Color::Red);
    } else {
        rect.setFillColor(sf::Color::Green);
    }

    System::window->draw(rect);
}

void WorkPlace::update() {

    if (worker && !chair) {
        chair = new Chair({worldCoordinates.x - 23, worldCoordinates.y - 16});
    }

    if(!worker && chair){
        EntityContainer::remove(chair);
        chair = nullptr;
    }
}
