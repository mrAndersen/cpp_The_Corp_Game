#ifndef THE_CORP_GAME_SYSTEM_H
#define THE_CORP_GAME_SYSTEM_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace System {
    extern unsigned int screenWidth;
    extern unsigned int screenHeight;
    extern std::string title;

    //sys
    extern sf::Time systemTime;
    extern sf::Clock systemClock;
    extern sf::RenderWindow *window;
    //sys

    //utility
    extern sf::Color grey;
    //utility

    //debug
    extern std::map<std::string, sf::Text> debugPanelTextNodes;
    extern sf::Font openSans;
    extern int mouseX;
    extern int mouseY;
    extern int framesPassed;
    extern int entitiesOnScreen;
    extern int fps;
    //debug

    void refreshTitleStats();

    void refreshDebugPanel();

    void initWindow();

    void initDebug();
}

#endif //THE_CORP_GAME_SYSTEM_H
