#include <sstream>
#include <SFML/Window/Event.hpp>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\DebugPattern.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    System::activeScene = SC_Main_Menu;

    //global lightweight loading
    ResourceLoader::loadFonts();
    ResourceLoader::loadLocales();

    if (System::activeScene == SC_Main_Menu) {
        ResourceLoader::loadMainMenuTextures();

        EntityContainer::initMainMenu();
        ControlPanel::initMainMenu();
    }



    //preload resources
    ResourceLoader::loadGameTextures();
    ResourceLoader::loadNames();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();





    while (System::window && System::window->isOpen()) {
        System::refreshSystem();
        sf::Event e{};

        while (System::window->pollEvent(e)) {
            System::event = e;
            System::handleGlobalLogic();

            if (System::activeScene == SC_Main_Menu) {

            }

            if (System::activeScene == SC_Game) {
                EntityContainer::handleObjectSelection();

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

