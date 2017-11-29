#ifndef THE_CORP_GAME_ELEVATORSHAFTTOP_H
#define THE_CORP_GAME_ELEVATORSHAFTTOP_H

#include "..\Basic\Entity.h"
#include "..\Component\Elevator.h"
#include "..\Office\Office.h"

class Elevator;

class Office;

class ElevatorShaftTop : public Entity {

protected:
    const static int width = 150;
    const static int height = 150;

    float cost = 0;

    Elevator *elevator = nullptr;
public:
    explicit ElevatorShaftTop(sf::Vector2f coordinates);

    Elevator *getElevator() const;

    void setElevator(Elevator *elevator);

    bool hasMiddleShaftOnTheBottom();

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    void updateLogic() override;

    void renderDebugInfo() override;

    std::vector<Office *> getNeighborOffices();

    int getFloor();
};


#endif //THE_CORP_GAME_ELEVATORSHAFTTOP_H
