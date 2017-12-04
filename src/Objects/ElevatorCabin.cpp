#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "..\Text\TextEntity.h"
#include "..\System\System.h"
#include "ElevatorCabin.h"


ElevatorCabin::ElevatorCabin(sf::Vector2f coordinates) {
    setEType(E_ElevatorCabin);

    setWidth(ElevatorCabin::width);
    setHeight(ElevatorCabin::height);
    setCost(500);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));

    setSelectable(true);
    setDrawOrder(DrawOrder::D_ElevatorCabin);
    initEntity();

    capacityIndicator.setFillColor(sf::Color::Green);
    capacityIndicator.setFont(*System::textFont);
    capacityIndicator.setCharacterSize(10);

    floorIndicator.setFillColor(sf::Color::Green);
    floorIndicator.setFont(*System::textFont);
    floorIndicator.setCharacterSize(10);

    EntityContainer::add(this);
}

float ElevatorCabin::getCost() const {
    return cost;
}

void ElevatorCabin::setCost(float cost) {
    ElevatorCabin::cost = cost;
}

bool ElevatorCabin::isSpawned() const {
    return spawned;
}

bool ElevatorCabin::isInsideShaftBoundaries() {
    for (auto e:EntityContainer::getGroupItems("shafts")) {
        if (
                (int) e->getLeft() == (int) left &&
                (int) e->getBottom() == (int) bottom &&
                (int) e->getTop() == (int) top &&
                (int) e->getRight() == (int) right
                ) {
            return true;
        }
    }

    return false;
}

bool ElevatorCabin::hasElevatorShaftTopAbove() {
    for (auto e:EntityContainer::getGroupItems("shafts")) {
        if (e->getEType() == E_ElevatorShaftTop && e->getWorldCoordinates().x == worldCoordinates.x) {
            return true;
        }
    }

    return false;
}

void ElevatorCabin::updateLogic() {
    //update floor
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;

    if (!currentPeople.empty()) {
        for (auto p:currentPeople) {
            p->setWorldCoordinates({p->getWorldCoordinates().x, worldCoordinates.y - 15});
        }
    }

    updateIndicators();
    Entity::updateLogic();
}

void ElevatorCabin::spawn() {
    auto *spent = new TextEntity(System::c_red, 30);
    auto position = worldCoordinates;
    position.y += height / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(cost) + "$");


    auto elevator = new Elevator();
    elevator->addCabin(this);

    for (auto e:EntityContainer::items[System::activeScene]) {

        if (auto d = dynamic_cast<ElevatorShaftMiddle *>(e)) {
            if (d->getWorldCoordinates().x == worldCoordinates.x) {
                elevator->addMiddleSection(d);
            }
        }

        if (auto d = dynamic_cast<ElevatorShaftTop *>(e)) {
            if (d->getWorldCoordinates().x == worldCoordinates.x) {
                elevator->addTopSection(d);
                d->setElevator(elevator);
            }
        };
    }

    elevator->addToQueue(1);
    elevator->finish();
    this->elevator = elevator;


    Entity::spawn();
}

int ElevatorCabin::getFloor() const {
    return floor;
}

void ElevatorCabin::setFloor(int floor) {
    ElevatorCabin::floor = floor;
}

bool ElevatorCabin::isMovableInside(Movable *movable) {
    return movable->getWorldCoordinates().x > worldCoordinates.x + movable->getWidth() / 2 &&
           movable->getWorldCoordinates().x < worldCoordinates.x - movable->getWidth() / 2;

}

const std::vector<Movable *> &ElevatorCabin::getCurrentPeople() const {
    return currentPeople;
}

void ElevatorCabin::addMovable(Movable *movable) {
    if (std::find(currentPeople.begin(), currentPeople.end(), movable) == currentPeople.end()) {
        currentPeople.push_back(movable);
    }
}

void ElevatorCabin::updateIndicators() {
    if (spawned) {
        auto position = worldCoordinates;
        position.x += 36;
        position.y += 71.5;

        if (currentPeople.size() < 10) {
            capacityIndicator.setString("0" + std::to_string(currentPeople.size()) + "/" + std::to_string(capacity));
        } else {
            capacityIndicator.setString(std::to_string(currentPeople.size()) + "/" + std::to_string(capacity));
        }

        capacityIndicator.setPosition(System::cToGl(position));
        System::window->draw(capacityIndicator);

        auto position2 = worldCoordinates;
        position2.x -= 52;
        position2.y += 71.5;

        if (floor < 10) {
            floorIndicator.setString("0" + std::to_string(floor));
        } else {
            floorIndicator.setString(std::to_string(floor));
        }

        floorIndicator.setPosition(System::cToGl(position2));
        System::window->draw(floorIndicator);
    }
}

void ElevatorCabin::removeMovable(Movable *movable) {
    currentPeople.erase(std::remove(currentPeople.begin(), currentPeople.end(), movable), currentPeople.end());
}

int ElevatorCabin::getSpeed() const {
    return speed;
}

void ElevatorCabin::setSpeed(int speed) {
    ElevatorCabin::speed = speed;
}

bool ElevatorCabin::hasFreeSpace() {
    return currentPeople.size() < capacity;
}

int ElevatorCabin::getCapacity() const {
    return capacity;
}

void ElevatorCabin::setCapacity(int capacity) {
    ElevatorCabin::capacity = capacity;
}


