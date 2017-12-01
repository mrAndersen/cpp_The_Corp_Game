#ifndef THE_CORP_GAME_RESOURCELOADER_H
#define THE_CORP_GAME_RESOURCELOADER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <yaml-cpp/yaml.h>
#include "Enum.h"
#include <SFML/System/String.hpp>

namespace ResourceLoader {
    extern YAML::Node translations;

    sf::String getTranslation(std::string key);

    void loadTexture(Entities target, const std::string &path, States states = S_None);

    void loadCharacterTexture(Entities target, const std::string &path, States state = S_None, Gender gender = G_Male, Race race = R_White, int level = 1);

    sf::Texture *getTexture(Entities target, States states = S_None);

    sf::Texture *loadAndGetTexture(const std::string &path);

    sf::Texture *getCharacterTexture(Entities target, States state = S_None, Gender gender = G_Male, Race race = R_White, int level = 1);

    void loadTexturesFromFiles();

    void loadFonts();

    void loadNames();

    void loadLocales();

    std::string getCharacterTextNotation(Entities character);

    std::string getStateTextNotation(States state);

    States getStateEnumNotation(const std::string &title);

    std::string getGenderTextNotation(Gender gender);

    Gender getGenderEnumNotation(const std::string &title);

    std::string getRaceTextNotation(Race race);

    Race getRaceEnumNotation(const std::string &title);

    std::string getRandomName(Gender gender);
}

#endif //THE_CORP_GAME_RESOURCELOADER_H
