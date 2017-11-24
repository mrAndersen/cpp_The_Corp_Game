#include "EntityContainer.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::map<std::string, std::vector<Entity *>> itemsByGroup;

    std::vector<Entity *> itemsToRemove = {};

    std::vector<sf::VertexArray> verticies;

    std::vector<Elevator *> elevators;

    bool sortNextFrame = false;

    void addToGroup(const std::string &groupName, Entity *target) {
        if (groupName != "~") {
            itemsByGroup[groupName].push_back(target);
        }
    }

    void removeFromGroup(const std::string &groupName, Entity *target) {
        itemsByGroup[groupName].erase(
                std::remove(itemsByGroup[groupName].begin(), itemsByGroup[groupName].end(), target),
                itemsByGroup[groupName].end());
    }


    std::vector<Elevator *> getElevators() {
        return elevators;
    }

    void add(Entity *item) {
        auto size = items.size();

        if (items.empty()) {
            items.push_back(item);
        }

        for (auto it = items.begin(); it != items.end();) {
            auto e = *it;
            bool position = comparator(item, e);

            if (position) {
                items.insert(it, item);
                break;
            } else {
                it++;
            }
        }


        if (items.size() == size) {
            items.push_back(item);
        }

        addToGroup(item->getGroupName(), item);

        System::debugCounters["vec_size"] = items.size();
        System::debugCounters["vec_capacity"] = items.capacity();
    }

    void sort() {
        std::sort(items.begin(), items.end(), EntityContainer::comparator);
    }

    bool comparator(const Entity *a, const Entity *b) {
        if (a == b) {
            return false;
        }

        if (a->getDrawOrder() == b->getDrawOrder()) {
            return a->getDrawOrder() + a->getWorldCoordinates().x + a->getWorldCoordinates().y <
                   b->getDrawOrder() + b->getWorldCoordinates().x + b->getWorldCoordinates().y;
        } else {
            return a->getDrawOrder() < b->getDrawOrder();
        }
    }

    void remove(Entity *item) {
        if (std::find(itemsToRemove.cbegin(), itemsToRemove.cend(), item) == itemsToRemove.cend()) {
            itemsToRemove.push_back(item);
        }
    }

    int size() {
        return items.size();
    }

    void initBackground() {
        int before = 0;
        int after = System::worldWidth;

        int nextFieldBorder = 0;
        int nextTreeBorder = 0;

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

            //far trees
            if (before == nextTreeBorder) {
                auto rnd = System::getRandom(0, 100);

                if (rnd <= 50) {
                    Entity::create(E_Entity, D_BG_Trees, {1438, 346}, {(float) i + 1438 / 2, Ground::height + 346 / 2}, "resources/background/bg.forest1.png");
                    nextTreeBorder += 1438;
                } else {
                    Entity::create(E_Entity, D_BG_Trees, {2124, 448}, {(float) i + 2124 / 2, Ground::height + 448 / 2}, "resources/background/bg.forest2.png");
                    nextTreeBorder += 2124;
                }
            }

            //close fields
            if(before == nextFieldBorder) {
                auto rnd2 = System::getRandom(0, 100);

                if (rnd2 <= 50) {
                    Entity::create(E_Entity, D_BG_Field_2, {1592, 756}, {(float) i + 1592 / 2, Ground::height + 756 / 2}, "resources/background/bg.field1.png");
                    nextFieldBorder += 1592;
                }

                if (rnd2 > 33 && rnd2 <= 66) {
                    Entity::create(E_Entity, D_BG_Field_2, {1740, 584}, {(float) i + 1740 / 2, Ground::height + 584 / 2}, "resources/background/bg.field2.png");
                    nextFieldBorder += 1740;
                }
            }

            //far fields
            if(before % 2452 == 0){
                auto rnd3 = System::getRandom(0, 100);

                if(rnd3 <= 50){
                    Entity::create(E_Entity, D_BG_Field_1, {2452, 906}, {(float) i + 2452 / 2, Ground::height + 906 / 2}, "resources/background/bg.far_field1.png");
                }

                if(rnd3 > 50){
                    Entity::create(E_Entity, D_BG_Field_1, {2452, 672}, {(float) i + 2452 / 2, Ground::height + 672 / 2}, "resources/background/bg.far_field2.png");
                }
            }

            //small mountains
            if(System::getRandom(0, 20000) <= 25){
                auto rnd4 = System::getRandom(0, 100);
                int mountainOffset = 500;

                if (rnd4 <= 25) {
                    auto size = sf::Vector2f(1250, 818);
                    Entity::create(E_Entity, D_BG_Mountain_2, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_small1.png");
                }

                if (rnd4 > 25 && rnd4 <= 50) {
                    auto size = sf::Vector2f(968, 752);
                    Entity::create(E_Entity, D_BG_Mountain_2, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_small2.png");
                }

                if (rnd4 > 50 && rnd4 <= 75) {
                    auto size = sf::Vector2f(852, 660);
                    Entity::create(E_Entity, D_BG_Mountain_2, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_small3.png");
                }

                if (rnd4 > 75) {
                    auto size = sf::Vector2f(814, 690);
                    Entity::create(E_Entity, D_BG_Mountain_2, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_small4.png");
                }
            }

            //big mountains
            if(System::getRandom(0, 20000) <= 15){
                auto rnd4 = System::getRandom(0, 100);
                int mountainOffset = 500;

                if (rnd4 <= 33) {
                    auto size = sf::Vector2f(1964, 932);
                    Entity::create(E_Entity, D_BG_Mountain_1, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_large1.png");
                }

                if (rnd4 > 33 && rnd4 <= 66) {
                    auto size = sf::Vector2f(1390, 780);
                    Entity::create(E_Entity, D_BG_Mountain_1, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_large2.png");
                }

                if (rnd4 > 66) {
                    auto size = sf::Vector2f(1786, 900);
                    Entity::create(E_Entity, D_BG_Mountain_1, size, {(float) i + size.x / 2, mountainOffset + Ground::height + size.y / 2}, "resources/background/bg.mountain_large3.png");
                }
            }


            //trees
            if (System::getRandom(0, 20000) <= 50 && i < System::worldWidth / 2 - Tree::width) {
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
                auto yrnd = System::getRandom((int) (System::groundLevel + 55 / 2), (int) (System::groundLevel + Ground::height - 55 / 2 - 35));
                new GroundArtifact({(float) i, (float) yrnd}, {81, 55}, E_StaticGroundArtifact_1);
            }

            before++;
            after--;
        }













    }

    void refreshEntities() {
        System::window->clear(System::c_background);

        int startSize = items.size();

        for (int i = 0; i < startSize; ++i) {
            Entity *e = items[i];

            if (!e->isManualUpdate()) {
                e->update();
            }
        }

        int endSize = items.size();

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

        if (sortNextFrame && startSize == endSize) {
            sort();
            System::debugCounters["sort_operations"]++;
            sortNextFrame = false;
        }

        if (System::debug) {
            System::debugCounters["empty"] = 0;
            for (auto &e:items) {
                System::debugCounters["empty"] =
                        e->getEType() == E_Entity ? System::debugCounters["empty"]++ : System::debugCounters["empty"];
            }

            auto group = EntityContainer::getGroupItems("offices");
            System::debugCounters["free_offices"] = 0;

            for (auto &e:group) {
                auto office = dynamic_cast<Office *>(e);
                System::debugCounters["free_offices"] += (4 - office->getBusyWorkPlaces());
            }
        }
    }

    void addElevator(Elevator *elevator) {
        elevators.push_back(elevator);
    }

    std::vector<Entity *> getGroupItems(const std::string &groupName) {
        return itemsByGroup[groupName];
    }

}

