#include <sstream>
#include <SFML/Window/Event.hpp>
#include <System/SaveManager.h>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\DebugPattern.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    std::set_terminate([](){
        exit(99);
    });

    System::activeScene = SC_Game;
//    System::activeScene = SC_Main_Menu;

    //global lightweight loading
    ResourceLoader::loadFonts();
    ResourceLoader::loadLocales();
    ResourceLoader::loadMainMenuTextures();

    if (System::activeScene == SC_Main_Menu) {
        System::loadingScene = SC_Main_Menu;
        EntityContainer::initMainMenu();
        ControlPanel::initMainMenu();
    }

    if (System::activeScene == SC_Game) {
        System::loadingScene = SC_Game;
        ResourceLoader::loadGameTextures();
        ResourceLoader::loadNames();

        EntityContainer::initBackground();
        ControlPanel::initControlPanel();

        System::loadingScene = SC_Main_Menu;
        EntityContainer::initMainMenu();
        ControlPanel::initMainMenu();

        System::loadingScene = SC_Game;
    }

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    while (System::window && System::window->isOpen()) {
        System::refreshSystem();
        sf::Event e{};

        while (System::window->pollEvent(e)) {
            System::event = e;
            System::handleGlobalLogic();

            //game loaded and menu opened
            if (System::activeScene == SC_Main_Menu && !EntityContainer::items[SC_Game].empty()) {

                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape &&
                    System::sceneChangeTimer.getElapsedTime().asMilliseconds() >= System::buttonReload) {

                    System::changeScene(SC_Game);
                }
            }

            if (System::activeScene == SC_Game) {
                EntityContainer::handleObjectSelection();

                if (
                        e.type == sf::Event::KeyPressed &&
                        e.key.code == sf::Keyboard::Escape &&
                        System::sceneChangeTimer.getElapsedTime().asMilliseconds() >= System::buttonReload
                        ) {

                    auto s = ControlPanel::mainMenu.size();
                    ControlPanel::mainMenu["resume"]->setVisible(true);
                    System::changeScene(SC_Main_Menu);
                }

                if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                    ViewHandler::handleViewScrollKeyPress(e);
                }

                if (
                        e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::S &&
                        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                        System::saveTimer.getElapsedTime().asSeconds() >= 1
                        ) {
                    SaveManager::save();
                    System::saveTimer.restart();
                }

                if (
                        e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::L &&
                        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                        System::saveTimer.getElapsedTime().asSeconds() >= 1
                        ) {
                    SaveManager::load();
                    System::saveTimer.restart();
                }
            }

            if (System::versionType == "Debug") {
                DebugPattern::process();
            }
        }


        if (System::activeScene == SC_Game) {
            System::refreshDayTime();
            ViewHandler::handleView();
        }

        if (System::activeScene == SC_Main_Menu) {
            ViewHandler::handleView();
        }

        EntityContainer::refreshEntities();
        System::refreshDebugPanel();

        System::window->display();
    }

    return 0;
}

