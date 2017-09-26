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
                "office: " + std::to_string(currentWorkPlace ? currentWorkPlace->getId() : 0) + "\n"
                        "state: " + std::to_string(state) + "\n"
        );
        System::window->draw(info);
    }
}

void Movable::updateAnimation() {
    float frameDistance = (frameTimeMs / 1000) * speed;

    if (direction == Direction::Down) {
        worldCoordinates.y -= frameDistance;
        speed = speed + fallAcceleration * (frameTimeMs / 1000);
    }

    if (direction == Direction::Right) {
        worldCoordinates.x += frameDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= frameDistance;
    }

    if (isOnTheGround() || isBelowGround()) {
        direction = Direction::None;
        state = S_Smoke;
        smokeStarted = System::gameTime;
    }

    Entity::updateAnimation();
}

void Movable::updateLogic() {

    //Stop smoking
    if (state == S_Smoke && System::gameTime.diffMinutes(smokeStarted) >= smokePeriodMinutes) {
        state = S_GoToOffice;
    }


    if (state == S_GoToOffice && currentWorkPlace) {

    }

    if (state == S_GoToOffice && !currentWorkPlace) {
        direction = Direction::None;
        errorString.setString("No office");
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
    if (workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
        searchWorkPlace();
    }

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



