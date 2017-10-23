#ifndef THE_CORP_GAME_ELEVATOR_H
#define THE_CORP_GAME_ELEVATOR_H

#include <stack>
#include "Objects/ElevatorCabin.h"
#include "Objects/ElevatorShaftTop.h"
#include "Objects/ElevatorShaftMiddle.h"

class ElevatorShaftTop;
class ElevatorShaftMiddle;
class ElevatorCabin;
class Elevator {

    float top = 0;
    float left = 0;
    float right = 0;

    ElevatorCabin *cabin = nullptr;
    std::vector<ElevatorShaftMiddle *> middleShafts;
    ElevatorShaftTop *topShaft = nullptr;

    std::vector<int> queue;
    sf::Clock waitTimer;
    bool waiting = false;
public:
    ElevatorCabin *getCabin() const;

    void setCabin(ElevatorCabin *cabin);

    float getTop() const;

    void setTop(float top);

    float getLeft() const;

    void setLeft(float left);

    float getRight() const;

    void setRight(float right);

    void addMiddleSection(ElevatorShaftMiddle *shaft);

    void addTopSection(ElevatorShaftTop *shaft);

    void addCabin(ElevatorCabin *cabin);

    void finish();

    void drawDebug();

    void update();

    void addToQueue(int floor);
};


#endif //THE_CORP_GAME_ELEVATOR_H
