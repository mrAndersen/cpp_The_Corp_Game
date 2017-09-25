#ifndef THE_CORP_GAME_MOVABLE_H
#define THE_CORP_GAME_MOVABLE_H

#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../System/Enum.h"
#include "../Office/Office.h"


class Movable : public Entity {

protected:
    float distancePassed = 0;
    Direction direction = Direction::Right;

    //pixels per second
    float speed = 0;
    float fallAcceleration = 980;

    Office *currentWorkPlace;

    //attr
    float cost = 0;

    bool hasReachedWorldEdges();

    void updateLogic();

    void renderCurrentFrame();

public:
    Movable();

    Direction getDirection() const;

    void spawn();

    float getCost() const;

    void setCost(float cost);

    void setDirection(Direction direction);

    float getSpeed() const;

    void setSpeed(float speed);

    float getFallAcceleration() const;

    void setFallAcceleration(float fallAcceleration);

    Office *searchWorkPlace();

    std::string serialize();
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
