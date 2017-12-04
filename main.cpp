#include <sstream>
#include <SFML/Window/Event.hpp>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\DebugPattern.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    System::activeScene = SC_Game;
    System::loadingScene = SC_Game;

    //global lightweight loading
    ResourceLoader::loadFonts();
    ResourceLoader::loadLocales();
    ResourceLoader::loadMainMenuTextures();

    if (System::activeScene == SC_Main_Menu) {
        EntityContainer::initMainMenu();
        ControlPanel::initMainMenu();
    }

    if (System::activeScene == SC_Game) {
        ResourceLoader::loadGameTextures();
        ResourceLoader::loadNames();

        EntityContainer::initBackground();
        ControlPanel::initControlPanel();
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

//                ControlPanel::mainMenu["resume"]->setVisible(true);
            }

            if (System::activeScene == SC_Game) {
                EntityContainer::handleObjectSelection();

                if (
                        e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape &&
                        System::sceneChangeTimer.getElapsedTime().asMilliseconds() >= System::buttonReload
                        ) {

                    System::changeScene(SC_Main_Menu);
                }

                if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                    ViewHandler::handleViewScrollKeyPress(e);
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

