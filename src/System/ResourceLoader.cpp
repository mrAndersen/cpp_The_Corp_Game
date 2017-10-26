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
    std::map<std::string, sf::Texture *> characterTextureCollection;

    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;

    void loadTexture(Entities target, const std::string &path, States state) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(path);
        textureCollection[target][state] = texture;
    }

    void loadCharacterTexture(Entities target, const std::string &path, States state, Gender gender, Race race) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(path);
        std::string key = std::to_string(target) + "." + std::to_string(state) + "." + std::to_string(gender) + "." +
                          std::to_string(race);
        characterTextureCollection[key] = texture;
    }

    sf::Texture *getTexture(Entities target, States state) {
        if (!textureCollection.count(target)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture *texture = textureCollection[target][state];
        texture->setSmooth(false);

        return texture;
    }

    sf::Texture *getCharacterTexture(Entities target, States state, Gender gender, Race race) {
        std::string key = std::to_string(target) + "." + std::to_string(state) + "." + std::to_string(gender) + "." +
                          std::to_string(race);

        if (!characterTextureCollection.count(key)) {
            throw std::invalid_argument("Unable to load texture");
        }

        sf::Texture *texture = characterTextureCollection[key];
        texture->setSmooth(false);

        return texture;
    }


    void loadTexturesFromFiles() {
        //----<<Ui>>----
        ResourceLoader::loadTexture(Entities::E_Indicator_Money, "resources/ui/indicator.money.png");

        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/ui/button.add.clerk.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/ui/button.add.clerk.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/ui/button.add.office.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/ui/button.add.office.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevator, "resources/ui/button.elevator.create.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevator, "resources/ui/button.elevator.create.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorCabin, "resources/ui/button.add.cabin.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorCabin, "resources/ui/button.add.cabin.pressed.png", S_Button_Pressed);

        //----<<QuestionMarks>>----
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddElevator, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddElevator, "resources/ui/question.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddOffice, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddOffice, "resources/ui/question.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddClerk, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddClerk, "resources/ui/question.pressed.png", S_Button_Pressed);

        //----<<Elevator>>----
        ResourceLoader::loadTexture(Entities::E_ElevatorCabin, "resources/elevator/cabin.l1.png");
        ResourceLoader::loadTexture(Entities::E_ElevatorShaftMiddle, "resources/elevator/elevator.middle.l1.png");
        ResourceLoader::loadTexture(Entities::E_ElevatorShaftTop, "resources/elevator/elevator.top.l1.png");

        //----<<Office>>----
        ResourceLoader::loadTexture(Entities::E_OfficeDefault, "resources/office/office.default.png");
        ResourceLoader::loadTexture(Entities::E_Chair, "resources/office/chair.png");


        //----<<Clerk>>-----
        std::string alias = "clerk";
        Gender genders[] = {G_Male, G_Female};
        Race races[] = {R_White, R_Black, R_Asian};
        std::string levels[] = {"l1"};
        States states[] = {
                S_None,
                S_Stand,
                S_Run,
                S_Walk,
                S_Smoking,
                S_WaitForElevator,
                S_RideInElevator,
                S_Working,
                S_Falling,
                S_GoToOffice,
                S_GoHome,
                S_GoSmoke,
                S_GoToElevator,
                S_GoToCabin,
        };

        for (auto gender:genders) {
            for (auto race:races) {
                for (auto level:levels) {
                    for (auto state:states) {
                        std::string path =
                                "resources/characters/" + alias + "/"
                                + getGenderTextNotation(gender) + "."
                                + getRaceTextNotation(race) + "."
                                + level + "."
                                + getStateTextNotation(state) + ".png";

                        ResourceLoader::loadCharacterTexture(
                                E_Clerk,
                                path,
                                state,
                                gender,
                                race
                        );
                    }
                }
            }
        }


        ResourceLoader::loadTexture(Entities::E_StaticGround, "resources/ground.png");

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

    States getStateEnumNotation(const std::string &title) {
        return S_None;
    }

    Gender getGenderEnumNotation(const std::string &title) {
        if (title == "m") { return G_Male; }
        if (title == "f") { return G_Female; }
    }

    Race getRaceEnumNotation(const std::string &title) {
        if (title == "w") { return R_White; }
        if (title == "b") { return R_Black; }
        if (title == "a") { return R_Asian; }
    }

    std::string getStateTextNotation(States state) {
        if ( state == S_Walk || state == S_GoToOffice || state == S_GoToCabin || state == S_GoToElevator || state == S_GoHome || state == S_GoSmoke){
            return "walk";
        }

        if(state == S_WaitForElevator || state == S_RideInElevator || state == S_Stand || state == S_None){
            return "wait";
        }

        if(state == S_Working){
            return "work";
        }

        if(state == S_Smoking){
            return "smoke";
        }
    }

    std::string getGenderTextNotation(Gender gender) {
        if (gender == G_Male) { return "m"; }
        if (gender == G_Female) { return "f"; }
    }

    std::string getRaceTextNotation(Race race) {
        if (race == R_White) { return "w"; }
        if (race == R_Black) { return "b"; }
        if (race == R_Asian) { return "a"; }
    }


}