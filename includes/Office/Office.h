#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "../Animation/Entity.h"

class Office : public Entity {
public:
    int floor = 1;

    float cost = 0;

    float getCost() const;

    void setCost(float cost);

    std::vector<Office *> getNeighborOffices();

    std::vector<Entity *> workers;

    void updateLogic();

    void spawn();

    void renderDebugInfo();

    int getFloor() const;

    void setFloor(int floor);

    bool intersectsWith();

    bool hasFreeWorkPlaces();
};

#endif //THE_CORP_GAME_OFFICE_H
