#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "../Animation/Entity.h"

class Office : public Entity {
protected:
    int floor = 1;

    float cost = 0;

    bool spawned = false;

    std::vector<Entity *> workers;
public:
    std::vector<Office *> getNeighborOffices();

    float getCost() const;

    void setCost(float cost);

    bool isSpawned() const;

    std::vector<Entity *> &getWorkers();

    void updateLogic();

    void spawn();

    void renderDebugInfo();

    int getFloor() const;

    void setFloor(int floor);

    bool intersectsWith();

    bool hasFreeWorkPlaces();
};

#endif //THE_CORP_GAME_OFFICE_H
