#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"
#include "../../includes/Animation/Entity.h"

namespace EntityContainer {
    std::vector<Entity *> items = {};

    std::vector<Entity *> getItems() {
        return items;
    }

    void add(Entity *item) {
        items.push_back(item);
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
        for (int i = -5000; i < 5000; ++i) {
            if ((i % Ground::width) == 0) {
                auto *ground = new Ground(sf::Vector2f(i, System::groundLevel + Ground::height / 2));
                EntityContainer::add(ground);
            }
        }
    }
}

