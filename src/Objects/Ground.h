#ifndef THE_CORP_GAME_GROUND_H
#define THE_CORP_GAME_GROUND_H

#include "Animation/Entity.h"

class Ground : public Entity {
public:
    const static int textureWidth = 578;
    const static int textureHeight = 100;

    const static int width = 578;
    const static int height = 100;

    explicit Ground(sf::Vector2f coordinates);

};

#endif //THE_CORP_GAME_GROUND_H
