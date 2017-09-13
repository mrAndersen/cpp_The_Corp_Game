#include "../../includes/System/Enum.h"
#include "../../includes/EntityAnimation/Movable.h"
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

    if (System::animationDebug) {
        sf::RectangleShape skeleton;

        skeleton.setSize(sf::Vector2f(width, height));
        skeleton.setFillColor(sf::Color::Transparent);
        skeleton.setOutlineColor(System::red);
        skeleton.setPosition(worldCoordinates.x - skeleton.getSize().x / 2,
                             worldCoordinates.y - skeleton.getSize().y / 2);
        skeleton.setOutlineThickness(2);
        System::window->draw(skeleton);

        sf::Text debugString;
        debugString.setString(
                "{" + std::to_string((int)worldCoordinates.x) + "," + std::to_string((int)worldCoordinates.y) + "}" +
                "[" + std::to_string((int)health) + "]"
        );
        debugString.setFillColor(sf::Color::Black);
        debugString.setPosition(worldCoordinates.x - skeleton.getSize().x / 2, worldCoordinates.y - skeleton.getSize().y / 2 - 15);
        debugString.setFont(System::openSans);
        debugString.setCharacterSize(10);
        System::window->draw(debugString);
    }
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

    animationResolution = 1000 / frames.size();
    sprite.setTextureRect(frames[0]);
}

void EntityAnimation::update() {
    updateAnimation();
    updateLogic();
}


void EntityAnimation::updateAnimation() {
    if (isAnimationResolutionReached()) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
    }

    float frameDistance = (frameTimeMs / 1000) * speed;

    if (direction == Direction::Right) {
        worldCoordinates.x += frameDistance;
        distancePassed += frameDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= (frameTimeMs / 1000) * speed;
        distancePassed += frameDistance;
    }

    renderCurrentFrame();
    updateFrameTime();
}

bool EntityAnimation::clicked(sf::Vector2f targetCoordinates) {

    return false;
}

void EntityAnimation::updateLogic() {
    health = 100 - (distancePassed / 300) * 100;


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
    EntityAnimation::worldCoordinates = System::convertToGLCoordinates(worldCoordinates);
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



