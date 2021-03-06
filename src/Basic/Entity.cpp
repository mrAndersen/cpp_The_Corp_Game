#include <sstream>
#include <iostream>
#include "Entity.h"
#include "../System/System.h"
#include "../System/Enum.h"
#include "../System/EntityContainer.h"
#include "../Background/Ground.h"
#include "../Characters/Clerk.h"
#include "../Characters/Manager.h"
#include "../Characters/Accountant.h"

void Entity::update() {
    if (visible) {
        selectAnimation(state);

        if (currentAnimation) {
            currentAnimation->update();
        }

        renderDebugInfo();
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
        currentAnimation->getSprite().setColor(System::c_red);
    }
}

void Entity::updateLogic() {
    recalculateBoundaries();
}

const sf::Vector2f &Entity::getWorldCoordinates() const {
    return worldCoordinates;
}

void Entity::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    Entity::worldCoordinates = worldCoordinates;
}

bool Entity::isBelowGround() {
    return bottom < 0 + Ground::height;
}

bool Entity::isAboveGround() {
    return bottom > 0 + Ground::height;
}


bool Entity::isOnTheGround(int delta) {

    return
            bottom - delta < 0 + Ground::height ||
            bottom + delta < 0 + Ground::height;
}

bool Entity::intersectsWithObjects() {
    std::vector<Office *> result;
    std::vector<Entity *> offices = EntityContainer::getGroupItems("offices");
    std::vector<Entity *> shafts = EntityContainer::getGroupItems("shafts");

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
    if (resort) {
        EntityContainer::sortNextFrame = true;
    }
}

void Entity::initEntity() {
    debugInfo.setFont(*System::textFont);
    debugInfo.setCharacterSize(10);
    debugInfo.setFillColor(sf::Color::Black);

    selectAnimation(S_None);
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

void Entity::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
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
    System::selectionCooldown.restart();

    if (selected) {
        setHovered();
    } else {
        setNormal();
    }
}

void Entity::setNormal() {
    if (currentAnimation) {
        currentAnimation->getSprite().setColor(sf::Color(255, 255, 255, 255));
    }
}

void Entity::setHovered() {
    if (currentAnimation) {
        currentAnimation->getSprite().setColor(System::c_green);
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
    States targetState;

    if (!animations.empty()) {
        if (!animations.count(state)) {
            if (!animations.count(S_None)) {
                targetState = S_Button_Normal;
            } else {
                targetState = S_None;
            }
        } else {
            targetState = state;
        }

        //None swap animation logic
        if (groupName == "movable" && targetState == S_None) {
            if (lastNoneSwapAnimation.getElapsedTime().asSeconds() >= 10 / System::timeFactor) {
                lastNoneSwapAnimation.restart();

                auto rnd = System::getRandom(0, 100);

                if (rnd >= 50) {
                    targetState = S_None;
                } else {
                    targetState = S_Play;
                }

                lastNoneSwapAnimationState = targetState;
            } else {
                targetState = lastNoneSwapAnimationState;
            }
        }

        currentAnimation = &animations.at(targetState);
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

const std::string &Entity::getGroupName() const {
    return groupName;
}

void Entity::setGroupName(const std::string &groupName) {
    Entity::groupName = groupName;
}

Entity::~Entity() {
    if (System::debug) {
        System::debugCounters["e_dtor_calls"]++;
    }
}

bool Entity::isOnTheFloor() {
    return (int) bottom % 150 == 100;
}

bool Entity::operator<(const Entity &a) const {
    if (drawOrder == a.getDrawOrder()) {
        return drawOrder + worldCoordinates.x + worldCoordinates.y <
               a.getDrawOrder() + a.getWorldCoordinates().x + a.getWorldCoordinates().y;
    } else {
        return drawOrder < a.getDrawOrder();
    }
}

bool Entity::isManualUpdate() const {
    return manualUpdate;
}

void Entity::setManualUpdate(bool manualUpdate) {
    Entity::manualUpdate = manualUpdate;
}

Entity *Entity::create(Entities type, DrawOrder order, sf::Vector2f size, sf::Vector2f coordinates, const std::string &texturePath, float scale) {
    auto e = new Entity(type);

    e->setDrawOrder(order);
    e->setWidth(size.x);
    e->setHeight(size.y);

    e->setWorldCoordinates(coordinates);
    e->addAnimation(S_None, Animation(e, S_None, 1, ResourceLoader::loadAndGetTexture(texturePath)));
    e->initEntity();
    e->getCurrentAnimation()->getSprite().setScale({scale, scale});

    EntityContainer::add(e);
    EntityContainer::addToGroup(e->getGroupName(), e);

    return e;
}

Entity *Entity::create(Entities type, DrawOrder order, sf::Vector2f size, sf::Vector2f coordinates, sf::Texture *texture, float scale) {
    auto e = new Entity(type);

    e->setDrawOrder(order);
    e->setWidth(size.x);
    e->setHeight(size.y);

    e->setWorldCoordinates(coordinates);
    e->addAnimation(S_None, Animation(e, S_None, 1, texture));
    e->initEntity();
    e->getCurrentAnimation()->getSprite().setScale({scale, scale});

    EntityContainer::add(e);
    EntityContainer::addToGroup(e->getGroupName(), e);

    return e;
}

Animation *Entity::getCurrentAnimation() {
    if (currentAnimation) {
        return currentAnimation;
    }

    return nullptr;
}

bool Entity::isSerializable() const {
    return serializable;
}

void Entity::setSerializable(bool serializable) {
    Entity::serializable = serializable;
}

void Entity::setValid(bool valid) {
    Entity::valid = valid;
}

std::map<std::string, sf::String> Entity::getSerializeParameters() {
    std::map<std::string, sf::String> parameters;

    parameters["id"] = std::to_string(id);
    parameters["groupName"] = groupName;
    parameters["visible"] = std::to_string(visible);
    parameters["manualUpdate"] = std::to_string(manualUpdate);
    parameters["valid"] = std::to_string(valid);
    parameters["serializable"] = std::to_string(serializable);
    parameters["worldCoordinates.x"] = std::to_string(worldCoordinates.x);
    parameters["worldCoordinates.y"] = std::to_string(worldCoordinates.y);
    parameters["width"] = std::to_string(width);
    parameters["height"] = std::to_string(height);
    parameters["state"] = std::to_string(state);
    parameters["selectable"] = std::to_string(selectable);
    parameters["drawOrder"] = std::to_string(drawOrder);
    parameters["direction"] = std::to_string(direction);

    return parameters;
}

sf::String Entity::serialize() {
    auto parameters = getSerializeParameters();
    sf::String s;
    int i = 1;

    for (auto &p:parameters) {
        s += p.first + "->" + p.second;
        i++;

        if (i != parameters.size()) {
            s += ',';
        }
    }

    s = "[" + s + "]";

    return s;
}















