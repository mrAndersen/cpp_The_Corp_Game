#include <SFML/Graphics/Texture.hpp>
#include "../../includes/System/Enum.h"
#include "../../includes/System/ResourceLoader.h"

namespace ResourceLoader {
    std::map<int, sf::Texture*> textureCollection;

    void loadTexture(Entities target, const std::string &filePath) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(filePath);
        ResourceLoader::textureCollection[target] = texture;
    }

    sf::Texture* getTexture(Entities target) {
        if (!ResourceLoader::textureCollection.count(target)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture* texture = textureCollection[target];
        return texture;
    }

    void loadTexturesFromFiles() {
        ResourceLoader::loadTexture(Entities::E_MovableClerk, "resources/128px.png");
        ResourceLoader::loadTexture(Entities::E_StaticGround, "resources/ground.png");

        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/control.panel/button.add.clerk.png");
        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/control.panel/button.add.office.png");

        ResourceLoader::loadTexture(Entities::E_OfficeClerk, "resources/office/office.clerk.png");
    }
}