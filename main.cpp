#include <cmath>
#include <sstream>
#include <SFML/Window/Event.hpp>
#include "includes/System/System.h"
#include "includes/System/ResourceLoader.h"
#include "includes/System/ViewHandler.h"
#include "includes/System/EntityContainer.h"
#include "includes/Characters/Clerk.h"
#include <iostream>

int main() {
    //preload resources
    ResourceLoader::loadTexturesFromFiles();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

//    EntityContainer::initGround();

    //frame loop
    while (System::window->isOpen()) {
        System::window->clear(System::grey);

        System::entitiesOnScreen = EntityContainer::movableSize() + EntityContainer::staticSize();
        System::framesPassed++;

        System::refreshTitleStats();
        System::refreshDebugPanel();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                System::window->close();
            }

            if (e.type == sf::Event::MouseButtonPressed) {
                if (
                        e.mouseButton.button == sf::Mouse::Button::Left ||
                        e.mouseButton.button == sf::Mouse::Button::Right
                        ) {

                    for (int i = 0; i < 100 ; ++i) {
                        auto *clerk = new Clerk(sf::Vector2f(System::g_x, System::g_y));

                        if (e.mouseButton.button == sf::Mouse::Button::Left) {
                            clerk->setDirection(Direction::Left);
                        }

                        if (e.mouseButton.button == sf::Mouse::Button::Right) {
                            clerk->setDirection(Direction::Right);
                        }

                        EntityContainer::addMovable(clerk);
                    }
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

        for (auto static_ : EntityContainer::getStaticItems()) {
            static_->update();
        }


        for (auto movable : EntityContainer::getMovableItems()) {
            movable->update();
        }


        System::window->display();
    }
}

