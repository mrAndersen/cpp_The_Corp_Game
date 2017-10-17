#ifndef THE_CORP_GAME_ELEVATORSHAFTTOP_H
#define THE_CORP_GAME_ELEVATORSHAFTTOP_H


#include "Office/Office.h"

class ElevatorShaftTop : public Entity {

protected:
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
public:
    explicit ElevatorShaftTop(sf::Vector2f coordinates);

    bool hasMiddleShaftOnTheBottom();

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    std::vector<Office *> getNeighborOffices();
};


#endif //THE_CORP_GAME_ELEVATORSHAFTTOP_H
