#ifndef THE_CORP_GAME_SYSTEM_H
#define THE_CORP_GAME_SYSTEM_H

#include <afxres.h>
#include <psapi.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../Utls/GameTime.h"

namespace System {
    extern unsigned int screenWidth;
    extern unsigned int screenHeight;
    extern std::string title;
    extern float groundLevel;
    extern float worldWidth;
    extern int gridSize;
    extern int entitySequence;

    //sys
    extern sf::Clock fpsClock;
    extern sf::Clock frameClock;
    extern sf::Clock timeSinceStart;
    extern sf::RenderWindow *window;
    extern int frameTimeMcs;
    extern sf::Uint32 screenMode;
    extern float timeFactor;
    //sys

    //utility
    extern sf::Color c_background;

    extern sf::Color c_grey;
    extern sf::Color c_red;
    extern sf::Color c_green;
    //utility

    //player
    extern float cash;
    extern bool spawningUnit;

    extern sf::Clock dayClock;
    extern GameTime gameTime;
    extern int startWorkHour;
    extern int endWorkHour;
    //player


    //debug
    extern std::map<std::string, sf::Text> debugPanelTextNodes;
    extern sf::Font *debugFont;
    extern sf::Font *gameFont;

    extern float g_x;
    extern float g_y;

    extern int framesPassed;
    extern int entitiesOnScreen;
    extern int fps;
    extern bool animationDebug;
    //debug

    RECT getScreenBoundaries();

    void refreshDayTime();

    void refreshDebugPanel();

    void refreshSystem();

    void initWindow();

    void initDebug();

    std::string to_string_with_precision(const float value, const int n = 2);

    sf::Text createDebugString(const std::string &alias, int index);

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates);

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates);

    sf::Vector2f cToGl(float x, float y);

    sf::Vector2f cFromGl(float x, float y);

    sf::Vector2f getGlobalMouse();
}

#endif //THE_CORP_GAME_SYSTEM_H
