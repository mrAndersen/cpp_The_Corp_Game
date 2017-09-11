#include "ViewHandler.h"
#include "System.h"

void ViewHandler::handleViewScroll() {
    int frameTimeMs = System::systemClock.restart().asMilliseconds();
    int scrollSpeed = 2;

    if (frameTimeMs > 800) {
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
    }

    System::window->setView(view);
}

void ViewHandler::handleViewScrollKeyPress(sf::Event e) {

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