#ifndef THE_CORP_GAME_ENTITY_H
#define THE_CORP_GAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "..\System\Enum.h"
#include "Animation.h"

class Animation;

class Movable;

class Entity {

protected:
    //parameters
    Entities eType = E_Entity;
    std::string groupName = "~";
    int id;
    std::map<States, Animation> animations;
    Animation *currentAnimation = nullptr;

    sf::Clock lastNoneSwapAnimation;
    States lastNoneSwapAnimationState = S_None;

    bool visible = true;
    bool manualUpdate = false;

    float health = 100;
    bool valid = true;

    sf::Vector2f worldCoordinates;
    int width = 0;
    int height = 0;

    float top = 0;
    float bottom = 0;
    float left = 0;
    float right = 0;

    States state = S_None;
    bool selected = false;
    bool selectable = false;
    bool spawned = false;

    sf::IntRect rect;

    //animation properties
    int drawOrder = 1;
    Direction direction = Direction::None;

    sf::Clock liveClock;

    //property map
    std::map<std::string, int> properties;

    //debug
    sf::Text debugInfo;
    sf::Text errorString;
public:
    virtual void spawn();

    bool isManualUpdate() const;

    void setManualUpdate(bool manualUpdate);

    virtual bool operator<(const Entity &a) const;

    virtual ~Entity();

    const std::string &getGroupName() const;

    void setGroupName(const std::string &groupName);

    bool isVisible() const;

    void setVisible(bool visible);

    Entity(Entities type = E_Entity);

    Entities getEType() const;

    void setEType(Entities eType);

    Direction getDirection() const;

    void setDirection(Direction direction);

    void addAnimation(States state, const Animation &animation);

    void selectAnimation(States state);

    bool isSpawned();

    bool isSelectable() const;

    void setSelectable(bool selectable);

    bool isSelected() const;

    bool isValid() const;

    int getId() const;

    void setId(int id);

    States getState() const;

    void setState(States state);

    const sf::IntRect &getRect() const;

    void setRect(const sf::IntRect &rect);

    float getTop() const;

    void setTop(float top);

    float getBottom() const;

    void setBottom(float bottom);

    float getLeft() const;

    void setLeft(float left);

    float getRight() const;

    void setRight(float right);

    virtual void update();

    bool isBelowGround();

    bool isAboveGround();

    bool isOnTheFloor();

    bool isOnTheGround();

    bool intersectsWithObjects();

    bool mouseIn();

    bool leftClicked();

    bool rightClicked();

    bool leftClickedOutside();

    bool rightClickedOutside();

    void setTransparent();

    void setNormal();

    virtual void updateLogic();

    void recalculateBoundaries();

    int getDrawOrder() const;

    void setDrawOrder(int drawOrder, bool resort = false);

    float getHealth() const;

    void setHealth(float health);

    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const sf::Clock &getLiveClock() const;

    void setLiveClock(const sf::Clock &liveClock);

    void setInvalid();

    virtual std::string serialize();

    void initEntity();

    virtual void renderDebugInfo();

    virtual void renderErrorText();

    sf::Text &getErrorString();

    void setErrorString(sf::Text &errorString);

    void setSelected(bool selected);
};

#endif //THE_CORP_GAME_ENTITY_H
