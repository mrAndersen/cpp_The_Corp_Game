#ifndef THE_CORP_GAME_TREE_H
#define THE_CORP_GAME_TREE_H


#include "..\System\Enum.h"
#include "..\Basic\Entity.h"
#include <SFML/Window.hpp>

class Tree : public Entity {
public:
    const static int width = 267;
    const static int height = 517;

    explicit Tree(sf::Vector2f coordinates, Entities type, sf::Vector2f size = {(float) width, (float) height});
};


#endif //THE_CORP_GAME_TREE_H