#ifndef THE_CORP_GAME_ELEVATORCABIN_H
#define THE_CORP_GAME_ELEVATORCABIN_H

#include <Basic/Entity.h>

class ElevatorCabin : public Entity {
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
    bool spawned = false;
    int capacity = 10;

    std::vector<Entity *> currentPeople;
public:
    explicit ElevatorCabin(sf::Vector2f coordinates);

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    bool isSpawned() const;

    bool isInsideShaftBoundaries();

    void updateLogic() override;
};


#endif //THE_CORP_GAME_ELEVATORCABIN_H
