#ifndef THE_CORP_GAME_OFFICECLERK_H
#define THE_CORP_GAME_OFFICECLERK_H

#include "../Animation/Entity.h"
#include "Office.h"

class OfficeClerk: public Office {
public:
    const static int width = 300;
    const static int height = 100;

    explicit OfficeClerk(sf::Vector2f coordinates);

    void updateLogic();

    virtual std::string serialize();
};

#endif //THE_CORP_GAME_OFFICECLERK_H
