#include <sstream>
#include <iostream>
#include "Entity.h"
#include "System/System.h"
#include "System/Enum.h"
#include "System/EntityContainer.h"
#include "Background/Ground.h"

std::string Entity::serialize() {


}

void Entity::update() {
    if (visible) {
        selectAnimation(state);

        if (currentAnimation) {
            currentAnimation->update();
        }

        renderDebugInfo();
        renderErrorText();
    }

    updateLogic();
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

    if (currentAnimation) {
        currentAnimation->getSprite().setColor(sf::Color(255, 255, 255, 96));
    }
}


void Entity::setInvalid() {
    valid = false;
    if (currentAnimation) {
        currentAnimation->getSprite().setColor(sf::Color(255, 0, 0, 255));
    }
}

void Entity::updateLogic() {
    frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    recalculateBoundaries();
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
    int delta = 3;

    return
            bottom - delta < System::groundLevel + Ground::height ||
            bottom + delta < System::groundLevel + Ground::height;
}

bool Entity::intersectsWithObjects() {
    std::vector<Office *> result;
    std::vector<Entity *> offices = EntityContainer::searchEntitiesByGroup(System::officeGroup);
    std::vector<Entity *> shafts = EntityContainer::searchEntitiesByGroup(System::elevatorShafts);

    for (auto target:offices) {
        if (this != target) {
            if (this->rect.intersects(target->getRect())) {
                return true;
            }
        }
    }

    for (auto target:shafts) {
        if (this != target) {
            if (this->rect.intersects(target->getRect())) {
                return true;
            }
        }
    }

    return false;
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

const sf::Clock &Entity::getLiveClock() const {
    return liveClock;
}

void Entity::setLiveClock(const sf::Clock &liveClock) {
    Entity::liveClock = liveClock;
}

int Entity::getDrawOrder() const {
    return drawOrder;
}

void Entity::setDrawOrder(int drawOrder, bool resort) {
    Entity::drawOrder = drawOrder;
//    if (resort) {
//        EntityContainer::sort();
//    }
}

void Entity::initEntity() {
    debugInfo.setFont(*System::debugFont);
    debugInfo.setCharacterSize(10);
    debugInfo.setFillColor(sf::Color::Black);

    errorString.setFont(*System::gameFont);
    errorString.setCharacterSize(16);
    errorString.setFillColor(System::c_red);

    selectAnimation(S_None);
}

sf::Text &Entity::getErrorString() {
    return errorString;
}

void Entity::setErrorString(sf::Text &errorString) {
    Entity::errorString = errorString;
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
//        debugInfo.setString(
//                "id: " + std::to_string(id) + "\n" +
//                "type: " + std::to_string(eType) + "\n" +
//                "pos: {" + std::to_string(worldCoordinates.x) + "," + std::to_string(worldCoordinates.y) + "}\n" +
//                "left: " + std::to_string(left) + "\n" +
//                "right: " + std::to_string(right) + "\n" +
//                "top: " + std::to_string(top) + "\n" +
//                "bottom: " + std::to_string(bottom) + "\n"
//        );
        System::window->draw(debugInfo);
    }
}

const sf::IntRect &Entity::getRect() const {
    return rect;
}

void Entity::setRect(const sf::IntRect &rect) {
    Entity::rect = rect;
}

Entity::Entity(Entities type) {
    eType = type;

    System::entitySequence++;
    id = System::entitySequence;

    selectAnimation(S_None);
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
        currentAnimation->getSprite().setColor(sf::Color(0, 255, 0, 255));
    } else {
        setNormal();
    }
}

void Entity::setNormal() {
    if (currentAnimation) {
        currentAnimation->getSprite().setColor(sf::Color(255, 255, 255, 255));
    }
}

bool Entity::isSelectable() const {
    return selectable;
}

void Entity::setSelectable(bool selectable) {
    Entity::selectable = selectable;
}

bool Entity::isSpawned() {
    return spawned;
}

void Entity::spawn() {
    liveClock.restart();
    recalculateBoundaries();
    spawned = true;
}

void Entity::addAnimation(States state, const Animation &animation) {
    animations.insert(std::pair<States, Animation>(state, animation));
}


void Entity::selectAnimation(States state) {
    if (!animations.empty()) {
        if (!animations.count(state)) {
            currentAnimation = &animations.find(S_None).operator*().second;
        } else {
            currentAnimation = &animations.find(state).operator*().second;
        }
    }
}

Direction Entity::getDirection() const {
    return direction;
}

void Entity::setDirection(Direction direction) {
    Entity::direction = direction;
}

void Entity::recalculateBoundaries() {
    top = worldCoordinates.y + height / 2;
    bottom = worldCoordinates.y - height / 2;
    left = worldCoordinates.x - width / 2;
    right = worldCoordinates.x + width / 2;

    rect.height = height;
    rect.width = width;
    rect.left = (int) left;
    rect.top = (int) top;
}

Entities Entity::getEType() const {
    return eType;
}

void Entity::setEType(Entities eType) {
    Entity::eType = eType;
}

bool Entity::isVisible() const {
    return visible;
}

void Entity::setVisible(bool visible) {
    Entity::visible = visible;
}

bool Entity::isUpdated() const {
    return updated;
}

void Entity::setUpdated(bool updated) {
    Entity::updated = updated;
}
