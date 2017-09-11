#ifndef CORP_GAME_RESOURCE_LOADER
#define CORP_GAME_RESOURCE_LOADER

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "Enum.h"

namespace ResourceLoader {
    std::map<int, sf::Texture> textureCollection;

    void loadSingleTexture(Objects gameTexture, const std::string &filePath) {
        sf::Texture texture;
        texture.loadFromFile(filePath);
        ResourceLoader::textureCollection[gameTexture] = texture;
    }

    sf::Texture getSingleTexture(Objects gameTexture) {
        if (!ResourceLoader::textureCollection.count(gameTexture)) {
            throw std::invalid_argument("Unable to load texture");
        }

        return ResourceLoader::textureCollection[gameTexture];
    }

    void loadTexturesFromFiles() {
        ResourceLoader::loadSingleTexture(Objects::CharacterClerk, "resources/braid.monster.png");
    }
}

#endif