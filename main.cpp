#include <sstream>
#include <SFML/Window/Event.hpp>
#include "System/System.h"
#include "System/ResourceLoader.h"
#include "System/ViewHandler.h"
#include "System/EntityContainer.h"
#include "System/ControlPanel.h"
#include "System/SaveManager.h"

int main() {
    auto *saveManager = new SaveManager();

    //preload resources
    ResourceLoader::loadTexturesFromFiles();
    ResourceLoader::loadFonts();
    ResourceLoader::loadNames();

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

            //entity selection
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {

                for (auto ex:EntityContainer::getItems()) {
                    if (ex->mouseIn() && ex->isSelectable() && ex->isSpawned() && ex->getLiveClock().getElapsedTime().asSeconds() >= 1) {

                        for (auto ei:EntityContainer::getItems()) {
                            if(ei != ex){
                                ei->setSelected(false);
                            }
                        }

                        ex->setSelected(!ex->isSelected());
                    }
                }
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

            if(System::debug){
                if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Numpad0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                    System::cash = 0;
                }

                if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Numpad5 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                    System::cash = 50000;
                }
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

