#ifndef THE_CORP_GAME_GROUND_H
#define THE_CORP_GAME_GROUND_H

#include "../Animation/Entity.h"

class Ground : public Entity {
public:
    const static int width = 289;
    const static int height = 50;

    explicit Ground(sf::Vector2f coordinates);
};

#endif //THE_CORP_GAME_GROUND_H
