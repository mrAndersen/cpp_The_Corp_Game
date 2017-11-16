#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "..\Component\Elevator.h"
#include "..\Office\Office.h"
#include "../Basic/Movable.h"

namespace EntityContainer {

    extern std::vector<sf::VertexArray> verticies;
    extern std::vector<Elevator *> elevators;


    //groups
    extern std::map<std::string, std::vector<Entity *>> itemsByGroup;

    void addToGroup(const std::string &groupName, Entity *target);

    void removeFromGroup(const std::string &groupName, Entity *target);

    std::vector<Entity *> getGroupItems(const std::string &groupName);
    //groups


    //items
    extern std::vector<Entity *> items;

    extern std::vector<Entity *> itemsToRemove;

    void add(Entity *item);

    void remove(Entity *item);

    void sort();
    //items





    std::vector<Entity *> getSaveable();

    void addElevator(Elevator *elevator);

    std::vector<Elevator *> getElevators();


    int size();

    void initBackground();

    void refreshEntities();
}


#endif //THE_CORP_GAME_ENTITYCONTAINER_H
