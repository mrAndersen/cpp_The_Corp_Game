#include <Office/Office.h>
#include <Background/Tree.h>
#include <Background/GroundArtifact.h>
#include "EntityContainer.h"
#include "Background/Ground.h"
#include "System.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::vector<Entity *> itemsToRemove = {};

    std::vector<sf::VertexArray> verticies;

    std::vector<Elevator *> elevators;

    std::vector<Entity *> getItems() {
        return items;
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

    std::vector<Office *> getOffices() {
        std::vector<Office *> buffer;

        for (Entity *entity:items) {
            if (auto d = dynamic_cast<Office *>(entity)) {
                buffer.push_back(d);
            }
        }

        return buffer;
    }

    std::vector<Entity *> getElevatorShafts() {
        std::vector<Entity *> buffer;

        for (Entity *entity:items) {
            if (
                    dynamic_cast<ElevatorShaftMiddle *>(entity) ||
                    dynamic_cast<ElevatorShaftTop *>(entity)) {
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

        std::sort(items.begin(), items.end(), [](Entity *a, Entity *b) -> bool {
            if (a->getDrawOrder() == b->getDrawOrder()) {
                return a->getDrawOrder() + a->getWorldCoordinates().x + a->getWorldCoordinates().y <
                       b->getDrawOrder() + b->getWorldCoordinates().x + b->getWorldCoordinates().y;
            } else {
                return a->getDrawOrder() < b->getDrawOrder();
            }
        });
    }

    void resort() {
        std::sort(items.begin(), items.end(), [](Entity *a, Entity *b) -> bool {
            return a->getDrawOrder() < b->getDrawOrder();
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

                if (rnd <= 50) {
                    new Ground(sf::Vector2f(i, System::groundLevel + Ground::height / 2), E_StaticGround_1);
                } else {
                    new Ground(sf::Vector2f(i, System::groundLevel + Ground::height / 2), E_StaticGround_2);
                }
            }

            //trees
            if (System::getRandom(0, 20000) <= 75 && i < System::worldWidth / 2 - Tree::width) {
                new Tree({(float) i, System::groundLevel + Ground::height + Tree::height / 2}, E_StaticTree_1);
            }

            //ground artifacts
            if (System::getRandom(0, 20000) <= 25 && i < System::worldWidth / 2 - Tree::width) {
                auto yrnd = System::getRandom((int) (System::groundLevel + 55 / 2),
                                              (int) (System::groundLevel + Ground::height - 55 / 2 - 35));


                new GroundArtifact({(float) i, (float) yrnd}, {81, 55}, E_StaticGroundArtifact_1);
            }
        }
    }

    void initGrid() {
        if (System::debug) {
            sf::Color transparentBlack(0, 0, 0, 25);

            for (int i = (int) -System::worldWidth / 2; i < System::worldWidth / 2; i++) {
                if ((i % System::gridSize) == 0) {

                    sf::VertexArray lines;
                    lines.setPrimitiveType(sf::Lines);
                    lines.append(sf::Vertex(System::cToGl(i, 5000), transparentBlack));
                    lines.append(sf::Vertex(System::cToGl(i, System::groundLevel), transparentBlack));

                    verticies.push_back(lines);
                }
            }

            for (int j = 8000; j > System::groundLevel; j--) {
                if ((j % System::gridSize) == 0) {
                    sf::VertexArray lines;
                    lines.setPrimitiveType(sf::Lines);
                    lines.append(sf::Vertex(System::cToGl(-System::worldWidth / 2, j), transparentBlack));
                    lines.append(sf::Vertex(System::cToGl(System::worldWidth / 2, j), transparentBlack));

                    verticies.push_back(lines);
                }
            }
        }
    }

    void refreshVertices() {
        for (const auto &v_array:verticies) {
            System::window->draw(v_array);
        }
    }

    void refreshEntities() {
        for (auto entity:items) {
            entity->update();
        }

        for (auto entity:items) {
            if (std::find(itemsToRemove.begin(), itemsToRemove.end(), entity) != itemsToRemove.end()) {
                items.erase(std::remove(items.begin(), items.end(), entity), items.end());
                delete entity;
            }
        }

        itemsToRemove.clear();
    }

    void addElevator(Elevator *elevator) {
        elevators.push_back(elevator);
    }

    std::vector<Entity *> searchEntitiesByType(Entities type) {
        std::vector<Entity *> buffer;

        for (auto e:items) {
            if (e->getEType() == type) {
                buffer.push_back(e);
            }
        }

        return buffer;
    }

    std::vector<Entity *> searchEntitiesByGroup(EntityGroup group) {
        std::vector<Entity *> buffer;

        for (auto e:items) {
            for (auto g:group.get()) {
                if (e->getEType() == g) {
                    buffer.push_back(e);
                }
            }
        }

        return buffer;
    }

    Entity *searchSingleEntityByType(Entities type) {
        for (auto e:items) {
            if (e->getEType() == type) {
                return e;
            }
        }
    }
}

