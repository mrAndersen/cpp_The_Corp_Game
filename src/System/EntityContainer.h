#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "ResourceLoader.h"
#include "Animation/Movable.h"
#include "Characters/Clerk.h"
#include "Office/Office.h"

namespace EntityContainer {
    extern std::vector<Entity *> items;

    extern std::vector<sf::VertexArray> verticies;

    std::vector<Entity *> getItems();

    std::vector<Entity *> getSaveable();

    std::vector<Office *> getOffices();

    std::vector<Entity *> getElevatorShafts();

    void add(Entity *item);

    void remove(Entity *item);

    int size();

    void initGround();

    void initGrid();

    void refreshVertices();

    void refreshEntities();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
