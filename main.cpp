#include <sstream>
#include <SFML/Window/Event.hpp>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\SaveManager.h"
#include "src\System\DebugPattern.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    SaveManager saveManager;

    //preload resources
    ResourceLoader::loadTexturesFromFiles();
    ResourceLoader::loadFonts();
    ResourceLoader::loadLocales();
    ResourceLoader::loadNames();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    EntityContainer::initBackground();
    ControlPanel::initControlPanel();

    while (System::window && System::window->isOpen()) {
        System::refreshSystem();
        System::refreshDayTime();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            System::event = e;

            System::eventDeque.push_front(e);

            if (System::eventDeque.size() >= 5) {
                System::eventDeque.pop_back();
            }

            if (e.type == sf::Event::Closed) {
                System::window->close();
            }

            if (e.type == sf::Event::Resized) {
                System::screenWidth = System::window->getSize().x;
                System::screenHeight = System::window->getSize().y;

                System::initWindow();
            }

            System::selectionAllowed = !System::spawningUnit && System::selectionCooldown.getElapsedTime().asMilliseconds() >= System::buttonReload;

            //entity selection
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && System::selectionAllowed) {
                for (auto ei:EntityContainer::items) {
                    if(!ei->mouseIn() && ei->isSelectable()){
                        ei->setSelected(false);
                        ei->setNormal();
                    }
                }

                for(auto it = EntityContainer::items.rbegin(); it != EntityContainer::items.rend(); ++it){
                    auto ex = *it;

                    if (
                            ex->mouseIn() &&
                            ex->isSelectable() &&
                            ex->isSpawned() &&
                            ex->getLiveClock().getElapsedTime().asMilliseconds() >= System::buttonReload
                            ) {
                        ex->setSelected(!ex->isSelected());
                        break;
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

            DebugPattern::process();

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
        EntityContainer::refreshEntities();

        System::refreshDebugPanel();
        System::window->display();
    }

    return 0;
}

