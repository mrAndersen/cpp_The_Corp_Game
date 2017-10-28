#include <sstream>
#include <SFML/Window/Event.hpp>
#include <Objects/ElevatorShaftMiddle.h>
#include <Office/OfficeClerk.h>
#include <chrono>
#include "System/System.h"
#include "System/ResourceLoader.h"
#include "System/ViewHandler.h"
#include "System/EntityContainer.h"
#include "System/ControlPanel.h"
#include "System/SaveManager.h"

int main() {
    SaveManager saveManager;
    System::seed = std::chrono::system_clock::now().time_since_epoch().count();

    //preload resources
    ResourceLoader::loadTexturesFromFiles();
    ResourceLoader::loadFonts();
    ResourceLoader::loadNames();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    EntityContainer::initBackground();
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
            System::event = e;

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
                    if (
                            !System::spawningUnit &&
                            ex->mouseIn() &&
                            ex->isSelectable() &&
                            ex->isSpawned() &&
                            ex->getLiveClock().getElapsedTime().asSeconds() >= 1
                            ) {
                        for (auto ei:EntityContainer::getItems()) {
                            if (ei != ex) {
                                ei->setSelected(false);
                            }
                        }

                        ex->setSelected(!ex->isSelected());
                    }
                }
            }

            if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                ViewHandler::handleViewScrollKeyPress(e);
                saveManager.handleSaveEvent();
            }

            if (e.type == sf::Event::MouseWheelScrolled) {
//                ViewHandler::handleViewZoomKeyPress(e);
            }

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::V) {
                System::debug = !System::debug;
            }

            if (System::debug) {
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Numpad0 &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    System::cash = 0;
                }

                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Numpad5 &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    System::cash = 50000;
                }
            }

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::F) {
                auto top = 900;

                for (int i = 0; i <= top; ++i) {

                    if ((i % 150 == 0 || i == 0) && i != top) {
                        auto a = new ElevatorShaftMiddle({775, 175 + (float) i});
                        auto a2 = new ElevatorShaftMiddle({1525, 175 + (float) i});
                        a->spawn();
                        a2->spawn();

                        auto o = new OfficeClerk({1150, 175 + (float) i});
                        o->spawn();
                    }

                    if (i == top) {
                        auto t = new ElevatorShaftTop({775, 175 + (float) i});
                        auto t2 = new ElevatorShaftTop({1525, 175 + (float) i});
                        t->spawn();
                        t2->spawn();

                        auto c = new ElevatorCabin({775, 175 + (float) (900 - 150)});
                        auto c2 = new ElevatorCabin({1525, 175 + (float) (900 - 150)});
                        c->spawn();
                        c2->spawn();
                    }
                }
            }

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::G) {
                auto count = 8;

                for (int i = 0; i < count; ++i) {
                    auto c = new Clerk({(float) 0 + (i * 72), 300.f});
                    c->spawn();
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

