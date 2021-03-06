#ifndef THE_CORP_GAME_SYSTEM_H
#define THE_CORP_GAME_SYSTEM_H

//#include <windows.h>
//#include <psapi.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <deque>
#include "GameTime.h"
#include "Enum.h"

namespace System {
    extern unsigned int screenWidth;
    extern unsigned int screenHeight;
    extern std::string title;
    extern float worldWidth;
    extern int gridSize;
    extern int entitySequence;

    //sys
    extern std::string id;
    extern Scenes activeScene;
    extern Scenes loadingScene;
    extern sf::Clock saveTimer;
    extern sf::Clock sceneChangeTimer;
    extern sf::Clock fpsClock;
    extern sf::Clock frameClock;
    extern sf::Clock timeSinceStart;
    extern sf::RenderWindow *window;
    extern sf::Event event;
    extern bool selectionAllowed;
    extern long long int frameTimeMcs;
    extern sf::Uint32 screenMode;
    extern float timeFactor;
    extern std::string locale;
    extern sf::Font *textFont;
    extern sf::Font *titleFont;
    extern sf::Font *titleFontI8N;
    extern unsigned int seed;
    //sys


    //group

    //utility
    extern sf::Color c_background;
    extern sf::Color c_grey;
    extern sf::Color c_red;
    extern sf::Color c_yellow;
    extern sf::Color c_green;
    extern sf::Color c_blue;
    //utility

    //player
    extern double cash;
    extern float accountantsBonus;
    extern bool spawningUnit;
    extern sf::Clock selectionCooldown;
    extern bool dayEndProcessed;
    extern bool dayStartProcessed;
    extern int buttonReload;

    extern sf::Clock dayClock;
    extern GameTime gameTime;
    extern int startWorkHour;
    extern int endWorkHour;
    extern int daysPassed;
    //player


    //debug
    extern std::map<std::string, sf::Text> debugPanelTextNodes;
    extern std::map<std::string, int> debugCounters;
    extern float g_x;
    extern float g_y;

    extern int framesPassed;
    extern int entitiesOnScreen;
    extern int fps;
    extern int debug;
    extern std::string versionType;
    extern std::string version;
    //debug

//    RECT getScreenBoundaries();

    sf::String join(std::vector<std::string> &array, char delimiter);
    std::vector<std::string> split(std::string source, char delimiter = '.');

    void refreshDayTime();

    void refreshDebugPanel();

    void refreshSystem();

    void initWindow();

    void initDebug();

    bool mouseInsideRect(const sf::Vector2f &leftTop, const sf::Vector2f &rightBottom);

    std::string f_to_string(double value, int n = 2);

    std::string formatNewLines(const std::string &in, size_t every_n);

    sf::Text createDebugString(const std::string &alias);

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates);

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates);

    sf::Vector2f cToGl(float x, float y);

    sf::Vector2f cFromGl(float x, float y);

    sf::Vector2f getGlobalMouse();

    int getRandom(int min, int max);

    int roundToMultiple(float target, int multiple = 25);

    void handleGlobalLogic();

    void changeScene(Scenes scene);
}

#endif //THE_CORP_GAME_SYSTEM_H
