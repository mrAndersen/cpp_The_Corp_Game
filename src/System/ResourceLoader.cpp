#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "Enum.h"

namespace ResourceLoader {
    static std::map<int, sf::Texture> textureCollection;

    static void loadSingleTexture(Objects gameTexture, const std::string &filePath) {
        sf::Texture texture;
        texture.loadFromFile(filePath);
        ResourceLoader::textureCollection[gameTexture] = texture;
    }

    static sf::Texture getSingleTexture(Objects gameTexture) {
        if (!ResourceLoader::textureCollection.count(gameTexture)) {
            throw std::invalid_argument("Unable to load texture");
        }

        return ResourceLoader::textureCollection[gameTexture];
    }

    static void loadTexturesFromFiles() {
        ResourceLoader::loadSingleTexture(Objects::CharacterClerk, "resources/braid.monster.png");
    }
}