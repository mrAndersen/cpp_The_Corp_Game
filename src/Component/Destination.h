#ifndef THE_CORP_GAME_DESTINATION_H
#define THE_CORP_GAME_DESTINATION_H

#include <SFML/System/Vector2.hpp>
#include <functional>
#include <System/Enum.h>
#include <Basic/Movable.h>
#include <System/System.h>

class Destination {
    sf::Vector2f coordinates;
    DestinationType type;
public:
    Destination(const sf::Vector2f &coordinates, DestinationType type = DST_Unknown);

    const sf::Vector2f &getCoordinates() const;

    void setCoordinates(const sf::Vector2f &coordinates);

    DestinationType getType() const;

    void setType(DestinationType type);

    bool reached(Movable *movable);

    int getFloor();
};


#endif //THE_CORP_GAME_DESTINATION_H
