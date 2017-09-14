#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"

namespace EntityContainer {
    std::vector<Movable *> m_items = {};
    std::vector<Static *> s_items = {};

    std::vector<Movable *> getMovableItems() {
        return m_items;
    }

    std::vector<Static *> getStaticItems() {
        return s_items;
    }

    void addMovable(Movable *item) {
        m_items.push_back(item);
    }

    void addStatic(Static *item) {
        s_items.push_back(item);
    }

    void removeMovable(Movable *item) {
        auto i = m_items.begin();
        while (i != m_items.end()) {
            if (*i == item) {
                i = m_items.erase(i);
                delete item;
            } else {
                ++i;
            }
        }
    }

    void removeStatic(Static *item) {
        auto i = s_items.begin();
        while (i != s_items.end()) {
            if (*i == item) {
                i = s_items.erase(i);
                delete item;
            } else {
                ++i;
            }
        }
    }

    int movableSize() {
        return m_items.size();
    }

    int staticSize() {
        return s_items.size();
    }

    void initGround() {
        for (int i = -5000; i < 5000; ++i) {
            if (i % 100 == 0) {
                auto *ground = new Ground(sf::Vector2f(i, System::groundLevel - Ground::height));

                EntityContainer::addStatic(ground);
            }

        }


    }
}

