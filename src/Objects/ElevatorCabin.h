#ifndef THE_CORP_GAME_ELEVATORCABIN_H
#define THE_CORP_GAME_ELEVATORCABIN_H

#include <Animation/Entity.h>

class ElevatorCabin : public Entity {
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
    bool spawned = false;
public:
    ElevatorCabin(sf::Vector2f coordinates);

    float getCost() const;

    void setCost(float cost);

    bool isSpawned() const;

    void setSpawned(bool spawned);
};


#endif //THE_CORP_GAME_ELEVATORCABIN_H
