#ifndef THE_CORP_GAME_GROUND_H
#define THE_CORP_GAME_GROUND_H

#include "../Animation/Static.h"

class Ground : public Static {
public:
    const static int width = 100;
    const static int height = 20;

    explicit Ground(sf::Vector2f coordinates);
};

#endif //THE_CORP_GAME_GROUND_H
