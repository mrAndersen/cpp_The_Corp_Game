#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <random>
#include <iostream>
#include "Enum.h"
#include "ResourceLoader.h"
#include "System.h"
#include "../../vendor/yaml-cpp/include/yaml-cpp/yaml.h"

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

    void loadCharacterTexture(Entities target, const std::string &path, States state, Gender gender, Race race, int level) {
        auto *texture = new sf::Texture;

        texture->loadFromFile(path);

        std::string key =
                std::to_string(level) + "."
                + std::to_string(target) + "."
                + std::to_string(state) + "."
                + std::to_string(gender) + "."
                + std::to_string(race);

        characterTextureCollection[key] = texture;
    }

    sf::Texture *getTexture(Entities target, States state) {
        sf::Texture *texture = textureCollection[target][state];

        if (texture) {
            texture->setSmooth(false);
        }

        return texture;
    }

    sf::Texture *getCharacterTexture(Entities target, States state, Gender gender, Race race, int level) {
        std::string key =
                std::to_string(level) + "."
                + std::to_string(target) + "."
                + std::to_string(state) + "."
                + std::to_string(gender) + "."
                + std::to_string(race);

        sf::Texture *texture = characterTextureCollection[key];

        if (texture) {
            texture->setSmooth(false);
        }

        return texture;
    }


    void loadTexturesFromFiles() {
        //----<<Background>>----
        ResourceLoader::loadTexture(Entities::E_StaticGround_1, "resources/background/ground1.png");
        ResourceLoader::loadTexture(Entities::E_StaticGround_2, "resources/background/ground2.png");
        ResourceLoader::loadTexture(Entities::E_StaticGround_3, "resources/background/ground3.png");

        ResourceLoader::loadTexture(Entities::E_StaticTree_1, "resources/background/tree1.png");
        ResourceLoader::loadTexture(Entities::E_StaticTree_2, "resources/background/tree2.png");
        ResourceLoader::loadTexture(Entities::E_StaticTree_3, "resources/background/tree3.png");
        ResourceLoader::loadTexture(Entities::E_StaticTree_4, "resources/background/tree4.png");
        ResourceLoader::loadTexture(Entities::E_StaticGroundArtifact_1, "resources/background/ground.skeleton.png");

        //----<<Ui>>----
        ResourceLoader::loadTexture(Entities::E_Indicator_Money, "resources/ui/indicator.money.png");
        ResourceLoader::loadTexture(Entities::E_Popup, "resources/ui/popup.png");

        ResourceLoader::loadTexture(Entities::E_Popup_Button, "resources/ui/popup.button.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Popup_Button, "resources/ui/popup.button.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_MainPanelOverlay, "resources/ui/main.panel.png");

        ResourceLoader::loadTexture(Entities::E_ButtonPause, "resources/ui/button.pause.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonPause, "resources/ui/button.pause.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Button1x, "resources/ui/button.1x.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Button1x, "resources/ui/button.1x.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Button5x, "resources/ui/button.5x.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Button5x, "resources/ui/button.5x.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Button10x, "resources/ui/button.10x.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Button10x, "resources/ui/button.10x.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/ui/button.add.clerk.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddClerk, "resources/ui/button.add.clerk.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddManager, "resources/ui/button.add.manager.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddManager, "resources/ui/button.add.manager.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddAccountant, "resources/ui/button.add.accountant.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddAccountant, "resources/ui/button.add.accountant.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/ui/button.add.office.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddOffice, "resources/ui/button.add.office.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevator, "resources/ui/button.elevator.create.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevator, "resources/ui/button.elevator.create.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorCabin, "resources/ui/button.add.cabin.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorCabin, "resources/ui/button.add.cabin.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftMiddle, "resources/ui/button.add.shaft.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftMiddle, "resources/ui/button.add.shaft.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftTop, "resources/ui/button.add.shaft-top.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_ButtonAddElevatorShaftTop, "resources/ui/button.add.shaft-top.pressed.png", S_Button_Pressed);

        //----<<QuestionMarks>>----
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddElevator, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddElevator, "resources/ui/question.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddManager, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddManager, "resources/ui/question.pressed.png", S_Button_Pressed);

        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddAccountant, "resources/ui/question.png", S_Button_Normal);
        ResourceLoader::loadTexture(Entities::E_Question_Mark_ButtonAddAccountant, "resources/ui/question.pressed.png", S_Button_Pressed);

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

        //----<<Characters>>-----
        std::vector<Entities> characters = {E_Clerk, E_Manager, E_Accountant};
        Gender genders[] = {G_Male};
        Race races[] = {R_White, R_Black, R_Asian};
        int levels[] = {1, 2};
        States states[] = {
                S_None,
                S_Play,
                S_Run,
                S_Walk,
                S_Smoking,
                S_Working
        };

        for (auto &character:characters) {
            for (auto &gender:genders) {
                for (auto &race:races) {
                    for (auto &level:levels) {
                        for (auto &state:states) {
                            std::string path =
                                    "resources/characters/" + getCharacterTextNotation(character) + "/"
                                    + getGenderTextNotation(gender) + "."
                                    + getRaceTextNotation(race) + "."
                                    + "l" + std::to_string(level) + "."
                                    + getStateTextNotation(state) + ".png";

                            if (std::ifstream(path)) {
                                ResourceLoader::loadCharacterTexture(
                                        character,
                                        path,
                                        state,
                                        gender,
                                        race,
                                        level
                                );
                            }
                        }
                    }
                }
            }
        }

    }

    void loadFonts() {
        System::debugFont = new sf::Font();
        System::gameFont = new sf::Font();
        System::gameFont2 = new sf::Font();

        System::debugFont->loadFromFile("resources/fonts/DidactGothic-Regular.ttf");
        System::gameFont->loadFromFile("resources/fonts/Teko-Regular.ttf");
        System::gameFont2->loadFromFile("resources/fonts/Oswald-Regular.ttf");
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
            return maleNames[System::getRandom(0, maleNames.size() - 1)];
        }

        if (gender == Gender::G_Female) {
            return femaleNames[System::getRandom(0, femaleNames.size() - 1)];
        }

        return "Unknown";
    }

    States getStateEnumNotation(const std::string &title) {
        return S_None;
    }

    Gender getGenderEnumNotation(const std::string &title) {
        if (title == "m") { return G_Male; }
        if (title == "f") { return G_Female; }

        return G_Male;
    }

    Race getRaceEnumNotation(const std::string &title) {
        if (title == "w") { return R_White; }
        if (title == "b") { return R_Black; }
        if (title == "a") { return R_Asian; }

        return R_White;
    }

    std::string getStateTextNotation(States state) {
        if (state == S_Walk) {
            return "walk";
        }

        if (state == S_None) {
            return "wait";
        }

        if (state == S_Working) {
            return "work";
        }

        if (state == S_Smoking) {
            return "smoke";
        }

        if (state == S_Play) {
            return "play";
        }

        return "wait";
    }

    std::string getGenderTextNotation(Gender gender) {
        if (gender == G_Male) { return "m"; }
        if (gender == G_Female) { return "f"; }

        return "m";
    }

    std::string getRaceTextNotation(Race race) {
        if (race == R_White) { return "w"; }
        if (race == R_Black) { return "b"; }
        if (race == R_Asian) { return "a"; }

        return "w";
    }

    std::string getCharacterTextNotation(Entities character) {
        if (character == E_Clerk) { return "clerk"; }
        if (character == E_Manager) { return "manager"; }
        if (character == E_Accountant) { return "accountant"; }

        return "clerk";
    }

    sf::Texture *loadAndGetTexture(const std::string &path) {
        auto texture = new sf::Texture;
        texture->loadFromFile(path);

        return texture;
    }

    void loadLocales() {
        YAML::Node config = YAML::LoadFile("resources/locale/" + System::locale + ".yml");



        return;


    }


}