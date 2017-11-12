#include <sstream>
#include "src\Component\Destination.h"
#include <SFML/Window/Event.hpp>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\Office\OfficeClerk.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\SaveManager.h"
#include "src\System\DebugPattern.h"
#include "src/Characters/Clerk.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    SaveManager saveManager;
//    System::seed = std::chrono::system_clock::now().time_since_epoch().count();

    //preload resources
    ResourceLoader::loadTexturesFromFiles();
    ResourceLoader::loadFonts();
    ResourceLoader::loadNames();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

//    EntityContainer::initBackground();
    EntityContainer::initGrid();
    ControlPanel::initControlPanel();

    while (System::window && System::window->isOpen()) {
        System::window->clear(System::c_background);
        System::entitiesOnScreen = EntityContainer::size();

        System::refreshDebugPanel();
        System::refreshSystem();
        System::refreshDayTime();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            System::event = e;

            System::eventDeque.push_front(e);

            if(System::eventDeque.size() >= 5){
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

            //entity selection
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                for (auto ex:EntityContainer::items) {
                    if (
                            !System::spawningUnit &&
                            ex->mouseIn() &&
                            ex->isSelectable() &&
                            ex->isSpawned() &&
                            ex->getLiveClock().getElapsedTime().asSeconds() >= 1
                            ) {

                        for (auto ei:EntityContainer::items) {
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
        ControlPanel::refreshControlPanel();

        EntityContainer::refreshVertices();
        EntityContainer::refreshEntities();

        System::window->display();
    }

    return 0;
}

