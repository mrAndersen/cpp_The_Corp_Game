#ifndef THE_CORP_GAME_GROUND_H
#define THE_CORP_GAME_GROUND_H

#include "../Animation/Entity.h"

class Ground : public Entity {
public:
    const static int width = 129;
    const static int height = 58;

    explicit Ground(sf::Vector2f coordinates);
};

#endif //THE_CORP_GAME_GROUND_H
