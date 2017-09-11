
#include <cmath>
#include <sstream>
#include "Characters/Clerk.cpp"
#include "System/System.cpp"


int main() {
    //preload resources
    ResourceLoader::loadTexturesFromFiles();

    //load window and debug utilities
    sf::RenderWindow *w = System::initWindow();
    System::initDebug();

    //entities
    std::vector<Clerk *> characters;

    //frame loop
    while (w->isOpen()) {
        w->clear(System::grey);

        System::entitiesOnScreen = characters.size();
        System::framesPassed++;

        System::refreshTitleStats();
        System::refreshDebugPanel();

        sf::Event e{};

        while (w->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                w->close();
            }

            if (e.type == sf::Event::MouseMoved) {
                System::mouseX = e.mouseMove.x;
                System::mouseY = e.mouseMove.y;
            }

            if (e.type == sf::Event::MouseButtonPressed) {
                if (
                        e.mouseButton.button == sf::Mouse::Button::Left ||
                        e.mouseButton.button == sf::Mouse::Button::Right
                        ) {
                    auto *clerk = new Clerk(e.mouseButton.x, e.mouseButton.y);

                    if (e.mouseButton.button == sf::Mouse::Button::Left) {
                        clerk->setDirection(Direction::Left);
                    }

                    if (e.mouseButton.button == sf::Mouse::Button::Right) {
                        clerk->setDirection(Direction::Right);
                    }

                    characters.push_back(clerk);
                }
            }

            if (e.type == sf::Event::KeyPressed) {
                ViewHandler::handleViewScrollKeyPress(e);
            }

            if (e.type == sf::Event::KeyReleased) {
                ViewHandler::viewDirectionMovement = Direction::None;
            }
        }

        ViewHandler::handleViewScroll();

        for (auto character : characters) {
            character->updateAnimation();
        }

        w->display();
    }
}

