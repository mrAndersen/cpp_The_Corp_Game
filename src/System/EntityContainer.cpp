#include <Objects/ElevatorShaftMiddle.h>
#include <Objects/ElevatorShaftTop.h>
#include "Characters/Clerk.h"
#include "EntityContainer.h"
#include "Objects/Ground.h"
#include "System.h"
#include "Animation/Entity.h"
#include "Office/OfficeClerk.h"
#include "Controls/ControlButtonAddClerk.h"
#include "Controls/ControlButtonAddOffice.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::vector<sf::VertexArray> verticies;

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

    void add(Entity *item) {
        items.push_back(item);

        std::sort(items.begin(), items.end(), [](Entity *a, Entity *b) -> bool {
            return a->getDrawOrder() < b->getDrawOrder();
        });
    }

    void remove(Entity *item) {
        auto i = items.begin();
        while (i != items.end()) {
            if (*i == item) {
                i = items.erase(i);
                delete item;
            } else {
                ++i;
            }
        }
    }

    int size() {
        return items.size();
    }

    void initGround() {
        for (int i = (int) -System::worldWidth / 2; (int) i < System::worldWidth / 2; ++i) {
            if ((i % Ground::width) == 0) {
                new Ground(sf::Vector2f(i, System::groundLevel + Ground::height / 2));
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
    }


}

