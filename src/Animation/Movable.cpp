#include <cmath>
#include "../../includes/System/Enum.h"
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"

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
//        sf::RectangleShape skeleton;
//
//        skeleton.setSize(sf::Vector2f(width, height));
//        skeleton.setFillColor(sf::Color::Transparent);
//        skeleton.setOutlineColor(System::red);
//        skeleton.setOrigin(width / 2, height / 2);
//        skeleton.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y));
//        skeleton.setOutlineThickness(2);
//        System::window->draw(skeleton);

//        sf::Text debugString;
//        debugString.setString(
//                "{" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) + "}" +
//                "[h=" + std::to_string((int) health) + "]" +
//                "[t=" + std::to_string((int) liveClock.getElapsedTime().asSeconds()) + "]" +
//                "[v=" + std::to_string((int) speed) + "]"
//        );
//        debugString.setOrigin(width / 2, height / 2);
//        debugString.setFillColor(sf::Color::Black);
//        debugString.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y + 15));
//        debugString.setFont(*System::openSans);
//        debugString.setCharacterSize(10);
//        System::window->draw(debugString);
    }
}

void Movable::updateFrameTime() {
    frameTimeMs = clock.restart().asMilliseconds();
    totalAnimationFrameTimeMs += frameTimeMs;
}

bool Movable::isAnimationResolutionReached() {
    if (totalAnimationFrameTimeMs >= animationResolution) {
        totalAnimationFrameTimeMs = 0;
        return true;
    } else {
        return false;
    }
}

void Movable::createAnimationFrames() {
    sprite.setTexture(*texture);
    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * width, 0, width, height);
        frames.push_back(rect);
    }

    animationResolution = 1000 / frames.size();
    sprite.setTextureRect(frames[0]);
}

void Movable::update() {
    updateAnimation();
    updateLogic();
}

void Movable::updateAnimation() {
    if (isAnimationResolutionReached()) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
    }

    renderCurrentFrame();
    updateFrameTime();
}

bool Movable::clicked(sf::Vector2f targetCoordinates) {

    return false;
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

//    if (liveClock.getElapsedTime().asSeconds() > 10) {
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
        EntityContainer::removeMovable(this);
    }
}

const std::string &Movable::getName() const {
    return name;
}

void Movable::setName(const std::string &name) {
    Movable::name = name;
}

const sf::Vector2f &Movable::getWorldCoordinates() const {
    return worldCoordinates;
}

void Movable::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    Movable::worldCoordinates = worldCoordinates;
}

int Movable::getWidth() const {
    return width;
}

void Movable::setWidth(int width) {
    Movable::width = width;
}

int Movable::getHeight() const {
    return height;
}

void Movable::setHeight(int height) {
    Movable::height = height;
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

float Movable::getScale() const {
    return scale;
}

void Movable::setScale(float scale) {
    Movable::scale = scale;
}

int Movable::getTotalFrames() const {
    return totalFrames;
}

void Movable::setTotalFrames(int totalFrames) {
    Movable::totalFrames = totalFrames;
}

sf::Texture *Movable::getTexture() const {
    return texture;
}

void Movable::setTexture(sf::Texture *texture) {
    Movable::texture = texture;
}