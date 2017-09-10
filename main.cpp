#include <cmath>
#include <sstream>
#include <Characters/BaseCharacter.cpp>
#include <Deubg/Debug.cpp>
#include <System/ViewHandler.cpp>
#include <windef.h>

int main() {
    auto *debug = new Debug();
    auto *viewHandler = new ViewHandler();

    std::string title;

    unsigned int screenWidth = 1820;
    unsigned int screenHeight = 800;
    float zoomFactor = 1;

    Direction viewDirectionMovement = Direction::None;

    int framesPassed = 0;
    sf::Color grey(236, 237, 227);

    std::vector<BaseCharacter *> characters;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::Clock systemClock;

    auto *w = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, sf::Style::None | sf::Style::Close,
                                   settings);

    sf::View view(sf::FloatRect(0, 0, screenWidth, screenHeight));
    view.setCenter(screenWidth / 2, screenHeight / 2);

    w->setView(view);
    w->setFramerateLimit(300);
    w->clear(grey);

    while (w->isOpen()) {
        w->clear(grey);

        debug->setCharactersOnScreenCount(characters.size());
        debug->setFps((int) (framesPassed / systemClock.getElapsedTime().asSeconds()));

        debug->refreshTitleStats(w);
        debug->refreshDebugPanel(w);

        framesPassed++;
        sf::Event e{};

        while (w->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                w->close();
            }

            if (e.type == sf::Event::MouseMoved) {
                debug->setMouseX(e.mouseMove.x);
                debug->setMouseY(e.mouseMove.y);
            }

            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Button::Left) {
                    auto *braid = new BaseCharacter(e.mouseButton.x, e.mouseButton.y);
                    characters.push_back(braid);
                }

                if (e.mouseButton.button == sf::Mouse::Button::Right) {

                    for (auto it = characters.begin(); it != characters.end(); ++it) {
                        if (it.operator*()->contains(e.mouseButton.x, e.mouseButton.y)) {
                            characters.erase(it);
                        }
                    }

                }
            }

            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        viewDirectionMovement = Direction::Left;
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        viewDirectionMovement = Direction::Right;
                        break;
                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                        viewDirectionMovement = Direction::Up;
                        break;
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                        viewDirectionMovement = Direction::Down;
                        break;
                }
            }

            if (e.type == sf::Event::KeyReleased) {
                viewDirectionMovement = Direction::None;
            }
        }

        for (auto character : characters) {
            character->updateAnimation(w);
        }

        viewHandler->handleViewScroll(w, view, viewDirectionMovement);
        w->display();
    }
}

