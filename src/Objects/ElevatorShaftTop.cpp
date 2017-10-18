#include <System/System.h>
#include "ElevatorShaftTop.h"
#include "System/EntityContainer.h"
#include "ElevatorShaftMiddle.h"


ElevatorShaftTop::ElevatorShaftTop(sf::Vector2f coordinates) {
    setName("elevator.shaft.top");

    setWidth(ElevatorShaftTop::width);
    setHeight(ElevatorShaftTop::height);
    setCost(1000);

    setWorldCoordinates(coordinates);
    setSelectable(true);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ElevatorShaftTop)));

    setDrawOrder(DrawOrder::D_ElevatorShafts);
    createAnimationFrames();

    EntityContainer::add(this);
}

bool ElevatorShaftTop::hasMiddleShaftOnTheBottom() {
    for (auto e:EntityContainer::getItems()) {

        if (auto d = dynamic_cast<ElevatorShaftMiddle *>(e) && e->getTop() == bottom) {
            return true;
        }
    }

    return false;
}

float ElevatorShaftTop::getCost() const {
    return cost;
}

void ElevatorShaftTop::setCost(float cost) {
    ElevatorShaftTop::cost = cost;
}

void ElevatorShaftTop::spawn() {
    System::cash -= this->cost;

    spawned = true;
}

std::vector<Office *> ElevatorShaftTop::getNeighborOffices() {
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

