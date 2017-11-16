#ifndef THE_CORP_GAME_MOVABLE_H
#define THE_CORP_GAME_MOVABLE_H

#include <cmath>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "..\Text\TextEntity.h"
#include "..\Background\Ground.h"
#include "..\System\EntityContainer.h"
#include "..\System\System.h"
#include "../Component/Destination.h"
#include "../System/EntityContainer.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Movable : public Entity {

protected:
    float distancePassed = 0;

    //pixels per second
    float defaultSpeed = 130;
    float currentSpeed = 130;
    float fallAcceleration = 980;

    std::deque<Destination> destinations;
    DestinationType currentDST = DST_Unknown;
    bool moving = false;
    Elevator *targetElevator = nullptr;
    sf::Clock lastElevatorSearch;
    int elevatorSearchResolutionSeconds = 5;
    bool smoking = false;

    int routeRefreshIntervalSeconds = 5;

    //relevant to game time
    int smokePeriodMinutes = 15;
    GameTime smokeStarted;

    //attr
    float cost = 0;
    int floor = 1;
    std::string personName;

    Gender gender = Gender::G_Male;
    Race race = Race::R_White;

    void updateLogic() override;

public:
    Movable(Entities type, int width, int height);

    bool isCrossingShafts();

    void updateFloor();

    float getFloorBottom(int floor);

    float getFloorBottom(sf::Vector2f coordinates);

    void createSmokeAreaRoute();

    void createHomeRoute();

    sf::Vector2f searchNearestOutside();

    void addAnimation(States state, Gender gender, Race race, int frames = 24, int duration = 1000000);

    Gender getGender() const;

    void setGender(Gender gender);

    const std::string &getPersonName() const;

    void setPersonName(const std::string &personName);

    int getFloor() const;

    void setFloor(int floor);

    bool isSpawned() const;

    void spawn() override;

    float getCost() const;

    void setCost(float cost);

    float getFallAcceleration() const;

    void setFallAcceleration(float fallAcceleration);

    Elevator *searchNearestElevator();

    std::string serialize() override;

    void renderDebugInfo() override;

    float getCurrentSpeed() const;

    void setCurrentSpeed(float currentSpeed);

    float getDefaultSpeed() const;

    void setDefaultSpeed(float defaultSpeed);
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
