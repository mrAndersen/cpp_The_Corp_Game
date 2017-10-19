#include <System/System.h>
#include "Animation.h"

States Animation::getState() const {
    return state;
}

void Animation::setState(States state) {
    Animation::state = state;
}

const std::vector<sf::IntRect> &Animation::getFrames() const {
    return frames;
}

void Animation::setFrames(const std::vector<sf::IntRect> &frames) {
    Animation::frames = frames;
}

int Animation::getTotalFrames() const {
    return totalFrames;
}

void Animation::setTotalFrames(int totalFrames) {
    Animation::totalFrames = totalFrames;
}

int Animation::getCurrentFrame() const {
    return currentFrame;
}

void Animation::setCurrentFrame(int currentFrame) {
    Animation::currentFrame = currentFrame;
}

float Animation::getScale() const {
    return scale;
}

void Animation::setScale(float scale) {
    Animation::scale = scale;
}

sf::Sprite &Animation::getSprite() {
    return sprite;
}

void Animation::setSprite(const sf::Sprite &sprite) {
    Animation::sprite = sprite;
}

float Animation::getAnimationResolution() const {
    return animationResolution;
}

void Animation::setAnimationResolution(float animationResolution) {
    Animation::animationResolution = animationResolution;
}

sf::Texture *Animation::getTexture() const {
    return texture;
}

void Animation::setTexture(sf::Texture *texture) {
    Animation::texture = texture;
}

Animation::Animation(Entity *entity, States state, int totalFrames, sf::Texture *texture) {
    this->entity = entity;
    this->state = state;
    this->totalFrames = totalFrames;
    this->texture = texture;
    this->width = entity->getWidth();
    this->height = entity->getHeight();

    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * width, 0, width, height);
        frames.push_back(rect);
    }

    animationResolution = 1000000 / totalFrames;
    sprite.setTextureRect(frames[0]);
}

void Animation::update() {
    if (frameClock.getElapsedTime().asMicroseconds() >= animationResolution / System::timeFactor) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;

        frameClock.restart();
    }

    auto frame = frames[currentFrame];

    sprite.setTexture(*texture);
    sprite.setPosition(System::cToGl(entity->getWorldCoordinates()));
    sprite.setTextureRect(frame);

    if (entity->getDirection() == Direction::Left) {
        sprite.setScale(-1.f, 1.f);
        sprite.setRotation(0);
    }

    if (entity->getDirection() == Direction::Right) {
        sprite.setScale(1.f, 1.f);
        sprite.setRotation(0);
    }

    System::window->draw(sprite);
}

Entity *Animation::getEntity() const {
    return entity;
}

void Animation::setEntity(Entity *entity) {
    Animation::entity = entity;
}
