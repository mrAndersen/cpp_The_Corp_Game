#include "../../includes/System/Enum.h"
#include "../../includes/EntityAnimation/EntityAnimation.h"
#include "../../includes/System/System.h"

void EntityAnimation::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(worldCoordinates);
    sprite.setTextureRect(frame);

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
    }

    System::window->draw(sprite);
}

void EntityAnimation::updateFrameTime() {
    frameTimeMs = clock.restart().asMilliseconds();
    totalAnimationFrameTimeMs += frameTimeMs;
}

bool EntityAnimation::isAnimationResolutionReached() {
    if (totalAnimationFrameTimeMs >= animationResolution) {
        totalAnimationFrameTimeMs = 0;
        return true;
    } else {
        return false;
    }
}

void EntityAnimation::createAnimationFrames() {
    sprite.setTexture(texture);
    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * width, 0, width, height);
        frames.push_back(rect);
    }

    this->animationResolution = 1000 / frames.size();
    this->sprite.setTextureRect(frames[0]);
}

void EntityAnimation::updateAnimation() {
    if (isAnimationResolutionReached()) {
        this->currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
    }

    if (direction == Direction::Right) {
        this->worldCoordinates.x += (frameTimeMs / 1000) * speed;
    }

    if (direction == Direction::Left) {
        this->worldCoordinates.x -= (frameTimeMs / 1000) * speed;
    }

    this->renderCurrentFrame();
    this->updateFrameTime();
}

const std::string &EntityAnimation::getName() const {
    return name;
}

void EntityAnimation::setName(const std::string &name) {
    EntityAnimation::name = name;
}

const sf::Vector2f &EntityAnimation::getWorldCoordinates() const {
    return worldCoordinates;
}

void EntityAnimation::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    EntityAnimation::worldCoordinates = worldCoordinates;
    EntityAnimation::worldCoordinates.y = System::screenHeight - EntityAnimation::worldCoordinates.y;
}

int EntityAnimation::getWidth() const {
    return width;
}

void EntityAnimation::setWidth(int width) {
    EntityAnimation::width = width;
}

int EntityAnimation::getHeight() const {
    return height;
}

void EntityAnimation::setHeight(int height) {
    EntityAnimation::height = height;
}

Direction EntityAnimation::getDirection() const {
    return direction;
}

void EntityAnimation::setDirection(Direction direction) {
    EntityAnimation::direction = direction;
}

float EntityAnimation::getSpeed() const {
    return speed;
}

void EntityAnimation::setSpeed(float speed) {
    EntityAnimation::speed = speed;
}

const sf::Texture &EntityAnimation::getTexture() const {
    return texture;
}

void EntityAnimation::setTexture(const sf::Texture &texture) {
    EntityAnimation::texture = texture;
}
