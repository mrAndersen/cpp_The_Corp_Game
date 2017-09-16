#include <cmath>
#include "../../includes/System/Enum.h"
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Animation/Entity.h"
#include "../../includes/Objects/Ground.h"


Movable::Movable() {
    debugString.setFont(*System::openSans);
    debugString.setFillColor(sf::Color::Black);
    debugString.setCharacterSize(10);
}


void Movable::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(System::convertToGLCoordinates(worldCoordinates));
    sprite.setTextureRect(frame);

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
        sprite.setRotation(0);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
        sprite.setRotation(0);
    }

    if (direction == Direction::Down) {
        sprite.setRotation(45);
    }

    System::window->draw(sprite);

    if (System::animationDebug) {
//        skeleton.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y));
//        System::window->draw(skeleton);
//
        debugString.setFont(*System::openSans);
        debugString.setString(
                "{" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) + "}" +
                "[h=" + std::to_string((int) health) + "]" +
                "[t=" + std::to_string((int) liveClock.getElapsedTime().asSeconds()) + "]" +
                "[v=" + std::to_string((int) speed) + "]"
                "[h=" + std::to_string((int) health) + "]"
        );
        debugString.setPosition(System::convertToGLCoordinates(worldCoordinates.x - width / 2, worldCoordinates.y + height / 2 + 15));
        System::window->draw(debugString);
    }
}

void Movable::updateLogic() {
    float frameDistance = (frameTimeMs / 1000) * speed;

    if (direction == Direction::Right) {

        worldCoordinates.x += frameDistance;
        distancePassed += frameDistance;
    }

    if (direction == Direction::Left) {

        worldCoordinates.x -= (frameTimeMs / 1000) * speed;
        distancePassed += frameDistance;
    }

    if (direction == Direction::Down) {
        //falling

        worldCoordinates.y = worldCoordinates.y - frameDistance;
        speed = speed + fallAcceleration * (frameTimeMs / 1000);
    }

    if (worldCoordinates.y - height / 2 <= System::groundLevel + Ground::height) {
        direction = Direction::Right;
        speed = 300;
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



