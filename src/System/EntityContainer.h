#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "..\Component\Elevator.h"
#include "ResourceLoader.h"
#include "..\Characters\Clerk.h"
#include "..\Office\Office.h"
#include "EntityGroup.h"

namespace EntityContainer {
    extern std::vector<Entity *> items;

    extern std::vector<sf::VertexArray> verticies;

    extern std::vector<Elevator *> elevators;

    std::vector<Entity *> getItems();

    std::vector<Entity *> getSaveable();

    Entity *searchSingleEntityByType(Entities type);

    std::vector<Entity *> searchEntitiesByType(Entities type);

    std::vector<Entity *> searchEntitiesByGroup(EntityGroup group);

    void addElevator(Elevator * elevator);

    std::vector<Elevator *> getElevators();

    void add(Entity *item);

    void sort();

    void remove(Entity *item);

    int size();

    void initBackground();

    void initGrid();

    void refreshVertices();

    void refreshEntities();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
