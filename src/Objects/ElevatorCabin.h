#ifndef THE_CORP_GAME_ELEVATORCABIN_H
#define THE_CORP_GAME_ELEVATORCABIN_H

#include <Basic/Entity.h>
#include <Basic/Movable.h>

class Movable;
class ElevatorCabin : public Entity {
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
    bool spawned = false;
    int capacity = 10;
    int floor = 1;

    std::vector<Movable *> currentPeople;
public:
    explicit ElevatorCabin(sf::Vector2f coordinates);

    const std::vector<Movable *> &getCurrentPeople() const;

    void addMovable(Movable *movable);

    bool isMovableInside(Movable *movable);

    int getFloor() const;

    void setFloor(int floor);

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    bool isSpawned() const;

    bool isInsideShaftBoundaries();

    void updateLogic() override;
};


#endif //THE_CORP_GAME_ELEVATORCABIN_H
