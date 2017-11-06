#ifndef THE_CORP_GAME_ENTITYGROUP_H
#define THE_CORP_GAME_ENTITYGROUP_H


#include <vector>
#include "Enum.h"

class EntityGroup {
    std::vector<Entities> list;

public:
    EntityGroup(std::initializer_list<Entities> types = {});

    std::vector<Entities> get();

    bool hasType(Entities type);

    void addType(Entities type);
};


#endif //THE_CORP_GAME_ENTITYGROUP_H
