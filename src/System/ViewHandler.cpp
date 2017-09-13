#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

#include "../../includes/System/Enum.h"
#include "../../includes/System/System.h"
#include "../../includes/System/ViewHandler.h"

namespace ViewHandler {
    float zoomFactor = 1.f;
    Direction viewDirectionMovement = Direction::None;

    sf::View view;
    sf::Clock viewClock;

    void handleViewScroll() {
        int scrollSpeed = 20;

        if(viewClock.getElapsedTime().asMilliseconds() > 20){
            viewClock.restart();

            if (viewDirectionMovement == Direction::Left) {
                view.move(-scrollSpeed, 0);
            }

            if (viewDirectionMovement == Direction::Right) {
                view.move(scrollSpeed, 0);
            }

            if (viewDirectionMovement == Direction::Up) {
                view.move(0, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::Down) {
                view.move(0, scrollSpeed);
            }

            if (viewDirectionMovement == Direction::UpLeft) {
                view.move(-scrollSpeed, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::UpRight) {
                view.move(scrollSpeed, -scrollSpeed);
            }

            if (viewDirectionMovement == Direction::DownLeft) {
                view.move(-scrollSpeed, scrollSpeed);
            }

            if (viewDirectionMovement == Direction::DownRight) {
                view.move(scrollSpeed, scrollSpeed);
            }

            System::window->setView(view);
        }
    }

    void handleViewScrollKeyPress(sf::Event e) {

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