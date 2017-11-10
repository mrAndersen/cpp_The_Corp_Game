#ifndef THE_CORP_GAME_SYSTEM_H
#define THE_CORP_GAME_SYSTEM_H

#include <windows.h>
#include <psapi.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <deque>
#include "GameTime.h"

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
    extern sf::Event event;
    extern std::deque<sf::Event> eventDeque;
    extern long long int frameTimeMcs;
    extern sf::Uint32 screenMode;
    extern float timeFactor;
    //sys


    //group

    //utility
    extern sf::Color c_background;
    extern sf::Color c_grey;
    extern sf::Color c_red;
    extern sf::Color c_green;
    //utility

    //player
    extern double cash;
    extern bool spawningUnit;
    extern bool dayEndProcessed;
    extern bool dayStartProcessed;
    extern float salaryTotal;
    extern int buttonReload;

    extern sf::Clock dayClock;
    extern GameTime gameTime;
    extern int startWorkHour;
    extern int endWorkHour;
    //player


    //debug
    extern std::map<std::string, sf::Text> debugPanelTextNodes;
    extern sf::Font *debugFont;
    extern sf::Font *gameFont;
    extern unsigned int seed;

    extern float g_x;
    extern float g_y;

    extern int framesPassed;
    extern int entitiesOnScreen;
    extern int fps;
    extern bool debug;
    //debug

    RECT getScreenBoundaries();

    void refreshDayTime();

    void refreshDebugPanel();

    void refreshSystem();

    void initWindow();

    void initDebug();

    std::string f_to_string(const double value, const int n = 2);

    sf::Text createDebugString(const std::string &alias);

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates);

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates);

    sf::Vector2f cToGl(float x, float y);

    sf::Vector2f cFromGl(float x, float y);

    sf::Vector2f getGlobalMouse();

    int getRandom(int min, int max);
}

#endif //THE_CORP_GAME_SYSTEM_H
