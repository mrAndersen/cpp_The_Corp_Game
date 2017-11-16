#ifndef THE_CORP_GAME_ELEVATORCABIN_H
#define THE_CORP_GAME_ELEVATORCABIN_H

#include "../Basic/Entity.h"
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"

class Elevator;

class Movable;

class ElevatorCabin : public Entity {
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
    int capacity = 20;
    int floor = 0;
    int speed = 300;

    std::vector<Movable *> currentPeople;
    Elevator *elevator;

    sf::Text floorIndicator;
    sf::Text capacityIndicator;
public:
    explicit ElevatorCabin(sf::Vector2f coordinates);

    bool hasFreeSpace();

    int getSpeed() const;

    void setSpeed(int speed);

    int getCapacity() const;

    void setCapacity(int capacity);

    const std::vector<Movable *> &getCurrentPeople() const;

    void addMovable(Movable *movable);

    void removeMovable(Movable *movable);

    bool isMovableInside(Movable *movable);

    int getFloor() const;

    void setFloor(int floor);

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    bool isSpawned() const;

    bool isInsideShaftBoundaries();

    void updateLogic() override;

    void updateIndicators();
};


#endif //THE_CORP_GAME_ELEVATORCABIN_H
