#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "..\Basic\Entity.h"
#include "..\Basic\Movable.h"
#include "..\Component\WorkPlace.h"

class Movable;
class WorkPlace;
class Office : public Entity {
protected:
    int floor = 1;

    float cost = 0;

    WorkPlace* workPlaces[4];
public:
    Office();

    virtual ~Office();

    WorkPlace *const *getWorkPlaces() const;

    std::vector<Office *> getNeighborOffices();

    float getCost() const;

    void setCost(float cost);

    void updateLogic() override;

    void spawn() override;

    void renderDebugInfo() override;

    int getFloor() const;

    void setFloor(int floor);

    bool hasFreeWorkPlaces();

    void addWorker(Movable * worker);

    int getBusyWorkPlaces();

    WorkPlace* getNextFreeWorkPlace();
};

#endif //THE_CORP_GAME_OFFICE_H
