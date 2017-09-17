#ifndef THE_CORP_GAME_RESOURCELOADER_H
#define THE_CORP_GAME_RESOURCELOADER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "Enum.h"

namespace ResourceLoader {
    extern std::map<int, sf::Texture*> textureCollection;

    void loadTexture(Entities target, const std::string &filePath);

    sf::Texture* getTexture(Entities target);

    void loadTexturesFromFiles();
}

#endif //THE_CORP_GAME_RESOURCELOADER_H
