#ifndef THE_CORP_GAME_VIEWHANDLER_H
#define THE_CORP_GAME_VIEWHANDLER_H

#include "Enum.h"
#include "System.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

namespace ViewHandler {
    extern Direction viewDirectionMovement;
    extern sf::View *view;
    extern sf::Clock viewClock;

    extern float top;
    extern float right;
    extern float bottom;
    extern float left;
    extern float zoom;

    void handleViewScroll();

    void handleViewZoomKeyPress(sf::Event e);

    void handleViewScrollKeyPress(sf::Event e);
}
#endif //THE_CORP_GAME_VIEWHANDLER_HF