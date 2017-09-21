#ifndef THE_CORP_GAME_MOVABLE_H
#define THE_CORP_GAME_MOVABLE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../System/Enum.h"
#include "Entity.h"

class Movable : public Entity {

protected:
    float distancePassed = 0;
    Direction direction = Direction::Right;

    //pixels per second
    float speed = 0;
    float fallAcceleration = 9832;

    bool hasReachedWorldEdges();

    void updateLogic();

    void renderCurrentFrame();
public:
    Movable();

    Direction getDirection() const;

    void setDirection(Direction direction);

    float getSpeed() const;

    void setSpeed(float speed);

    float getFallAcceleration() const;

    void setFallAcceleration(float fallAcceleration);

    bool isBelowGround();

    std::string serialize();
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
