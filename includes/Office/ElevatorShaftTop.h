#ifndef THE_CORP_GAME_ELEVATORSHAFTTOP_H
#define THE_CORP_GAME_ELEVATORSHAFTTOP_H


#include "Office.h"

class ElevatorShaftTop : public Office {

protected:
    const static int width = 150;
    const static int height = 150;
public:
    explicit ElevatorShaftTop(sf::Vector2f coordinates);

    bool hasMiddleShaftOnTheBottom();
};


#endif //THE_CORP_GAME_ELEVATORSHAFTTOP_H
