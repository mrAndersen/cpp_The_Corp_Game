//
// Created by mrAndersen on 11.09.2017.
//

#ifndef THE_CORP_GAME_SYSTEM_H_H
#define THE_CORP_GAME_SYSTEM_H_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace System {
    static unsigned int screenWidth = 1820;
    static unsigned int screenHeight = 800;
    static std::string title = "New World";

    //sys
    static sf::Clock systemClock;
    static sf::RenderWindow *window;
    //sys

    //utility
    static sf::Color grey(236, 237, 227);
    //utility

    //debug
    static std::map<std::string, sf::Text> debugPanelTextNodes;
    static sf::Font openSans;
    static int mouseX = 0;
    static int mouseY = 0;
    static int framesPassed = 0;
    static int entitiesOnScreen = 0;

    static int charactersOnScreenCount = 0;
    static int fps = 0;
    //debug

    static void refreshTitleStats();

    static void refreshDebugPanel();

    static sf::RenderWindow *initWindow();

    static void initDebug();
}

#endif //THE_CORP_GAME_SYSTEM_H_H
