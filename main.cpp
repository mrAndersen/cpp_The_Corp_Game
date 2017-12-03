#include <sstream>
#include <SFML/Window/Event.hpp>
#include "src\Objects\ElevatorShaftMiddle.h"
#include "src\System\ResourceLoader.h"
#include "src\System\ViewHandler.h"
#include "src\System\EntityContainer.h"
#include "src\System\ControlPanel.h"
#include "src\System\DebugPattern.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {


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

    DebugPattern::prepareDebug();

    while (System::window && System::window->isOpen()) {
        System::refreshSystem();
        System::refreshDayTime();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            System::event = e;

            System::handleGlobalLogic();


            if (System::activeScene == Scenes::SC_Game) {
                System::selectionAllowed = !System::spawningUnit &&
                                           System::selectionCooldown.getElapsedTime().asMilliseconds() >=
                                           System::buttonReload;

                EntityContainer::handleObjectSelection();

                if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                    ViewHandler::handleViewScrollKeyPress(e);
                }

                if (System::version == 0) {
                    DebugPattern::process();
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

