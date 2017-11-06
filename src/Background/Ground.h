#ifndef THE_CORP_GAME_GROUND_H
#define THE_CORP_GAME_GROUND_H

#include "..\Basic\Entity.h"

class Ground : public Entity {
public:
    const static int width = 300;
    const static int height = 100;

    explicit Ground(sf::Vector2f coordinates, Entities type);
};

#endif //THE_CORP_GAME_GROUND_H
