#include <SFML/Window/Mouse.hpp>
#include <winuser.h>
#include <afxres.h>
#include <psapi.h>
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"

namespace System {
    unsigned int screenWidth = 1820;
    unsigned int screenHeight = 800;
    std::string title = "New World";
    float groundLevel = 0;
    float worldWidth = 10000;
    int gridSize = 100;

    //sys
    sf::Clock fpsClock;
    sf::RenderWindow *window;
    //sys

    //utility
    sf::Color grey(236, 237, 227);
    sf::Color red(248, 215, 227, 255);
    sf::Color green(92, 184, 92);
    //utility

    //debug
    std::map<std::string, sf::Text> debugPanelTextNodes;
    sf::Font *openSans;
    float g_x = 0;
    float g_y = 0;
    int framesPassed = 0;
    int entitiesOnScreen = 0;
    int fps = 0;
    bool animationDebug = false;
    //debug

    void refreshTitleStats() {
        window->setTitle("Incorporated ~ [" + std::to_string(fps) + " FPS]");
    }

    void refreshDebugPanel() {
        auto mousePosition = sf::Mouse::getPosition(*window);
        auto coordMap = window->mapPixelToCoords(mousePosition);

        PROCESS_MEMORY_COUNTERS pmc = {};
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        SIZE_T mem = pmc.WorkingSetSize;

        g_x = coordMap.x;
        g_y = System::screenHeight - coordMap.y;

        fps = (int) (framesPassed / fpsClock.getElapsedTime().asSeconds());

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

        std::map<std::string, sf::Text>::iterator it;
        int i = 1;

        for (it = debugPanelTextNodes.begin(); it != debugPanelTextNodes.end(); it++) {
            it->second.setPosition(
                    convertToGLCoordinates(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - i * 12)));
            window->draw(it->second);

            i++;
        }
    }

    void initWindow() {
        auto mode = sf::Style::Close;

        if (mode == sf::Style::Fullscreen) {
            RECT w_Desktop;
            GetWindowRect(GetDesktopWindow(), &w_Desktop);

            screenWidth = (unsigned int) w_Desktop.right;
            screenHeight = (unsigned int) w_Desktop.bottom;
        }

        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, mode);
        window->setFramerateLimit(420);
        window->clear(grey);

        ViewHandler::view = new sf::View();
        ViewHandler::view->reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::view->setCenter(screenWidth / 2, screenHeight / 2);

        window->setView(*ViewHandler::view);
    }

    sf::Text createDebugString(const std::string &alias, int index) {
        sf::Text label;
        label.setPosition(convertToGLCoordinates(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - index * 12)));
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
    }

    sf::Vector2f convertToGLCoordinates(sf::Vector2f worldCoordinates) {
        worldCoordinates.y = System::screenHeight - worldCoordinates.y;
        return worldCoordinates;
    }

    sf::Vector2f convertToGLCoordinates(float x, float y) {
        return {x, System::screenHeight - y};
    }

    sf::Vector2f convertFromGLCoordinates(sf::Vector2f glCoordinates) {
        glCoordinates.y = System::screenHeight - glCoordinates.y;
        return glCoordinates;
    }

    sf::Vector2f convertFromGLCoordinates(float x, float y) {
        return {x, y - System::screenHeight};
    }

    sf::Vector2f getGlobalMouse() {
        return sf::Vector2f(System::g_x, System::g_y);
    }
}