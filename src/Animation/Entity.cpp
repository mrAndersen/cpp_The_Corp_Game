#include <sstream>
#include "Entity.h"
#include "System/System.h"
#include "System/Enum.h"
#include "System/EntityContainer.h"
#include "Objects/Ground.h"

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

void Entity::update() {
    updateLogic();
    updateAnimation();
}

void Entity::updateAnimation() {

    if (frameClock.getElapsedTime().asMicroseconds() >= animationResolution / System::timeFactor) {
        currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;

        frameClock.restart();
    }

    renderDebugInfo();
    renderErrorText();
    renderCurrentFrame();
}

void Entity::renderCurrentFrame() {
    top = worldCoordinates.y + height / 2;
    bottom = worldCoordinates.y - height / 2;
    left = worldCoordinates.x - width / 2;
    right = worldCoordinates.x + width / 2;

    rect.height = height;
    rect.width = width;
    rect.left = (int) left;
    rect.top = (int) top;

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
    valid = true;
    sprite.setColor(sf::Color(255, 255, 255, 96));
}

void Entity::setNormal() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
}

void Entity::setInvalid() {
    valid = false;
    sprite.setColor(sf::Color(255, 0, 0, 255));
}

void Entity::updateLogic() {

    if (selectable && !selected && leftClicked() && !System::spawningUnit) {
        setSelected(true);
    }

    if (selectable && selected && leftClicked() && !System::spawningUnit) {
        setSelected(false);
    }

    if (health <= 0) {
        EntityContainer::remove(this);
    }
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

bool Entity::isAboveGround() {
    return bottom > System::groundLevel + Ground::height;
}

bool Entity::isOnTheGround() {
    int delta = 2;

    return
            bottom - delta < System::groundLevel + Ground::height ||
            bottom + delta < System::groundLevel + Ground::height;
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

int Entity::getDrawOrder() const {
    return drawOrder;
}

void Entity::setDrawOrder(int drawOrder) {
    Entity::drawOrder = drawOrder;
}

void Entity::createAnimationFrames() {
    debugInfo.setFont(*System::debugFont);
    debugInfo.setCharacterSize(10);
    debugInfo.setFillColor(sf::Color::Black);

    errorString.setFont(*System::gameFont);
    errorString.setCharacterSize(16);
    errorString.setFillColor(System::c_red);

    if (!textureHeight) {
        textureHeight = height;
    }

    if (!textureWidth) {
        textureWidth = width;
    }

    sprite.setTexture(*textures[state]);
    sprite.setOrigin(width / 2, height / 2);

    for (int i = 0; i < totalFrames; ++i) {
        sf::IntRect rect(i * textureWidth, 0, textureWidth, textureHeight);
        frames.push_back(rect);
    }

    animationResolution = 1000000 / frames.size();
    sprite.setTextureRect(frames[0]);
}

sf::Text &Entity::getErrorString() {
    return errorString;
}

void Entity::setErrorString(sf::Text &errorString) {
    Entity::errorString = errorString;
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

void Entity::renderErrorText() {
    if (!valid) {
        errorString.setPosition(System::cToGl(worldCoordinates.x - width / 2, worldCoordinates.y + height / 2 + 20));
        System::window->draw(errorString);
    }
}

void Entity::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "id: " + std::to_string(id) + "\n" +
                "name: " + name + "\n" +
                "pos: {" + std::to_string(worldCoordinates.x) + "," + std::to_string(worldCoordinates.y) + "}\n" +
                "left: " + std::to_string(left) + "\n" +
                "right: " + std::to_string(right) + "\n" +
                "top: " + std::to_string(top) + "\n" +
                "bottom: " + std::to_string(bottom) + "\n"
        );
        System::window->draw(debugInfo);
    }
}

const sf::IntRect &Entity::getRect() const {
    return rect;
}

void Entity::setRect(const sf::IntRect &rect) {
    Entity::rect = rect;
}

sf::Texture *Entity::getTexture(States state) {
    if (!textures.count(state)) {
        throw std::invalid_argument("Unable to get texture for state");
    }

    return textures[state];
}

void Entity::setTexture(sf::Texture *texture, States state) {
    textures[state] = texture;
}

Entity::Entity() {
    System::entitySequence++;
    id = System::entitySequence;
}

States Entity::getState() const {
    return state;
}

void Entity::setState(States state) {
    Entity::state = state;
}

int Entity::getId() const {
    return id;
}

void Entity::setId(int id) {
    Entity::id = id;
}

bool Entity::isValid() const {
    return valid;
}

bool Entity::isSelected() const {
    return selected;
}

void Entity::setSelected(bool selected) {
    Entity::selected = selected;

    if (selected) {
        sprite.setColor(sf::Color(0, 0, 0, 200));
    } else {
        setNormal();
    }
}

bool Entity::isSelectable() const {
    return selectable;
}

void Entity::setSelectable(bool selectable) {
    Entity::selectable = selectable;
}


