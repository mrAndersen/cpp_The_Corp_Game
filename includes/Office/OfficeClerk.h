#ifndef THE_CORP_GAME_OFFICECLERK_H
#define THE_CORP_GAME_OFFICECLERK_H

#include "../Animation/Movable.h"

class OfficeClerk: public Office {
public:
    const static int width = 450;
    const static int height = 150;

    explicit OfficeClerk(sf::Vector2f coordinates);

    void updateLogic();

    virtual std::string serialize();
};

#endif //THE_CORP_GAME_OFFICECLERK_H
