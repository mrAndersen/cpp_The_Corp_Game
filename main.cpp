#include <cmath>
#include <sstream>
#include <SFML/Window/Event.hpp>
#include "includes/System/System.h"
#include "includes/System/ResourceLoader.h"
#include "includes/System/ViewHandler.h"
#include "includes/System/EntityContainer.h"
#include "includes/Characters/Clerk.h"
#include "includes/System/ControlPanel.h"

int main() {
    //preload resources
    ResourceLoader::loadTexturesFromFiles();

    //load window and debug utilities
    System::initWindow();
    System::initDebug();


    EntityContainer::initGround();
    ControlPanel::initControlPanel();

    //frame loop
    while (System::window->isOpen()) {
        System::window->clear(System::grey);

        System::entitiesOnScreen = EntityContainer::size();
        System::framesPassed++;

        System::refreshTitleStats();
        System::refreshDebugPanel();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                System::window->close();
            }

            if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                ViewHandler::handleViewScrollKeyPress(e);
            }
        }

        ViewHandler::handleViewScroll();
        ControlPanel::refreshControlPanel();

        for (auto entity : EntityContainer::getItems()) {
            entity->update();
        }

        System::window->display();
    }
}

