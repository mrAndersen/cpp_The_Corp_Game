#include "..\Basic\Movable.h"
#include "..\Office\Office.h"
#include "..\Background\Tree.h"
#include "..\Background\GroundArtifact.h"
#include "EntityContainer.h"
#include "..\Background\Ground.h"
#include "System.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::map<std::string, std::vector<Entity *>> itemsByGroup;

    std::vector<Entity *> itemsToRemove = {};

    std::vector<sf::VertexArray> verticies;

    std::vector<Elevator *> elevators;

    void addToGroup(const std::string &groupName, Entity *target) {
        if (groupName != "~") {
            itemsByGroup[groupName].push_back(target);
        }
    }

    void removeFromGroup(const std::string &groupName, Entity *target) {
        itemsByGroup[groupName].erase(std::remove(itemsByGroup[groupName].begin(), itemsByGroup[groupName].end(), target), itemsByGroup[groupName].end());
    }

    std::vector<Entity *> getSaveable() {
        std::vector<Entity *> buffer;

        for (auto entity:items) {
            if (
                    dynamic_cast<Movable *>(entity) ||
                    dynamic_cast<Office *>(entity)
                    ) {
                buffer.push_back(entity);
            }
        }

        return buffer;
    }


    std::vector<Elevator *> getElevators() {
        return elevators;
    }

    void add(Entity *item) {
        items.push_back(item);
        sort();
    }

    void sort() {
        std::sort(items.begin(), items.end(), [](Entity *a, Entity *b) -> bool {
            if (a && b) {
                if (a->getDrawOrder() == b->getDrawOrder()) {
                    return a->getDrawOrder() + a->getWorldCoordinates().x + a->getWorldCoordinates().y <
                           b->getDrawOrder() + b->getWorldCoordinates().x + b->getWorldCoordinates().y;
                } else {
                    return a->getDrawOrder() < b->getDrawOrder();
                }
            } else {
                return false;
            }
        });
    }

    void remove(Entity *item) {
        itemsToRemove.push_back(item);
    }

    int size() {
        return items.size();
    }

    void initBackground() {
        for (int i = (int) -System::worldWidth / 2; i < (int) (System::worldWidth / 2); ++i) {

            //ground
            if ((i % Ground::width) == 0) {
                auto rnd = System::getRandom(0, 100);

                if (rnd <= 33) {
                    new Ground(sf::Vector2f((float) i, System::groundLevel + Ground::height / 2), E_StaticGround_1);
                }

                if (rnd > 33 && rnd <= 66) {
                    new Ground(sf::Vector2f((float) i, System::groundLevel + Ground::height / 2), E_StaticGround_2);
                }

                if (rnd > 66) {
                    new Ground(sf::Vector2f((float) i, System::groundLevel + Ground::height / 2), E_StaticGround_3);
                }
            }

            //trees
            if (System::getRandom(0, 20000) <= 75 && i < System::worldWidth / 2 - Tree::width) {
                auto treeIndex = System::getRandom(0, 100);

                if (treeIndex <= 25) {
                    new Tree({(float) i, System::groundLevel + Ground::height + Tree::height / 2}, E_StaticTree_1);
                }

                if (treeIndex > 25 && treeIndex <= 50) {
                    new Tree({(float) i, System::groundLevel + Ground::height + Tree::height / 2}, E_StaticTree_2);
                }

                if (treeIndex > 50 && treeIndex <= 75) {
                    new Tree({(float) i, System::groundLevel + Ground::height + 449 / 2}, E_StaticTree_3, {361, 449});
                }

                if (treeIndex > 75) {
                    new Tree({(float) i, System::groundLevel + Ground::height + 162 / 2}, E_StaticTree_4, {308, 162});
                }
            }

            //ground artifacts
            if (System::getRandom(0, 20000) <= 15 && i < System::worldWidth / 2 - Tree::width) {
                auto yrnd = System::getRandom((int) (System::groundLevel + 55 / 2),
                                              (int) (System::groundLevel + Ground::height - 55 / 2 - 35));


                new GroundArtifact({(float) i, (float) yrnd}, {81, 55}, E_StaticGroundArtifact_1);
            }
        }
    }

    void refreshEntities() {
        System::window->clear(System::c_background);

        for (auto &entity:items) {
            entity->update();
        }

        if (!itemsToRemove.empty()) {
            for (auto &e:itemsToRemove) {
                //remove if item presents in group
                if (e->getGroupName() != "~") {
                    removeFromGroup(e->getGroupName(), e);
                }

                //remove from actual vector
                items.erase(std::remove(items.begin(), items.end(), e), items.end());

                //free object
                delete e;
            }

            itemsToRemove.clear();
        }

        //@todo debug logic - to remove
        System::debugCounters["empty"] = 0;
        for (auto &e:items) {
            System::debugCounters["empty"] = e->getEType() == E_Entity ? System::debugCounters["empty"]++ : System::debugCounters["empty"];
        }

        auto group = EntityContainer::getGroupItems("offices");
        System::debugCounters["free_offices"] = 0;

        for (auto &e:group) {
            auto office = dynamic_cast<Office *>(e);
            System::debugCounters["free_offices"] += (4 - office->getBusyWorkPlaces());
        }

        //@todo debug logic - to remove
    }

    void addElevator(Elevator *elevator) {
        elevators.push_back(elevator);
    }

    std::vector<Entity *> getGroupItems(const std::string &groupName) {
        return itemsByGroup[groupName];
    }

}

