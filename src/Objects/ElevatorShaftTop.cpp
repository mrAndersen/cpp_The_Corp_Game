#include <System/System.h>
#include <Text/TextEntity.h>
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

    addAnimation(S_None, Animation(this, S_None, 24, ResourceLoader::getTexture(E_ElevatorShaftTop)));

    setDrawOrder(DrawOrder::D_ElevatorShafts);
    initEntity();

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

    auto *spent = new TextEntity(System::c_red, 30);
    auto position = this->getWorldCoordinates();
    position.y += this->getHeight() / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(this->getCost()) + "$");

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

Elevator *ElevatorShaftTop::getElevator() const {
    return elevator;
}

void ElevatorShaftTop::setElevator(Elevator *elevator) {
    ElevatorShaftTop::elevator = elevator;
}

void ElevatorShaftTop::updateLogic() {

    if(elevator){
        elevator->setTop(top);
        elevator->setLeft(left);
        elevator->setRight(right);

        elevator->update();
    }

    Entity::updateLogic();
}

void ElevatorShaftTop::renderDebugInfo() {

    if (elevator && System::debug) {
        elevator->drawDebug();
    }

    Entity::renderDebugInfo();
}

