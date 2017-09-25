#ifndef THE_CORP_GAME_SYSTEM_H
#define THE_CORP_GAME_SYSTEM_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace System {
    extern unsigned int screenWidth;
    extern unsigned int screenHeight;
    extern std::string title;
    extern float groundLevel;
    extern float worldWidth;
    extern int gridSize;
    extern int entitySequence;

    //sys
    extern sf::Time systemTime;
    extern sf::Clock fpsClock;
    extern sf::RenderWindow *window;
    //sys

    //utility
    extern sf::Color grey;
    extern sf::Color red;
    extern sf::Color green;
    //utility

    //player
    extern float cash;

    //player


    //debug
    extern std::map<std::string, sf::Text> debugPanelTextNodes;
    extern sf::Font *openSans;

    extern float g_x;
    extern float g_y;

    extern int framesPassed;
    extern int entitiesOnScreen;
    extern int fps;
    extern bool animationDebug;
    //debug

    void refreshTitleStats();

    void refreshDebugPanel();

    void initWindow();

    void initDebug();

    sf::Text createDebugString(const std::string &alias, int index);

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates);

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates);

    sf::Vector2f cToGl(float x, float y);

    sf::Vector2f cFromGl(float x, float y);

    sf::Vector2f getGlobalMouse();
}

#endif //THE_CORP_GAME_SYSTEM_H
