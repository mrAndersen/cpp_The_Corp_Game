#ifndef THE_CORP_GAME_ENTITYCONTAINER_H
#define THE_CORP_GAME_ENTITYCONTAINER_H

#include "..\Background\Tree.h"
#include "..\Background\GroundArtifact.h"
#include "..\Background\Ground.h"
#include "..\Component\Elevator.h"
#include "..\Office\Office.h"
#include "../Component/Destination.h"

#include "System.h"

namespace EntityContainer {

    extern std::vector<sf::VertexArray> verticies;

    extern std::vector<Elevator *> elevators;

    extern bool sortNextFrame;

    //groups
    extern std::map<std::string, std::vector<Entity *>> itemsByGroup;

    void addToGroup(const std::string &groupName, Entity *target);

    void removeFromGroup(const std::string &groupName, Entity *target);

    std::vector<Entity *> getGroupItems(const std::string &groupName);
    //groups


    //items
    extern std::map<Scenes, std::vector<Entity *>> items;

    extern std::vector<Entity *> itemsToRemove;

    void add(Entity *item);

    int compareEntity(const void *v_a, const void *v_b);

    void remove(Entity *item);

    void sort();

    bool comparator(const Entity *a, const Entity *b);
    //items


    void addElevator(Elevator *elevator);

    std::vector<Elevator *> getElevators();

    void initMainMenu();

    void initBackground();

    void clearEntities();

    void refreshEntities();

    void handleObjectSelection();
}
#endif //THE_CORP_GAME_ENTITYCONTAINER_H
