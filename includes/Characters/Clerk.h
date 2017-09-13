#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"

class Clerk : public Movable {
public:
    const static int width = 128;
    const static int height = 125;

    explicit Clerk(sf::Vector2f coordinates);
};

#endif //THE_CORP_GAME_CLERK_H
