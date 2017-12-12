#ifndef THE_CORP_GAME_DESTINATION_H
#define THE_CORP_GAME_DESTINATION_H

#include <SFML/System/Vector2.hpp>

#include "../System/Enum.h"
#include "../System/System.h"
#include "../Background/Ground.h"

class Elevator;

class Clerk;

class Manager;

class Accountant;

class Destination {
    sf::Vector2f coordinates;
    DestinationType type;
public:
    Destination(const sf::Vector2f &coordinates, DestinationType type = DST_Unknown);

    const sf::Vector2f &getCoordinates() const;

    void setCoordinates(const sf::Vector2f &coordinates);

    DestinationType getType() const;

    void setType(DestinationType type);

    int getFloor();

    sf::String serialize();

    static Destination populate(std::string &data);

    static Destination createElevatorWaitingDST(Elevator *elevator, Movable *movable);

    static Destination createElevatorExitingDST(Elevator *elevator, Movable *movable, sf::Vector2f finalDestination);

    static Destination createElevatorCabinDST(Elevator *elevator, Movable *movable);

    static Destination createWorkplaceDST(Clerk *movable);
    static Destination createWorkplaceDST(Accountant *movable);

    static Destination createBuffPlaceDST(Clerk *movable);
    static Destination createBuffPlaceDST(Accountant *movable);

    static Destination createSmokeAreaDST(Movable *movable, sf::Vector2f &smokeArea);

    static Destination createHomeDST(Movable *movable, sf::Vector2f &home);
};


#endif //THE_CORP_GAME_DESTINATION_H
