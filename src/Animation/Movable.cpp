#include <cmath>
#include <iostream>
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
    if (System::debug) {
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "id: " + std::to_string(id) + "\n" +
                "pos: {" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) +
                "}\n" +
                "left: " + std::to_string((int) left) + "," +
                "right: " + std::to_string((int) right) + "," +
                "top: " + std::to_string((int) top) + "," +
                "bottom: " + std::to_string((int) bottom) + "\n" +
                "office: " + std::to_string(currentWorkPlace ? currentWorkPlace->getId() : 0) + "\n" +
                "state: " + std::to_string(state) + "\n" +
                "floor: " + std::to_string(floor) + "\n" +
                "speed: " + std::to_string((int) currentSpeed) + "p/s\n"
        );
        System::window->draw(debugInfo);
    }
}

void Movable::updateAnimation() {
    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * currentSpeed * System::timeFactor;

    if (direction == Direction::Down && state == S_Falling) {
        worldCoordinates.y -= frameDistance;
        currentSpeed = currentSpeed + fallAcceleration * frameTimeSeconds;
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

//    if(isOnTheGround()){
//        EntityContainer::remove(this);
//    }

    //no work place
    if (!currentWorkPlace && isOnTheGround()) {
        valid = false;

        errorString.setString("No free work places");
        state = S_None;
    }else{
        valid = true;
    }

    //end of work day
    if (!System::gameTime.isWorkTime()) {
        state = S_GoHome;
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

    if (state == S_Working) {
        direction = Direction::None;
    }

    //go to office
    if (state == S_GoToOffice && currentWorkPlace) {

        if (isInWorkPlace()) {
            state = S_Working;
        } else {
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
    }

    if (state == S_GoToElevator) {

    }

    //not working - but should
    if (
            currentWorkPlace &&
            System::gameTime.isWorkTime() &&
            state != S_Working
            ) {
        state = S_GoToOffice;
        currentSpeed = defaultSpeed * System::timeFactor;
    }

    //search workplace every 500ms
    if (!currentWorkPlace && isOnTheGround() && workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
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

float Movable::getCurrentSpeed() const {
    return currentSpeed;
}

void Movable::setCurrentSpeed(float currentSpeed) {
    Movable::currentSpeed = currentSpeed;
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

float Movable::getDefaultSpeed() const {
    return defaultSpeed;
}

void Movable::setDefaultSpeed(float defaultSpeed) {
    Movable::defaultSpeed = defaultSpeed;
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
    return
            currentWorkPlace &&
            floor == currentWorkPlace->getFloor() &&
            (int) worldCoordinates.x == (int) currentWorkPlace->getWorldCoordinates().x;
}



