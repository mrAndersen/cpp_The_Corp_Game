#ifndef THE_CORP_GAME_CHAIR_H
#define THE_CORP_GAME_CHAIR_H

#include "..\Basic\Entity.h"

class Chair : public Entity {

    const static int width = 53;
    const static int height = 89;

public:
    explicit Chair(sf::Vector2f coordinates);

};


#endif //THE_CORP_GAME_CHAIR_H
