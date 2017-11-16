#ifndef THE_CORP_GAME_WORKPLACE_H
#define THE_CORP_GAME_WORKPLACE_H

#include "..\Office\Office.h"
#include <SFML/System/Vector2.hpp>

class Office;

class Movable;

class WorkPlace {

    sf::Vector2f worldCoordinates;
    Office *parentOffice = nullptr;
    Movable *worker = nullptr;
    Entity *chair = nullptr;
public:
    WorkPlace(const sf::Vector2f &worldCoordinates, Office *parentOffice);

    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    Office *getParentOffice() const;

    void setParentOffice(Office *parentOffice);

    Movable *getWorker() const;

    void setWorker(Movable *worker);

    void update();

    void drawDebug();
};


#endif //THE_CORP_GAME_WORKPLACE_H
