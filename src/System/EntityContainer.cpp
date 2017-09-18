#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"
#include "../../includes/Animation/Entity.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::vector<sf::VertexArray> verticies;

    std::vector<Entity *> getItems() {
        return items;
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
                auto *ground = new Ground(sf::Vector2f(i, System::groundLevel + Ground::height / 2));
            }
        }
    }

    void initGrid() {
        sf::Color transparentBlack(0, 0, 0, 25);

        for (int i = (int) -System::worldWidth / 2; i < System::worldWidth / 2; i++) {
            if ((i % System::gridSize) == 0) {

                sf::VertexArray lines;
                lines.setPrimitiveType(sf::Lines);
                lines.append(sf::Vertex(System::convertToGLCoordinates(i, 5000), transparentBlack));
                lines.append(sf::Vertex(System::convertToGLCoordinates(i, System::groundLevel), transparentBlack));

                verticies.push_back(lines);
            }

        }

        for (int j = 8000; j > System::groundLevel; j--) {
            if ((j % System::gridSize) == 0) {
                sf::VertexArray lines;
                lines.setPrimitiveType(sf::Lines);
                lines.append(sf::Vertex(System::convertToGLCoordinates(-System::worldWidth / 2, j), transparentBlack));
                lines.append(sf::Vertex(System::convertToGLCoordinates(System::worldWidth / 2, j), transparentBlack));

                verticies.push_back(lines);
            }
        }
    }

    void refreshVertices() {
        for (const auto &v_array:verticies) {
            System::window->draw(v_array);
        }
    }
}

