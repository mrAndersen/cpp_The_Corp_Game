#include "../../includes/Animation/Entity.h"
#include "../../includes/System/System.h"
#include "../../includes/System/Enum.h"

void Entity::createAnimationFrames() {
    sprite.setTexture(*texture);
    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * width, 0, width, height);
        frames.push_back(rect);
    }

    animationResolution = 1000 / frames.size();
    sprite.setTextureRect(frames[0]);
}

void Entity::updateFrameTime() {
    frameTimeMs = frameClock.restart().asMilliseconds();
    totalAnimationFrameTimeMs += frameTimeMs;
}

bool Entity::isAnimationResolutionReached() {
    if (totalAnimationFrameTimeMs >= animationResolution) {
        totalAnimationFrameTimeMs = 0;
        return true;
    } else {
        return false;
    }
}

void Entity::update() {
    updateAnimation();
    updateLogic();
}

void Entity::updateAnimation() {
    if (isAnimationResolutionReached()) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
    }

    renderCurrentFrame();
    updateFrameTime();
}

void Entity::renderCurrentFrame() {
    auto frame = frames[currentFrame];

    sprite.setPosition(System::convertToGLCoordinates(worldCoordinates));
    sprite.setTextureRect(frame);

    System::window->draw(sprite);
}

bool Entity::mouseIn() {
    return System::g_x >= worldCoordinates.x - width / 2 &&
        System::g_x <= worldCoordinates.x + width / 2 &&
        System::g_y >= worldCoordinates.y - height / 2 &&
        System::g_y <= worldCoordinates.y + height / 2;
}


bool Entity::leftClicked() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseIn();
}

bool Entity::rightClicked() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && mouseIn();
}

bool Entity::leftClickedOutside() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseIn();
}

bool Entity::rightClickedOutside() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !mouseIn();
}

void Entity::setTransparent() {
    sprite.setColor(sf::Color(255, 255, 255, 96));
}

void Entity::removeTransparency() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
}

void Entity::updateLogic() {
}

const std::string &Entity::getName() const {
    return name;
}

void Entity::setName(const std::string &name) {
    Entity::name = name;
}

float Entity::getHealth() const {
    return health;
}

void Entity::setHealth(float health) {
    Entity::health = health;
}

const sf::Vector2f &Entity::getWorldCoordinates() const {
    return worldCoordinates;
}

void Entity::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    Entity::worldCoordinates = worldCoordinates;
}

int Entity::getWidth() const {
    return width;
}

void Entity::setWidth(int width) {
    Entity::width = width;
}

int Entity::getHeight() const {
    return height;
}

void Entity::setHeight(int height) {
    Entity::height = height;
}

const std::vector<sf::IntRect> &Entity::getFrames() const {
    return frames;
}

void Entity::setFrames(const std::vector<sf::IntRect> &frames) {
    Entity::frames = frames;
}

int Entity::getTotalFrames() const {
    return totalFrames;
}

void Entity::setTotalFrames(int totalFrames) {
    Entity::totalFrames = totalFrames;
}

int Entity::getCurrentFrame() const {
    return currentFrame;
}

void Entity::setCurrentFrame(int currentFrame) {
    Entity::currentFrame = currentFrame;
}

float Entity::getScale() const {
    return scale;
}

void Entity::setScale(float scale) {
    Entity::scale = scale;
}

sf::Sprite &Entity::getSprite() {
    return sprite;
}

void Entity::setSprite(const sf::Sprite &sprite) {
    Entity::sprite = sprite;
}

sf::Texture *Entity::getTexture() const {
    return texture;
}

void Entity::setTexture(sf::Texture *texture) {
    Entity::texture = texture;
}

const sf::Clock &Entity::getLiveClock() const {
    return liveClock;
}

void Entity::setLiveClock(const sf::Clock &liveClock) {
    Entity::liveClock = liveClock;
}

float Entity::getAnimationResolution() const {
    return animationResolution;
}

void Entity::setAnimationResolution(float animationResolution) {
    Entity::animationResolution = animationResolution;
}

float Entity::getTotalAnimationFrameTimeMs() const {
    return totalAnimationFrameTimeMs;
}

void Entity::setTotalAnimationFrameTimeMs(float totalAnimationFrameTimeMs) {
    Entity::totalAnimationFrameTimeMs = totalAnimationFrameTimeMs;
}

float Entity::getFrameTimeMs() const {
    return frameTimeMs;
}

void Entity::setFrameTimeMs(float frameTimeMs) {
    Entity::frameTimeMs = frameTimeMs;
}

int Entity::getDrawOrder() const {
    return drawOrder;
}

void Entity::setDrawOrder(int drawOrder) {
    Entity::drawOrder = drawOrder;
}
