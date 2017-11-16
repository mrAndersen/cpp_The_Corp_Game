#ifndef THE_CORP_GAME_DESTINATION_H
#define THE_CORP_GAME_DESTINATION_H

#include <SFML/System/Vector2.hpp>
#include "../System/Enum.h"
#include "../Component/Elevator.h"
#include "../System/System.h"
#include "../Background/Ground.h"
#include "../Characters/Clerk.h"

class Elevator;

class Movable;

class Clerk;

class Manager;

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

    static Destination createElevatorWaitingDST(Elevator *elevator, Movable *movable);

    static Destination createElevatorExitingDST(Elevator *elevator, Movable *movable, sf::Vector2f finalDestination);

    static Destination createElevatorCabinDST(Elevator *elevator, Movable *movable);

    static Destination createWorkplaceDST(Clerk *movable);

    static Destination createSmokeAreaDST(Movable *movable, sf::Vector2f &smokeArea);

    static Destination createHomeDST(Movable *movable, sf::Vector2f &home);
};


#endif //THE_CORP_GAME_DESTINATION_H
