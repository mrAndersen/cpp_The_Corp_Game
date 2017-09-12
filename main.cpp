#include <cmath>
#include <sstream>
#include <SFML/Window/Event.hpp>
#include "includes/System/System.h"
#include "includes/System/ResourceLoader.h"
#include "includes/System/ViewHandler.h"
#include "includes/Characters/Clerk.h"

int main() {
    //preload resources
    ResourceLoader::loadTexturesFromFiles();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    //entities
    std::vector<Clerk *> characters;

    //frame loop
    while (System::window->isOpen()) {
        System::window->clear(System::grey);

        System::entitiesOnScreen = characters.size();
        System::framesPassed++;

        System::refreshTitleStats();
        System::refreshDebugPanel();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                System::window->close();
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

        System::window->display();
    }
}

