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

    //load window and debug utilities
    System::initWindow();
    System::initDebug();

    EntityContainer::initGround();
    EntityContainer::initGrid();

    ControlPanel::initControlPanel();

    //frame loop
    while (System::window->isOpen()) {
        System::window->clear(System::c_background);

        System::entitiesOnScreen = EntityContainer::size();
        System::framesPassed++;

        System::refreshTitleStats();
        System::refreshDebugPanel();
        System::refreshDayTime();

        sf::Event e{};

        while (System::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                System::window->close();
            }

            if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
                ViewHandler::handleViewScrollKeyPress(e);
                saveManager->handleSaveEvent();
            }

            if (e.type == sf::Event::MouseWheelScrolled) {
//                ViewHandler::handleViewZoomKeyPress(e);
            }

            if (e.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                for (int i = 0; i <= 50; i++) {
                    auto *clerk = new Clerk(System::window->getDefaultView().getCenter());
                }
            }
        }

        ViewHandler::handleViewScroll();
        ControlPanel::refreshControlPanel();

        EntityContainer::refreshVertices();

        for (auto entity : EntityContainer::getItems()) {
            entity->update();
        }

        System::window->display();
    }
}

