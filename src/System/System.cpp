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
        int mouseX = mousePosition.x;
        int mouseY = mousePosition.y;

        auto coordMap = window->mapPixelToCoords(mousePosition);

        g_x = coordMap.x;
        g_y = System::screenHeight - coordMap.y;

        fps = (int) (framesPassed / fpsClock.getElapsedTime().asSeconds());

        debugPanelTextNodes["global_coordinates"].setString("g_x:" + std::to_string(g_x) + " g_y:" + std::to_string(g_y));
        window->draw(debugPanelTextNodes["global_coordinates"]);

        debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
        window->draw(debugPanelTextNodes["fps"]);

        debugPanelTextNodes["mouse"].setString("m_x:" + std::to_string(mouseX) + " m_y:" + std::to_string(mouseY));
        window->draw(debugPanelTextNodes["mouse"]);

        debugPanelTextNodes["entity_count"].setString("e_count: " + std::to_string(entitiesOnScreen));
        window->draw(debugPanelTextNodes["entity_count"]);

        debugPanelTextNodes["view_direction"].setString("v_direction: " + std::to_string(ViewHandler::viewDirectionMovement));
        window->draw(debugPanelTextNodes["view_direction"]);
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

    void initDebug() {
        openSans.loadFromFile("resources/fonts/open-sans.ttf");

        //Mouse Coordinates
        sf::Text t_fps;
        t_fps.setPosition(20, 20);
        t_fps.setFillColor(sf::Color::Black);
        t_fps.setFont(openSans);
        t_fps.setCharacterSize(10);
        debugPanelTextNodes["fps"] = t_fps;

        //Mouse Coordinates
        sf::Text t_mouse;
        t_mouse.setPosition(20, 40);
        t_mouse.setFillColor(sf::Color::Black);
        t_mouse.setFont(openSans);
        t_mouse.setCharacterSize(10);
        debugPanelTextNodes["mouse"] = t_mouse;

        //Entites count
        sf::Text t_entity_count;
        t_entity_count.setPosition(20, 60);
        t_entity_count.setFillColor(sf::Color::Black);
        t_entity_count.setFont(openSans);
        t_entity_count.setCharacterSize(10);
        debugPanelTextNodes["entity_count"] = t_entity_count;

        //View direction
        sf::Text t_view_direction;
        t_view_direction.setPosition(20, 80);
        t_view_direction.setFillColor(sf::Color::Black);
        t_view_direction.setFont(openSans);
        t_view_direction.setCharacterSize(10);
        debugPanelTextNodes["view_direction"] = t_view_direction;

        //Global coordinates
        sf::Text t_global_coordinates;
        t_global_coordinates.setPosition(20, 100);
        t_global_coordinates.setFillColor(sf::Color::Black);
        t_global_coordinates.setFont(openSans);
        t_global_coordinates.setCharacterSize(10);
        debugPanelTextNodes["global_coordinates"] = t_global_coordinates;
    }
}