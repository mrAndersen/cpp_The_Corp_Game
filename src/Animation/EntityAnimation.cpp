#include "../../includes/System/Enum.h"
#include "../../includes/EntityAnimation/EntityAnimation.h"
#include "../../includes/System/System.h"

void EntityAnimation::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(x, y);
    sprite.setTextureRect(frame);

    if (direction == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
    }

    if (direction == Direction::Right) {
        sprite.setScale(1.f, 1.f);
    }

    System::window->draw(sprite);
}

bool EntityAnimation::contains(float x, float y) {
    return
            x > this->x &&
            x < x + this->width &&
            y > this->y &&
            y < y + this->height;

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
        this->x += (frameTimeMs / 1000) * speed;
    }

    if (direction == Direction::Left) {
        this->x -= (frameTimeMs / 1000) * speed;
    }

    this->renderCurrentFrame();
    this->updateFrameTime();
}

Direction EntityAnimation::getDirection() const {
    return this->direction;
}

void EntityAnimation::setDirection(Direction direction) {
    this->direction = direction;
}

const std::string &EntityAnimation::getName() const {
    return name;
}

void EntityAnimation::setName(const std::string &name) {
    EntityAnimation::name = name;
}

float EntityAnimation::getX() const {
    return x;
}

void EntityAnimation::setX(float x) {
    EntityAnimation::x = x;
}

float EntityAnimation::getY() const {
    return y;
}

void EntityAnimation::setY(float y) {
    EntityAnimation::y = y;
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

const sf::Sprite &EntityAnimation::getSprite() const {
    return sprite;
}

void EntityAnimation::setSprite(const sf::Sprite &sprite) {
    EntityAnimation::sprite = sprite;
}

const sf::Texture &EntityAnimation::getTexture() const {
    return texture;
}

void EntityAnimation::setTexture(const sf::Texture &texture) {
    EntityAnimation::texture = texture;
}

float EntityAnimation::getAnimationResolution() const {
    return animationResolution;
}

void EntityAnimation::setAnimationResolution(float animationResolution) {
    EntityAnimation::animationResolution = animationResolution;
}

float EntityAnimation::getSpeed() const {
    return speed;
}

void EntityAnimation::setSpeed(float speed) {
    EntityAnimation::speed = speed;
}

