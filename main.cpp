#include <sstream>
#include <SFML/Window/Event.hpp>
#include "includes/System/System.h"
#include "includes/System/ResourceLoader.h"
#include "includes/System/ViewHandler.h"
#include "includes/System/EntityContainer.h"
#include "includes/System/ControlPanel.h"
#include "includes/System/SaveManager.h"

int main() {
    auto *saveManager = new SaveManager();

    //preload resources
    ResourceLoader::loadTexturesFromFiles();
    ResourceLoader::loadFonts();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    EntityContainer::initGround();
    EntityContainer::initGrid();

    ControlPanel::initControlPanel();

    //frame loop
    while (System::window && System::window->isOpen()) {
        System::window->clear(System::c_background);

        System::entitiesOnScreen = EntityContainer::size();

        System::refreshDebugPanel();
        System::refreshSystem();
        System::refreshDayTime();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                System::window->close();
            }

            if (e.type == sf::Event::Resized) {
                System::screenWidth = System::window->getSize().x;
                System::screenHeight = System::window->getSize().y;

                System::initWindow();
            }

            if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                ViewHandler::handleViewScrollKeyPress(e);
                saveManager->handleSaveEvent();
            }

            if (e.type == sf::Event::MouseWheelScrolled) {
//                ViewHandler::handleViewZoomKeyPress(e);
            }

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::V) {
                System::debug = !System::debug;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                for (int i = 0; i <= 1; i++) {
                    auto *clerk = new Clerk(System::window->getDefaultView().getCenter());
                }
            }

            if (
                    System::timeFactor < 10 &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                System::timeFactor++;
            }

            if (
                    System::timeFactor > 0 &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                System::timeFactor--;
            }

            if (e.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                auto boundaries = System::getScreenBoundaries();

                switch (System::screenMode) {
                    case sf::Style::Default:
                        System::screenMode = sf::Style::Fullscreen;
                        System::initWindow();
                        break;
                    case sf::Style::Fullscreen:
                        System::screenMode = sf::Style::Default;

                        System::screenWidth = (unsigned int) boundaries.right * 8 / 10;
                        System::screenHeight = (unsigned int) boundaries.bottom * 4 / 5;

                        System::initWindow();
                    default:
                        break;
                }
            }
        }

        ViewHandler::handleViewScroll();
        ControlPanel::refreshControlPanel();

        EntityContainer::refreshVertices();
        EntityContainer::refreshEntities();

        System::window->display();
    }
}

