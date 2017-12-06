#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

#include "Enum.h"
#include "System.h"
#include "ViewHandler.h"
#include <iostream>

namespace ViewHandler {
    Direction viewDirectionMovement = None;
    std::map<Scenes, sf::View *> views;

    float top = 0;
    float right = 0;
    float bottom = 0;
    float left = 0;
    float zoom = 1;

    void handleView() {
        int scrollSpeed = 2200;
        auto scrollDistance = (float) System::frameTimeMcs / 1000000 * scrollSpeed;

        if (viewDirectionMovement == Direction::Left) {
            if (ViewHandler::left <= (int) -System::worldWidth / 2) {
                return;
            } else {
                views[System::activeScene]->move(-scrollDistance, 0);
            }
        }

        if (viewDirectionMovement == Direction::Right) {
            if (ViewHandler::right >= (int) System::worldWidth / 2) {
                return;
            } else {
                views[System::activeScene]->move(scrollDistance, 0);
            }
        }

        if (viewDirectionMovement == Direction::Up) {
            views[System::activeScene]->move(0, -scrollDistance);
        }

        if (viewDirectionMovement == Direction::Down) {
            if (bottom > 0) {
                views[System::activeScene]->move(0, scrollDistance);
            }
        }

        if (viewDirectionMovement == Direction::UpLeft) {
            if (ViewHandler::left <= (int) -System::worldWidth / 2) {
                views[System::activeScene]->move(0, -scrollDistance);
            } else {
                views[System::activeScene]->move(-scrollDistance, -scrollDistance);
            }

        }

        if (viewDirectionMovement == Direction::UpRight) {
            if (ViewHandler::right >= (int) System::worldWidth / 2) {
                views[System::activeScene]->move(0, -scrollDistance);
            } else {
                views[System::activeScene]->move(scrollDistance, -scrollDistance);
            }
        }

        if (viewDirectionMovement == Direction::DownLeft) {
            if (ViewHandler::bottom <= 0 && ViewHandler::left <= -System::worldWidth / 2) {
                return;
            }

            if (ViewHandler::bottom > 0 && ViewHandler::left <= -System::worldWidth / 2) {
                views[System::activeScene]->move(0, scrollDistance);
            }

            if (ViewHandler::bottom <= 0 && ViewHandler::left > -System::worldWidth / 2) {
                views[System::activeScene]->move(-scrollDistance, 0);
            }

            if (ViewHandler::bottom > 0 && ViewHandler::left > -System::worldWidth / 2) {
                views[System::activeScene]->move(-scrollDistance, scrollDistance);
            }
        }

        if (viewDirectionMovement == Direction::DownRight) {
            if (ViewHandler::bottom <= 0 && ViewHandler::right >= System::worldWidth / 2) {
                return;
            }

            if (ViewHandler::bottom > 0 && ViewHandler::right >= System::worldWidth / 2) {
                views[System::activeScene]->move(0, scrollDistance);
            }

            if (ViewHandler::bottom <= 0 && ViewHandler::right < System::worldWidth / 2) {
                views[System::activeScene]->move(scrollDistance, 0);
            }

            if (ViewHandler::bottom > 0 && ViewHandler::right < System::worldWidth / 2) {
                views[System::activeScene]->move(scrollDistance, scrollDistance);
            }
        }

        auto center = recalculateBoundaries();

//        left = left * zoom;
//        right = right * zoom;
//        top = top * zoom;
//        bottom = bottom * zoom;

        //normalizer

        if (right > System::worldWidth / 2) {
            views[System::activeScene]->setCenter(System::cToGl({System::worldWidth / 2 - System::screenWidth / 2, center.y}));
        }

        if (left < -System::worldWidth / 2) {
            views[System::activeScene]->setCenter(System::cToGl({-System::worldWidth / 2 + System::screenWidth / 2, center.y}));
        }

        if (bottom < 0) {
            views[System::activeScene]->setCenter(System::cToGl({center.x, (float) System::screenHeight / 2}));
        }

        recalculateBoundaries();

        auto mousePosition = sf::Mouse::getPosition(*System::window);
        auto coordMap = System::window->mapPixelToCoords(mousePosition);

        System::g_x = coordMap.x;
        System::g_y = System::screenHeight - coordMap.y;

        System::window->setView(*views[System::activeScene]);
    }

    void handleViewZoomKeyPress(sf::Event e) {
        float delta = e.mouseWheelScroll.delta;

        if (delta > 0) {
            zoom = zoom - 0.1f;
        } else {
            zoom = zoom + 0.1f;
        }

        views[System::activeScene]->setSize(System::screenWidth * zoom, System::screenHeight * zoom);
    }

    sf::Vector2f recalculateBoundaries() {
        auto center = System::cFromGl(views[System::activeScene]->getCenter());

        left = center.x - System::screenWidth / 2;
        right = center.x + System::screenWidth / 2;
        top = center.y + System::screenHeight / 2;
        bottom = center.y - System::screenHeight / 2;

        return center;
    }

    void handleViewScrollKeyPress(sf::Event e) {

        if (e.type == sf::Event::KeyReleased) {
            viewDirectionMovement = Direction::None;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            viewDirectionMovement = Direction::Left;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            viewDirectionMovement = Direction::Right;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            viewDirectionMovement = Direction::Up;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            viewDirectionMovement = Direction::Down;
        }

        if (
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                ) {
            viewDirectionMovement = Direction::UpLeft;
        }

        if (
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                ) {
            viewDirectionMovement = Direction::UpRight;
        }

        if (
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                ) {
            viewDirectionMovement = Direction::DownLeft;
        }

        if (
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                ) {
            viewDirectionMovement = Direction::DownRight;
        }
    }
}