#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"
#include "../Characters/Clerk.h"

namespace EntityContainer {
    extern std::vector<Entity *> items;

    std::vector<Entity *> getItems();

    void add(Entity *item);

    void remove(Entity *item);

    int size();

    void initGround();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
