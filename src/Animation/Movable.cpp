#include <cmath>
#include "../../includes/System/Enum.h"
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"

void Movable::renderCurrentFrame() {

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
        sprite.setRotation(0);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
        sprite.setRotation(0);
    }

    Entity::renderCurrentFrame();
}

void Movable::renderDebugInfo() {
    if (System::animationDebug) {
        info.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        info.setString(
                "id: " + std::to_string(id) + "\n" +
                "pos: {" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) +
                "}\n" +
                "left: " + std::to_string((int) left) + "," +
                "right: " + std::to_string((int) right) + "," +
                "top: " + std::to_string((int) top) + "," +
                "bottom: " + std::to_string((int) bottom) + "\n" +
                "office: " + std::to_string(currentWorkPlace ? currentWorkPlace->getId() : 0) + "\n" +
                "state: " + std::to_string(state) + "\n" +
                "floor: " + std::to_string(floor) + "\n"
        );
        System::window->draw(info);
    }
}

void Movable::updateAnimation() {
    float frameDistance = (frameTimeMs / 1000) * speed;

    if (direction == Direction::Down && state == S_Falling) {
        worldCoordinates.y -= frameDistance;
        speed = speed + fallAcceleration * (frameTimeMs / 1000);
    }

    if (direction == Direction::Right) {
        worldCoordinates.x += frameDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= frameDistance;
    }

    Entity::updateAnimation();
}

void Movable::updateLogic() {

    //update floor
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize;

    //no work place
    if (!currentWorkPlace && isOnTheGround()) {
        errorString.setString("No office");
        state = S_None;
    }

    if (currentWorkPlace) {
        errorString.setString("");
    }

    //falling
    if (!isOnTheGround() && isAboveGround() && direction == Direction::Down) {
        state = S_Falling;
    }

    //stop falling
    if (isOnTheGround() && state == S_Falling) {
        direction = Direction::None;
        state = S_GoToOffice;
    }

    //stop smoking
    if (state == S_Smoke && System::gameTime.diffMinutes(smokeStarted) >= smokePeriodMinutes) {
        state = S_GoToOffice;
    }

    //go to office
    if (state == S_GoToOffice && currentWorkPlace) {

        if (isInWorkPlace()) {
            state = S_Work;
        }

        if (currentWorkPlace->getFloor() == this->floor) {
            //office is on the same floor

            if (currentWorkPlace->getWorldCoordinates().x < this->worldCoordinates.x) {
                direction = Direction::Left;
            } else {
                direction = Direction::Right;
            }
        } else {
            state = S_GoToElevator;
        }
    }

    if (state == S_GoToElevator) {

    }

    if (
            currentWorkPlace &&
            (state != S_GoToOffice && state != S_GoSmoke && state != S_Smoke) &&
            System::gameTime.isWorkTime()
            ) {
        state = S_GoToOffice;
        speed = 300;
    }

    //search workplace every 500ms
    if (isOnTheGround() && !currentWorkPlace && workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
        searchWorkPlace();
    }


    //world boundaries
    if (hasReachedWorldEdges()) {
        health = 0;
    }

    if (health <= 0) {
        EntityContainer::remove(this);
    }
}

bool Movable::hasReachedWorldEdges() {
    return !((worldCoordinates.x + width / 2) <= System::worldWidth / 2 &&
             (worldCoordinates.x - width / 2) >= -System::worldWidth / 2);
}

Direction Movable::getDirection() const {
    return direction;
}

void Movable::setDirection(Direction direction) {
    Movable::direction = direction;
}

float Movable::getSpeed() const {
    return speed;
}

void Movable::setSpeed(float speed) {
    Movable::speed = speed;
}

float Movable::getFallAcceleration() const {
    return fallAcceleration;
}

void Movable::setFallAcceleration(float fallAcceleration) {
    Movable::fallAcceleration = fallAcceleration;
}

std::string Movable::serialize() {
    return Entity::serialize();
}

Movable::Movable() : Entity() {

}

float Movable::getCost() const {
    return cost;
}

void Movable::setCost(float cost) {
    Movable::cost = cost;
}

void Movable::spawn() {
    System::cash -= this->cost;
    spawned = true;

    if (isAboveGround()) {
        state = S_Falling;
    }
}

void Movable::searchWorkPlace() {
    if (!this->currentWorkPlace && this->isSpawned()) {
        for (auto office:EntityContainer::getOffices()) {
            if (office->hasFreeWorkPlaces() && office->isSpawned()) {
                currentWorkPlace = office;
                office->getWorkers().push_back(this);

                return;
            }
        }
    }
}

bool Movable::isSpawned() const {
    return spawned;
}

int Movable::getFloor() const {
    return floor;
}

void Movable::setFloor(int floor) {
    Movable::floor = floor;
}

bool Movable::isInWorkPlace() {
    int delta = 2;

    return
            currentWorkPlace->getFloor() == this->floor &&
            worldCoordinates.x == currentWorkPlace->getWorldCoordinates().x;
}



