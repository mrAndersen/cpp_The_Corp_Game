#ifndef THE_CORP_GAME_ELEVATORSHATFMIDDLE_H
#define THE_CORP_GAME_ELEVATORSHATFMIDDLE_H

#include "..\Basic\Entity.h"
#include "..\Office\Office.h"
#include "..\Component\WorkPlace.h"

class ElevatorShaftMiddle : public Entity {

protected:
    const static int width = 150;
    const static int height = 150;

    float cost = 0;
public:
    explicit ElevatorShaftMiddle(sf::Vector2f coordinates);

    float getCost() const;

    void setCost(float cost);

    void spawn() override;

    bool hasMiddleShaftOnTheBottom();

    std::vector<Office *> getNeighborOffices();
};

#endif