#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "Component/Elevator.h"
#include "ResourceLoader.h"
#include "Characters/Clerk.h"
#include "Office/Office.h"

namespace EntityContainer {
    extern std::vector<Entity *> items;

    extern std::vector<sf::VertexArray> verticies;

    extern std::vector<Elevator *> elevators;

    std::vector<Entity *> getItems();

    std::vector<Entity *> getSaveable();

    std::vector<Office *> getOffices();

    std::vector<Entity *> getElevatorShafts();

    std::vector<Elevator *> getElevators();

    void addElevator(Elevator * elevator);

    void add(Entity *item);

    void resort();

    void remove(Entity *item);

    int size();

    void initGround();

    void initGrid();

    void refreshVertices();

    void refreshEntities();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
