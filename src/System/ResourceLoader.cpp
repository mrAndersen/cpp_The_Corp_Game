#include <SFML/Graphics/Texture.hpp>
#include "../../includes/System/Enum.h"
#include "../../includes/System/ResourceLoader.h"

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