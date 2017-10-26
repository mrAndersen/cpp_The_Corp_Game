#include <algorithm>
#include <cstdarg>
#include "EntityGroup.h"

bool EntityGroup::hasType(Entities type) {
    return std::find(list.begin(), list.end(), type) != list.end();
}

bool EntityGroup::addType(Entities type) {
    list.push_back(type);
}

EntityGroup::EntityGroup(std::initializer_list<Entities> types) {
    for (auto t:types) {
        list.push_back(t);
    }
}

std::vector<Entities> EntityGroup::get() {
    return list;
}
