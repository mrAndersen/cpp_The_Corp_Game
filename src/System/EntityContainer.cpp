#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"

namespace EntityContainer {
    std::vector<Movable *> items = {};

    std::vector<Movable *> getAll() {
        return items;
    }

    void add(Movable *item) {
        items.push_back(item);
    }

    void remove(Movable *item) {

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
}

