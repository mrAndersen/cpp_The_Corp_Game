#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

#include "../../includes/System/Enum.h"
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"
#include <iostream>

namespace ViewHandler {
    Direction viewDirectionMovement = Direction::None;

    sf::View *view;
    sf::Clock viewClock;

    float top = 0;
    float right = 0;
    float bottom = 0;
    float left = 0;
    float zoom = 1;

    void handleViewScroll() {
        int scrollSpeed = 30;

        if (viewClock.getElapsedTime().asMilliseconds() > 20) {
            viewClock.restart();

            if (viewDirectionMovement == Direction::Left) {
                view->move(-scrollSpeed, 0);
            }

            if (viewDirectionMovement == Direction::Right) {
                view->move(scrollSpeed, 0);
            }

            if (viewDirectionMovement == Direction::Up) {
                view->move(0, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::Down) {
                if (bottom > System::groundLevel) {
                    view->move(0, scrollSpeed);
                }
            }

            if (viewDirectionMovement == Direction::UpLeft) {
                view->move(-scrollSpeed, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::UpRight) {
                view->move(scrollSpeed, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::DownLeft) {
                if (bottom > System::groundLevel) {
                    view->move(-scrollSpeed, scrollSpeed);
                } else {
                    view->move(-scrollSpeed, 0);
                }
            }

            if (viewDirectionMovement == Direction::DownRight) {
                if (bottom > System::groundLevel) {
                    view->move(scrollSpeed, scrollSpeed);
                } else {
                    view->move(scrollSpeed, 0);
                }
            }

            auto center = System::cFromGl(ViewHandler::view->getCenter());

            left = center.x - System::screenWidth / 2;
            right = center.x + System::screenWidth / 2;
            top = center.y + System::screenHeight / 2;
            bottom = center.y - System::screenHeight / 2;

            left = left * zoom;
            right = right * zoom;
            top = top * zoom;
            bottom = bottom * zoom;

            System::window->setView(*view);
        }
    }

    void handleViewZoomKeyPress(sf::Event e) {
        float delta = e.mouseWheelScroll.delta;

        if (delta > 0) {
            zoom = zoom - 0.1f;
        } else {
            zoom = zoom + 0.1f;
        }

        view->setSize(System::screenWidth * zoom, System::screenHeight * zoom);
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