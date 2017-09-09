#include <Characters/BaseCharacter.cpp>
#include <SFML/Graphics.hpp>


int main(int argc, char *argv[]) {
    std::string title = "New world";

    unsigned int screenWidth = 1700;
    unsigned int screenHeight = 650;


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow w(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::None | sf::Style::Close, settings);

    w.setFramerateLimit(60);
    w.clear(sf::Color::White);

    while (w.isOpen()) {
        sf::Event e{};

        while (w.pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                w.close();
            }

        }

        BaseCharacter fatMan(w, e.mouseButton.x, e.mouseButton.y);

        w.display();
    }
}