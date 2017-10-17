#ifndef THE_CORP_GAME_ELEVATOR_H
#define THE_CORP_GAME_ELEVATOR_H

#include "Objects/ElevatorCabin.h"
#include "Objects/ElevatorShaftTop.h"
#include "Objects/ElevatorShaftMiddle.h"

class Elevator {

    float top = 0;
    float left = 0;
    float right = 0;

    ElevatorCabin *cabin = nullptr;
    std::vector<ElevatorShaftMiddle *> middleShafts;
    ElevatorShaftTop *topShaft = nullptr;

public:
    void addMiddleSection(ElevatorShaftMiddle *shaft);

    void addTopSection(ElevatorShaftTop *shaft);

    void addCabin(ElevatorCabin *cabin);

    void finish();
};


#endif //THE_CORP_GAME_ELEVATOR_H
