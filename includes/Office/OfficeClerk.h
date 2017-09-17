#ifndef THE_CORP_GAME_OFFICECLERK_H
#define THE_CORP_GAME_OFFICECLERK_H

#include "../Animation/Entity.h"

class OfficeClerk: public Entity {
public:
    const static int width = 250;
    const static int height = 100;

    explicit OfficeClerk(sf::Vector2f coordinates);

    void updateLogic();
};

#endif //THE_CORP_GAME_OFFICECLERK_H