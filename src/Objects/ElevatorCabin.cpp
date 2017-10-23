#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <Text/TextEntity.h>
#include <System/System.h>
#include "ElevatorCabin.h"

ElevatorCabin::ElevatorCabin(sf::Vector2f coordinates) {
    setName("elevator.cabin");

    setWidth(ElevatorCabin::width);
    setHeight(ElevatorCabin::height);
    setCost(500);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ElevatorCabin)));

    setDrawOrder(DrawOrder::D_ElevatorCabin);
    initEntity();

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
    for (auto e:EntityContainer::getItems()) {
        if (e != this) {
            if (
                    e->getName() == "elevator.shaft.middle" &&
                    (int) e->getLeft() == (int) left &&
                    (int) e->getBottom() == (int) bottom &&
                    (int) e->getTop() == (int) top &&
                    (int) e->getRight() == (int) right
                    ) {
                return true;
            }
        }
    }

    return false;
}

void ElevatorCabin::updateLogic() {
    //update floor
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;

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

    for (auto e:EntityContainer::getItems()) {

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

    elevator->addToQueue(3);
    elevator->finish();

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
