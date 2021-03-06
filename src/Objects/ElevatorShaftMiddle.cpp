#include "../System/System.h"
#include "../Text/TextEntity.h"
#include "ElevatorShaftMiddle.h"
#include "../System/EntityContainer.h"
#include "../System/ResourceLoader.h"

ElevatorShaftMiddle::ElevatorShaftMiddle(sf::Vector2f coordinates) : Entity(E_ElevatorShaftMiddle) {
    setWidth(ElevatorShaftMiddle::width);
    setHeight(ElevatorShaftMiddle::height);
    setCost(1000);
    setGroupName("shafts");
    setSerializable(true);

    setWorldCoordinates(coordinates);
    setSelectable(false);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    addAnimation(S_Working, Animation(this, S_Working, 3, ResourceLoader::getTexture(eType), 333333));

    setDrawOrder(DrawOrder::D_ElevatorShafts);
    initEntity();

    EntityContainer::add(this);
}


float ElevatorShaftMiddle::getCost() const {
    return cost;
}

void ElevatorShaftMiddle::setCost(float cost) {
    ElevatorShaftMiddle::cost = cost;
}

bool ElevatorShaftMiddle::hasMiddleShaftOnTheBottom() {
    for (auto e:EntityContainer::items[System::activeScene]) {

        if (dynamic_cast<ElevatorShaftMiddle *>(e) && e->getTop() == bottom) {
            return true;
        }
    }

    return false;
}

std::vector<Office *> ElevatorShaftMiddle::getNeighborOffices() {
    std::vector<Office *> result;
    std::vector<Entity *> offices = EntityContainer::getGroupItems("offices");

    for (auto e:offices) {
        auto target = dynamic_cast<Office *>(e);

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

    auto *spent = new TextEntity(System::c_red, 30);
    auto position = this->getWorldCoordinates();
    position.y += this->getHeight() / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(this->getCost()) + "$");

    spawned = true;
}


