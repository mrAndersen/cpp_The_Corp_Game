#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../../includes/System/Enum.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/System.h"

namespace ResourceLoader {
    std::map<int, std::map<int, sf::Texture*>> textureCollection;

    void loadTexture(Entities target, const std::string &filePath, States state) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(filePath);
        ResourceLoader::textureCollection[target][state] = texture;
    }

    sf::Texture* getTexture(Entities target, States state) {
        if (!ResourceLoader::textureCollection.count(target)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture* texture = textureCollection[target][state];
        texture->setSmooth(true);

        return texture;
    }

    void loadTexturesFromFiles() {
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/white.level_1.png");


        ResourceLoader::loadTexture(Entities::E_StaticGround, "resources/ground.png");

        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/control.panel/button.add.clerk.png");
        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/control.panel/button.add.office.png");

        ResourceLoader::loadTexture(Entities::E_OfficeClerk, "resources/office/office.clerk.png");
    }

    void loadFonts(){
        System::debugFont = new sf::Font();
        System::gameFont = new sf::Font();

        System::debugFont->loadFromFile("resources/fonts/OpenSans-Light.ttf");
        System::gameFont->loadFromFile("resources/fonts/Teko-Regular.ttf");
    }
}