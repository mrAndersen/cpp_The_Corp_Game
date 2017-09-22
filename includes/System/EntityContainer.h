#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"
#include "../Characters/Clerk.h"

namespace EntityContainer {
    extern std::vector<Entity *> items;

    extern std::vector<sf::VertexArray> verticies;

    std::vector<Entity *> getItems();

    std::vector<Entity *> getSaveable();

    std::vector<Entity *> getOffices();

    void add(Entity *item);

    void remove(Entity *item);

    int size();

    void initGround();

    void initGrid();

    void refreshVertices();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
