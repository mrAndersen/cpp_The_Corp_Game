#include <SFML/Window/Mouse.hpp>
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"

namespace System {
    unsigned int screenWidth = 1820;
    unsigned int screenHeight = 800;
    std::string title = "New World";

    //sys
    sf::Clock fpsClock;
    sf::RenderWindow *window;
    //sys

    //utility
    sf::Color grey(236, 237, 227);
    sf::Color red(248, 215, 227);
    //utility

    //debug
    std::map<std::string, sf::Text> debugPanelTextNodes;
    sf::Font openSans;
    float g_x = 0;
    float g_y = 0;
    int framesPassed = 0;
    int entitiesOnScreen = 0;
    int fps = 0;
    bool animationDebug = true;
    //debug

    void refreshTitleStats() {
        window->setTitle("New world [" + std::to_string(fps) + " FPS]");
    }

    void refreshDebugPanel() {
        auto mousePosition = sf::Mouse::getPosition(*window);
        auto coordMap = window->mapPixelToCoords(mousePosition);

        g_x = coordMap.x;
        g_y = System::screenHeight - coordMap.y;

        fps = (int) (framesPassed / fpsClock.getElapsedTime().asSeconds());

        debugPanelTextNodes["g_coordinates"].setString("global: {" + std::to_string((int)g_x) + "," + std::to_string((int)g_y) + "}");
        debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
        debugPanelTextNodes["mouse"].setString("mouse: {" + std::to_string(mousePosition.x) + "," + std::to_string(mousePosition.y) + "}");
        debugPanelTextNodes["entity_count"].setString("entities: " + std::to_string(entitiesOnScreen));
        debugPanelTextNodes["v_direction"].setString("v_direction: " + std::to_string(ViewHandler::viewDirectionMovement));

        std::map<std::string, sf::Text>::iterator it;
        for (it = debugPanelTextNodes.begin(); it != debugPanelTextNodes.end(); it++) {
            window->draw(it->second);
        }
    }

    void initWindow() {
        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::Close);
        window->setFramerateLimit(300);
        window->clear(grey);

        ViewHandler::view = window->getDefaultView();
        ViewHandler::view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::view.setCenter(screenWidth / 2, screenHeight / 2);

        window->setView(ViewHandler::view);
    }

    sf::Text createDebugString(const std::string &alias, int index) {
        sf::Text label;
        label.setPosition(convertToGLCoordinates(sf::Vector2f(12, System::screenHeight - index * 12)));
        label.setFillColor(sf::Color::Black);
        label.setFont(openSans);
        label.setCharacterSize(10);

        debugPanelTextNodes[alias] = label;
        return label;
    }

    sf::Vector2f convertToGLCoordinates(sf::Vector2f worldCoordinates) {
        worldCoordinates.y = System::screenHeight - worldCoordinates.y;
        return worldCoordinates;
    }

    sf::Vector2f convertToGLCoordinates(float x, float y) {
        return {x, System::screenHeight - y};
    }

    void initDebug() {
        openSans.loadFromFile("resources/fonts/open-sans.ttf");

        createDebugString("fps", 1);
        createDebugString("g_coordinates", 2);
        createDebugString("mouse", 3);
        createDebugString("entity_count", 4);
        createDebugString("v_direction", 5);
    }
}