#include <cmath>
#include <sstream>

#include <Characters/BaseCharacter.cpp>
#include <Deubg/Debug.cpp>


int main() {
    auto *debug = new Debug();

    std::string title;

    unsigned int screenWidth = 1700;
    unsigned int screenHeight = 650;

    int framesPassed = 0;
    sf::Color grey(236,237,227);

    std::vector<BaseCharacter*> characters;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::Clock systemClock;
    auto *w = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::None | sf::Style::Close, settings);

    w->setFramerateLimit(320);
    w->clear(grey);

    while (w->isOpen()) {
        debug->refreshTitleStats(w, (int) (framesPassed / systemClock.getElapsedTime().asSeconds()));
        framesPassed++;

        sf::Event e{};

        while (w->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                w->close();
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left) {
                auto *braid = new BaseCharacter(e.mouseButton.x, e.mouseButton.y);
                characters.push_back(braid);
            }
        }

        w->clear(grey);

        for (auto character : characters) {
            character->updateAnimation(w);
        }

        w->display();
    }
}