#ifndef THE_CORP_GAME_MOVABLE_H
#define THE_CORP_GAME_MOVABLE_H

#include "Entity.h"
#include "..\Component\Destination.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "..\System\Enum.h"
#include "..\System\GameTime.h"
#include "..\Component\WorkPlace.h"
#include "..\Component\Elevator.h"

class Office;

class WorkPlace;

class Elevator;

class Destination;

class Movable : public Entity {

protected:
    float distancePassed = 0;

    //pixels per second
    float defaultSpeed = 130;
    float currentSpeed = 130;
    float fallAcceleration = 980;

    WorkPlace *currentWorkPlace = nullptr;

    std::deque<Destination> destinations;
    DestinationType currentDST = DST_Unknown;
    bool moving = false;
    Elevator *targetElevator = nullptr;
    sf::Clock lastElevatorSearch;
    int elevatorSearchResolutionSeconds = 5;
    bool smoking = false;
    sf::Clock workPlaceSearchResolution;
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

    WorkPlace *getCurrentWorkPlace() const;

    bool isCrossingShafts();

    void setCurrentWorkPlace(WorkPlace *currentWorkPlace);

    void updateFloor();

    float getFloorBottom(int floor);

    float getFloorBottom(sf::Vector2f coordinates);

    void createWorkPlaceRoute();

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

    void searchWorkPlace();

    Elevator *searchNearestElevator();

    bool isInWorkPlace();

    std::string serialize() override;

    void renderDebugInfo() override;

    float getCurrentSpeed() const;

    void setCurrentSpeed(float currentSpeed);

    float getDefaultSpeed() const;

    void setDefaultSpeed(float defaultSpeed);
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
