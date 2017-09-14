#include <SFML/Graphics/Texture.hpp>
#include "../../includes/System/Enum.h"
#include "../../includes/System/ResourceLoader.h"

namespace ResourceLoader {
    std::map<int, sf::Texture*> textureCollection;

    void loadSingleTexture(Objects object, const std::string &filePath) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(filePath);
        ResourceLoader::textureCollection[object] = texture;
    }

    sf::Texture* getSingleTexture(Objects object) {
        if (!ResourceLoader::textureCollection.count(object)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture* texture = textureCollection[object];
        return texture;
    }

    void loadTexturesFromFiles() {
        ResourceLoader::loadSingleTexture(Objects::CharacterClerk, "resources/128px.png");
    }
}