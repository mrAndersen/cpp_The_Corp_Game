#include <cmath>
#include "../../includes/System/Enum.h"
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"

void Movable::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(System::cToGl(worldCoordinates));
    sprite.setTextureRect(frame);

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
        sprite.setRotation(0);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
        sprite.setRotation(0);
    }

    System::window->draw(sprite);
}

void Movable::updateLogic() {
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



