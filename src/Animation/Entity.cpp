#include <sstream>
#include "../../includes/Animation/Entity.h"
#include "../../includes/System/System.h"
#include "../../includes/System/Enum.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"

std::string Entity::serialize() {
    std::map<int, std::string> parameters;
    std::string serialized;

    parameters[1] = std::to_string(E_Entity);
    parameters[2] = name;
    parameters[3] = std::to_string(health);
    parameters[4] = std::to_string(worldCoordinates.x) + "." + std::to_string(worldCoordinates.y);
    parameters[5] = std::to_string(width);
    parameters[6] = std::to_string(height);
    parameters[7] = std::to_string(totalFrames);
    parameters[8] = std::to_string(currentFrame);
    parameters[9] = std::to_string(drawOrder);
    parameters[10] = std::to_string(liveClock.getElapsedTime().asMicroseconds());
    parameters[11] = std::to_string(animationResolution);

    for (const auto &node:parameters) {
        serialized += std::to_string(node.first) + ":" + node.second + "|";
    }

    return serialized;
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
    updateLogic();
    updateAnimation();
}

void Entity::updateAnimation() {
    if (isAnimationResolutionReached()) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
    }


    renderDebugInfo();
    renderCurrentFrame();
    updateFrameTime();
}

void Entity::renderCurrentFrame() {
    top = worldCoordinates.y + height / 2;
    bottom = worldCoordinates.y - height / 2;
    left = worldCoordinates.x - width / 2;
    right = worldCoordinates.x + width / 2;

    rect.height = height;
    rect.width = width;
    rect.left = left;
    rect.top = top;

    auto frame = frames[currentFrame];

    sprite.setPosition(System::cToGl(worldCoordinates));
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

void Entity::setInvalid() {
    sprite.setColor(sf::Color(255, 0, 0, 255));
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

bool Entity::isBelowGround() {
    return bottom < System::groundLevel + Ground::height;
}

bool Entity::isOnTheGround() {
    return bottom == System::groundLevel + Ground::height;
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

void Entity::createAnimationFrames() {
    info.setFont(*System::openSans);
    info.setCharacterSize(10);
    info.setFillColor(sf::Color::Black);

    if (!textureHeight) {
        textureHeight = height;
    }

    if (!textureWidth) {
        textureWidth = width;
    }

    sprite.setTexture(*texture);
    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * textureWidth, 0, textureWidth, textureHeight);
        frames.push_back(rect);
    }

    animationResolution = 1000 / frames.size();
    sprite.setTextureRect(frames[0]);
}

int Entity::getTextureWidth() const {
    return textureWidth;
}

void Entity::setTextureWidth(int textureWidth) {
    Entity::textureWidth = textureWidth;
}

int Entity::getTextureHeight() const {
    return textureHeight;
}

void Entity::setTextureHeight(int textureHeight) {
    Entity::textureHeight = textureHeight;
}

std::vector<std::string> Entity::getTypeTree() {
    std::vector<std::string> result;
    std::istringstream iss(name);

    for (std::string token; std::getline(iss, token, '.');) {
        result.push_back(std::move(token));
    }

    return result;
}

bool Entity::hasType(const std::string &typeName) {
    auto types = getTypeTree();

    for (const auto &type:types) {
        if (type == typeName) {
            return true;
        }
    }

    return false;
}

float Entity::getTop() const {
    return top;
}

void Entity::setTop(float top) {
    Entity::top = top;
}

float Entity::getBottom() const {
    return bottom;
}

void Entity::setBottom(float bottom) {
    Entity::bottom = bottom;
}

float Entity::getLeft() const {
    return left;
}

void Entity::setLeft(float left) {
    Entity::left = left;
}

float Entity::getRight() const {
    return right;
}

void Entity::setRight(float right) {
    Entity::right = right;
}

const sf::FloatRect &Entity::getRect() const {
    return rect;
}

void Entity::setRect(const sf::FloatRect &rect) {
    Entity::rect = rect;
}

void Entity::renderDebugInfo() {
    if (System::animationDebug) {
        info.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        info.setString(
                "pos: {" + std::to_string(worldCoordinates.x) + "," + std::to_string(worldCoordinates.y) + "}\n" +
                "left: " + std::to_string(left) + "\n" +
                "right: " + std::to_string(right) + "\n" +
                "top: " + std::to_string(top) + "\n" +
                "bottom: " + std::to_string(bottom) + "\n"
        );
        System::window->draw(info);
    }
}
