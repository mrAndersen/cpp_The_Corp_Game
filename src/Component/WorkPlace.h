#ifndef THE_CORP_GAME_WORKPLACE_H
#define THE_CORP_GAME_WORKPLACE_H

#include <Basic/Movable.h>
#include <SFML/System/Vector2.hpp>

class Movable;
class Office;
class WorkPlace {

    sf::Vector2f worldCoordinates;
    Office *parentOffice = nullptr;
    Movable *worker = nullptr;

public:
    explicit WorkPlace(const sf::Vector2f &worldCoordinates);

    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    Office *getParentOffice() const;

    void setParentOffice(Office *parentOffice);

    Movable *getWorker() const;

    void setWorker(Movable *worker);
};


#endif //THE_CORP_GAME_WORKPLACE_H
