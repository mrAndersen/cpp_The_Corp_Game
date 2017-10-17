#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "Animation/Entity.h"

class Office : public Entity {
protected:
    int floor = 1;

    float cost = 0;

    std::vector<Entity *> workers;
public:
    Office();

    std::vector<Office *> getNeighborOffices();

    float getCost() const;

    void setCost(float cost);

    std::vector<Entity *> &getWorkers();

    void updateLogic() override;

    void spawn() override;

    void renderDebugInfo() override;

    int getFloor() const;

    void setFloor(int floor);

    bool hasFreeWorkPlaces();
};

#endif //THE_CORP_GAME_OFFICE_H
