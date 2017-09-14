#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"
#include "../Characters/Clerk.h"
#include "../Animation/Static.h"

namespace EntityContainer {
    extern std::vector<Movable *> m_items;
    extern std::vector<Static *> s_items;

    std::vector<Movable *> getMovableItems();
    std::vector<Static *> getStaticItems();

    void addMovable(Movable *item);
    void addStatic(Static *item);

    void removeMovable(Movable *item);
    void removeStatic(Static *item);

    int movableSize();
    int staticSize();


    void initGround();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
