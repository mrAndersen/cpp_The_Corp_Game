#ifndef THE_CORP_GAME_ELEVATOR_H
#define THE_CORP_GAME_ELEVATOR_H


#include "../Animation/Entity.h"
#include "Office.h"

class ElevatorShaft : public Office {

protected:
    ElevatorShafts type = ElevatorShafts::EL_Middle;

    const static int width = 150;
    const static int height = 150;
public:
    explicit ElevatorShaft(sf::Vector2f coordinates);
};


#endif //THE_CORP_GAME_ELEVATOR_H
