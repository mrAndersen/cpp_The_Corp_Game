#include <SFML/Window/Mouse.hpp>
#include <afxres.h>
#include <psapi.h>
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/Utls/GameTime.h"

namespace System {
    unsigned int screenWidth = 1700;
    unsigned int screenHeight = 800;
    std::string title = "New World";
    float groundLevel = 0;
    float worldWidth = 10000;
    int gridSize = 100;
    int entitySequence = 1;

    //sys
    sf::Clock fpsClock;
    sf::Clock frameClock;
    sf::Clock timeSinceStart;
    sf::RenderWindow *window;
    int frameTimeMcs;
    sf::Uint32 screenMode = sf::Style::Default;
    float timeFactor = 5;
    //sys

    //utility
    sf::Color c_background(255, 255, 255);

    sf::Color c_grey(236, 237, 227);
    sf::Color c_red(186, 24, 24);
    sf::Color c_green(92, 184, 92);
    //utility

    //player
    float cash = 50000;
    bool spawningUnit = false;

    sf::Clock dayClock;
    GameTime gameTime(12, 0);

    int startWorkHour = 9;
    int endWorkHour = 18;
    //player

    //debug
    std::map<std::string, sf::Text> debugPanelTextNodes;
    sf::Font *openSans;
    float g_x = 0;
    float g_y = 0;
    int framesPassed = 0;
    int entitiesOnScreen = 0;
    int fps = 0;
    bool animationDebug = true;
    //debug

    void refreshDayTime() {
        auto localTimeFactor = 1000 / timeFactor;

        if (dayClock.getElapsedTime().asMilliseconds() >= localTimeFactor) {
            dayClock.restart();

            gameTime = gameTime + 1;
        }
    }

    void refreshSystem() {
        window->setTitle("Incorporated ~ [" + std::to_string(fps) + " FPS]");

        frameTimeMcs = frameClock.restart().asMicroseconds();
        framesPassed++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1) {
            fps = framesPassed;

            framesPassed = 0;
            fpsClock.restart();
        }
    }

    void refreshDebugPanel() {
        auto mousePosition = sf::Mouse::getPosition(*window);
        auto coordMap = window->mapPixelToCoords(mousePosition);

        PROCESS_MEMORY_COUNTERS pmc = {};
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        SIZE_T mem = pmc.WorkingSetSize;

        g_x = coordMap.x;
        g_y = System::screenHeight - coordMap.y;

        debugPanelTextNodes["g_coordinates"].setString(
                "global: {" + std::to_string((int) g_x) + "," + std::to_string((int) g_y) + "}");
        debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
        debugPanelTextNodes["mouse"].setString(
                "mouse: {" + std::to_string(mousePosition.x) + "," + std::to_string(mousePosition.y) + "}");
        debugPanelTextNodes["entity_count"].setString("entities: " + std::to_string(entitiesOnScreen));
        debugPanelTextNodes["v_direction"].setString(
                "v_direction: " + std::to_string(ViewHandler::viewDirectionMovement));
        debugPanelTextNodes["mem"].setString(
                "mem:" + std::to_string((int) mem / 1024 / 1024) + "mb"
        );


        debugPanelTextNodes["v_boundaries"].setString(
                "v_boundaries: "
                        "{t=" + std::to_string((int) ViewHandler::top) + ","
                        "b=" + std::to_string((int) ViewHandler::bottom) + ","
                        "l=" + std::to_string((int) ViewHandler::left) + ","
                        "r=" + std::to_string((int) ViewHandler::right) + "}"
        );

        debugPanelTextNodes["v_zoom"].setString("v_zoom: " + std::to_string(ViewHandler::zoom));
        debugPanelTextNodes["p_cash"].setString("p_cash: " + std::to_string(System::cash));
        debugPanelTextNodes["p_time"].setString("p_time:" + gameTime.get());

        std::map<std::string, sf::Text>::iterator it;
        int i = 1;

        for (it = debugPanelTextNodes.begin(); it != debugPanelTextNodes.end(); it++) {
            it->second.setPosition(
                    cToGl(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - i * 12)));
            window->draw(it->second);

            i++;
        }
    }

    void initWindow() {

        if (window) {
            delete window;
            window = nullptr;

            delete ViewHandler::view;
            ViewHandler::view = nullptr;
        }

        if (screenMode == sf::Style::Fullscreen) {
            auto boundaries = getScreenBoundaries();

            screenWidth = (unsigned int) boundaries.right;
            screenHeight = (unsigned int) boundaries.bottom;
        }

        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, screenMode);
        window->clear(c_background);

        ViewHandler::view = new sf::View();
        ViewHandler::view->reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::view->setCenter(screenWidth / 2, screenHeight / 2);

        window->setView(*ViewHandler::view);
    }

    sf::Text createDebugString(const std::string &alias, int index) {
        sf::Text label;
        label.setPosition(cToGl(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - index * 12)));
        label.setFillColor(sf::Color::Black);
        label.setFont(*openSans);
        label.setCharacterSize(10);

        debugPanelTextNodes[alias] = label;
        return label;
    }

    void initDebug() {
        openSans = new sf::Font();
        openSans->loadFromFile("resources/fonts/open-sans.ttf");
        const_cast<sf::Texture &>(openSans->getTexture(10)).setSmooth(false);

        createDebugString("fps", 1);
        createDebugString("mem", 2);
        createDebugString("g_coordinates", 3);
        createDebugString("mouse", 4);
        createDebugString("entity_count", 5);
        createDebugString("v_direction", 6);
        createDebugString("v_boundaries", 7);
        createDebugString("v_zoom", 8);
        createDebugString("p_cash", 9);
        createDebugString("p_time", 10);
    }

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates) {
        worldCoordinates.y = System::screenHeight - worldCoordinates.y;
        return worldCoordinates;
    }

    sf::Vector2f cToGl(float x, float y) {
        return {x, System::screenHeight - y};
    }

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates) {
        glCoordinates.y = System::screenHeight - glCoordinates.y;
        return glCoordinates;
    }

    sf::Vector2f cFromGl(float x, float y) {
        return {x, y - System::screenHeight};
    }

    sf::Vector2f getGlobalMouse() {
        return {System::g_x, System::g_y};
    }

    RECT getScreenBoundaries() {
        RECT w_Desktop{};
        GetWindowRect(GetDesktopWindow(), &w_Desktop);

        return w_Desktop;
    }
}