#ifndef THE_CORP_GAME_ELEVATOR_H
#define THE_CORP_GAME_ELEVATOR_H

#include <deque>
#include <vector>
#include <SFML/System/Clock.hpp>
#include "../System/Enum.h"

class ElevatorShaftMiddle;

class ElevatorShaftTop;

class ElevatorCabin;

class Elevator {
    int boarding = 0;

    float top = 0;
    float left = 0;
    float right = 0;

    ElevatorCabin *cabin = nullptr;
    std::vector<ElevatorShaftMiddle *> middleShafts;
    ElevatorShaftTop *topShaft = nullptr;

    std::deque<int> queue;
    sf::Clock waitTimer;

    bool waiting = true;
    sf::Clock waitClock;
    Direction direction = Up;

public:
    ElevatorCabin *getCabin() const;

    int getBoarding() const;

    void incBoarding();

    const std::deque<int> &getQueue() const;

    void decBoarding();

    bool isWaiting() const;

    void setWaiting(bool waiting);

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
