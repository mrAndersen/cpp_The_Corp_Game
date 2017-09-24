#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "../Animation/Entity.h"

class Office : public Entity {
public:
    int floor = 1;

    std::vector<Office *> getNeighborOffices();

    void updateLogic();

    void renderDebugInfo();

    int getFloor() const;

    void setFloor(int floor);
};

#endif //THE_CORP_GAME_OFFICE_H
