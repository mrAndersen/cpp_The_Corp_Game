#include <SFML/Graphics/Texture.hpp>
#include "../../includes/System/Enum.h"
#include "../../includes/System/ResourceLoader.h"

namespace ResourceLoader {
    std::map<int, sf::Texture*> textureCollection;

    void loadSingleTexture(Entities target, const std::string &filePath) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(filePath);
        ResourceLoader::textureCollection[target] = texture;
    }

    sf::Texture* getSingleTexture(Entities target) {
        if (!ResourceLoader::textureCollection.count(target)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture* texture = textureCollection[target];
        return texture;
    }

    void loadTexturesFromFiles() {
        ResourceLoader::loadSingleTexture(Entities::MovableClerk, "resources/128px.png");
        ResourceLoader::loadSingleTexture(Entities::StaticGround, "resources/ground.png");
    }
}