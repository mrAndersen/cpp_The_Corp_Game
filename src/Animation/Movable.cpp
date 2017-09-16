#include <cmath>
#include "../../includes/System/Enum.h"
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Animation/Entity.h"

void Movable::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(System::convertToGLCoordinates(worldCoordinates));
    sprite.setTextureRect(frame);

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
    }

    System::window->draw(sprite);

    if (System::animationDebug) {
        skeleton.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y));
        System::window->draw(skeleton);
//
        debugString.setString(
                "{" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) + "}" +
                "[h=" + std::to_string((int) health) + "]" +
                "[t=" + std::to_string((int) liveClock.getElapsedTime().asSeconds()) + "]" +
                "[v=" + std::to_string((int) speed) + "]"
        );
        debugString.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y + 15));
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

//    if (liveClock.getElapsedTime().asSeconds() > 4) {
//        health = 0;
//    }

//    if ((worldCoordinates.y - height / 2 <= System::groundLevel) && speed < 350) {
//        direction = Direction::Right;
//        speed = 300;
//    }
//
//    if (worldCoordinates.y - height / 2 <= System::groundLevel && speed > 350) {
//        health = 0;
//    }

    if (health <= 0) {
        EntityContainer::remove(this);
    }
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
