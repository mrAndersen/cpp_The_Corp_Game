#ifndef THE_CORP_GAME_VIEWHANDLER_H
#define THE_CORP_GAME_VIEWHANDLER_H

#include "Enum.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>

namespace ViewHandler {
    extern Direction viewDirectionMovement;
    extern sf::View *view;
    extern sf::Clock viewClock;

    extern float top;
    extern float right;
    extern float bottom;
    extern float left;
    extern float zoom;

    void handleView();

    void handleViewZoomKeyPress(sf::Event e);

    sf::Vector2f recalculateBoundaires();

    void handleViewScrollKeyPress(sf::Event e);
}
#endif //THE_CORP_GAME_VIEWHANDLER_HF