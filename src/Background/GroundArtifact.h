#ifndef THE_CORP_GAME_GROUNDARTIFACT_H
#define THE_CORP_GAME_GROUNDARTIFACT_H


#include <SFML/System/Vector2.hpp>
#include "..\System\Enum.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "..\Basic\Entity.h"

class GroundArtifact : public Entity {

public:
    GroundArtifact(sf::Vector2f coordinates, sf::Vector2i size, Entities type);
};


#endif //THE_CORP_GAME_GROUNDARTIFACT_H
