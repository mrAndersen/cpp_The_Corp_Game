#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <random>
#include <iostream>
#include "Enum.h"
#include "ResourceLoader.h"
#include "System.h"

namespace ResourceLoader {
    std::map<int, std::map<int, sf::Texture *>> textureCollection;

    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;

    void loadTexture(Entities target, const std::string &filePath, States state) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(filePath);
        ResourceLoader::textureCollection[target][state] = texture;
    }

    sf::Texture *getTexture(Entities target, States state) {
        if (!ResourceLoader::textureCollection.count(target)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture *texture = textureCollection[target][state];
        texture->setSmooth(false);

        return texture;
    }

    void loadTexturesFromFiles() {
        //----<<Ui>>-----
        ResourceLoader::loadTexture(Entities::E_Indicator_Money, "resources/ui/indicator.money.png");


        ResourceLoader::loadTexture(Entities::E_OfficeDefault, "resources/office/office.default.png");
        ResourceLoader::loadTexture(Entities::E_Chair, "resources/office/chair.png");


        //----<<Clerk>>-----
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.wait.png", S_None);
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.walk.png", S_GoToOffice);
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.walk.png", S_GoToElevator);
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.walk.png", S_GoToCabin);
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.work.png", S_Working);
        ResourceLoader::loadTexture(Entities::E_Clerk, "resources/characters/clerk/w.l1.smoke.png", S_Smoking);


        ResourceLoader::loadTexture(Entities::E_StaticGround, "resources/ground.png");

        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/control.panel/button.add.clerk.png");
        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/control.panel/button.add.office.png");
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftMiddle, "resources/control.panel/button.add.elevator.png");
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftTop, "resources/control.panel/button.add.elevator.png");




//        ResourceLoader::loadTexture(Entities::E_ElevatorShaftBottom, "resources/elevator/elevator.middle.l1.png");
        ResourceLoader::loadTexture(Entities::E_ElevatorShaftMiddle, "resources/elevator/elevator.middle.l1.png");
        ResourceLoader::loadTexture(Entities::E_ElevatorShaftTop, "resources/elevator/elevator.top.l1.png");
        ResourceLoader::loadTexture(Entities::E_ElevatorCabin, "resources/elevator/cabin.l1.png");

    }

    void loadFonts() {
        System::debugFont = new sf::Font();
        System::gameFont = new sf::Font();

        System::debugFont->loadFromFile("resources/fonts/OpenSans-Light.ttf");
        System::gameFont->loadFromFile("resources/fonts/Teko-Regular.ttf");
    }

    void loadNames() {
        std::ifstream males("resources/names/male.txt");
        std::ifstream females("resources/names/female.txt");
        std::string line;

        while (std::getline(males, line)) {
            maleNames.push_back(line);
        }

        while (std::getline(females, line)) {
            femaleNames.push_back(line);
        }

        males.close();
        females.close();
    }

    std::string getRandomName(Gender gender) {

        if (gender == Gender::G_Male) {
            return maleNames[System::getRandom(0, maleNames.size())];
        }

        if (gender == Gender::G_Female) {
            return femaleNames[System::getRandom(0, femaleNames.size())];
        }
    }
}