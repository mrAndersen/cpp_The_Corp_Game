#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"
#include "../Characters/Clerk.h"

namespace EntityContainer {
    extern std::vector<Movable *> items;

    std::vector<Movable *> getAll();

    void add(Movable *item);

    void remove(Movable *item);

    int size();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
