#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"

namespace System {
    unsigned int screenWidth = 1820;
    unsigned int screenHeight = 800;
    std::string title = "New World";

    //sys
    sf::Time systemTime;
    sf::Clock systemClock;
    sf::RenderWindow *window;
    //sys

    //utility
    sf::Color grey(236, 237, 227);
    //utility

    //debug
    std::map<std::string, sf::Text> debugPanelTextNodes;
    sf::Font openSans;
    int mouseX = 0;
    int mouseY = 0;
    int framesPassed = 0;
    int entitiesOnScreen = 0;
    int fps = 0;
    //debug

    void refreshTitleStats() {
        window->setTitle("New world [" + std::to_string(fps) + " FPS]");
    }

    void refreshDebugPanel() {
        fps = (int) (framesPassed / systemTime.asSeconds());

        debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
        window->draw(debugPanelTextNodes["fps"]);

        debugPanelTextNodes["mouse"].setString("x:" + std::to_string(mouseX) + " y:" + std::to_string(mouseY));
        window->draw(debugPanelTextNodes["mouse"]);

        debugPanelTextNodes["characters_count"].setString("characters: " + std::to_string(entitiesOnScreen));
        window->draw(debugPanelTextNodes["characters_count"]);

        debugPanelTextNodes["view_direction"].setString("direction: " + std::to_string(ViewHandler::viewDirectionMovement));
        window->draw(debugPanelTextNodes["view_direction"]);
    }

    void initWindow() {
        systemTime = sf::Time::Zero;
        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::Close);

        ViewHandler::view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::view.setCenter(screenWidth / 2, screenHeight / 2);

        //full rect
        ViewHandler::view.setViewport(sf::FloatRect(0, 0, 1, 1));

        window->setView(ViewHandler::view);
        window->setFramerateLimit(300);
        window->clear(grey);
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

        //Mouse Coordinates
        sf::Text t_characters_count;
        t_characters_count.setPosition(20, 60);
        t_characters_count.setFillColor(sf::Color::Black);
        t_characters_count.setFont(openSans);
        t_characters_count.setCharacterSize(10);
        debugPanelTextNodes["characters_count"] = t_characters_count;

        //View direction
        sf::Text t_view_direction;
        t_view_direction.setPosition(20, 80);
        t_view_direction.setFillColor(sf::Color::Black);
        t_view_direction.setFont(openSans);
        t_view_direction.setCharacterSize(10);
        debugPanelTextNodes["view_direction"] = t_view_direction;
    }
}