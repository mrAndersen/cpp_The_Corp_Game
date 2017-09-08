#ifndef THE_CORP_GAME_WORLD_H
#define THE_CORP_GAME_WORLD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Characters/BaseCharacter.h>

using namespace std;

class World {
public:
    std::string title = "New brave world";

    int width = 50000;
    int height = 6000;

    unsigned int screenWidth;
    unsigned int screenHeight;

    sf::RenderWindow worldWindow;

    explicit World(unsigned int width = 1700, unsigned int height = 750);

    sf::RenderWindow start();
};

sf::RenderWindow World::start() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    worldWindow(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::None | sf::Style::Close,
                                 settings);


    while (worldWindow.isOpen()) {
        sf::Event event{};

        while (worldWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                worldWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    BaseCharacter _fat(worldWindow, 300, 300);
//                    worldWindow.close();
                }
            }
        }

        worldWindow.display();
    }


}

World::World(unsigned int width, unsigned int height) {
    screenWidth = width;
    screenHeight = height;
}

#endif
