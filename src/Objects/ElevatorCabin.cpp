#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "ElevatorCabin.h"

ElevatorCabin::ElevatorCabin(sf::Vector2f coordinates) {
    setName("elevator.cabin");

    setWidth(ElevatorCabin::width);
    setHeight(ElevatorCabin::height);
    setCost(500);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ElevatorCabin)));

    setDrawOrder(DrawOrder::D_ElevatorCabin);
    createAnimationFrames();

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
                    )
            {
                return true;
            }
        }
    }

    return false;
}

void ElevatorCabin::updateLogic() {
    Entity::updateLogic();
}

void ElevatorCabin::spawn() {














    Entity::spawn();
}
