#include <System/System.h>
#include "ElevatorShaftMiddle.h"
#include "System/EntityContainer.h"

ElevatorShaftMiddle::ElevatorShaftMiddle(sf::Vector2f coordinates) {
    setName("elevator.shaft.middle");

    setWidth(ElevatorShaftMiddle::width);
    setHeight(ElevatorShaftMiddle::height);
    setCost(1000);

    setWorldCoordinates(coordinates);
    setSelectable(true);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ElevatorShaftMiddle)));

    setDrawOrder(DrawOrder::D_ElevatorShafts);
    createAnimationFrames();

    EntityContainer::add(this);
}

float ElevatorShaftMiddle::getCost() const {
    return cost;
}

void ElevatorShaftMiddle::setCost(float cost) {
    ElevatorShaftMiddle::cost = cost;
}

bool ElevatorShaftMiddle::hasMiddleShaftOnTheBottom() {
    for (auto e:EntityContainer::getItems()) {

        if (auto d = dynamic_cast<ElevatorShaftMiddle *>(e) && e->getTop() == bottom) {
            return true;
        }
    }

    return false;
}

std::vector<Office *> ElevatorShaftMiddle::getNeighborOffices() {
    std::vector<Office *> result;
    std::vector<Office *> offices = EntityContainer::getOffices();

    for (auto target:offices) {
        if ((int) target->getRight() == (int) this->left &&
            target->getWorldCoordinates().y == this->worldCoordinates.y && target->getFloor() == 1) {
            result.push_back(target);
        }

        if ((int) target->getLeft() == (int) this->right &&
            target->getWorldCoordinates().y == this->worldCoordinates.y && target->getFloor() == 1) {
            result.push_back(target);
        }

        if (
                (int) target->getTop() == (int) this->bottom &&
                this->worldCoordinates.x == target->getWorldCoordinates().x
                ) {
            result.push_back(target);
        }
    }

    return result;
}



void ElevatorShaftMiddle::spawn() {
    System::cash -= this->cost;

    spawned = true;
}
