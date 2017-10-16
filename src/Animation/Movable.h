#ifndef THE_CORP_GAME_MOVABLE_H
#define THE_CORP_GAME_MOVABLE_H

#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "System/Enum.h"
#include "Office/Office.h"
#include "System/GameTime.h"


class Movable : public Entity {

protected:
    float distancePassed = 0;
    Direction direction = Direction::Right;

    //pixels per second
    float defaultSpeed = 130;
    float currentSpeed = 130;
    float fallAcceleration = 980;

    Office *currentWorkPlace = nullptr;
    sf::Clock workPlaceSearchResolution;

    //relevant to game time
    int smokePeriodMinutes = 5;
    GameTime smokeStarted;

    //attr
    float cost = 0;
    int floor = 1;
    std::string personName;
    Gender gender = Gender::G_Male;


    bool hasReachedWorldEdges();

    void updateLogic() override;

    void renderCurrentFrame() override;

public:
    Movable();

    Gender getGender() const;

    void setGender(Gender gender);

    const std::string &getPersonName() const;

    void setPersonName(const std::string &personName);

    int getFloor() const;

    void setFloor(int floor);

    bool isSpawned() const;

    Direction getDirection() const;

    void spawn() override;

    float getCost() const;

    void setCost(float cost);

    void setDirection(Direction direction);

    float getFallAcceleration() const;

    void setFallAcceleration(float fallAcceleration);

    void searchWorkPlace();

    bool isInWorkPlace();

    std::string serialize() override;

    void renderDebugInfo() override;

    void updateAnimation() override;

    float getCurrentSpeed() const;

    void setCurrentSpeed(float currentSpeed);

    float getDefaultSpeed() const;

    void setDefaultSpeed(float defaultSpeed);
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
