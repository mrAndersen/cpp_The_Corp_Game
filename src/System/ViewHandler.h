#ifndef THE_CORP_GAME_VIEWHANDLER_H
#define THE_CORP_GAME_VIEWHANDLER_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include "Enum.h"

namespace ViewHandler {
    static float zoomFactor = 1;
    static Direction viewDirectionMovement = Direction::None;
    static sf::View view;

    static void handleViewScroll();

    static void handleViewScrollKeyPress(sf::Event e);
}

#endif //THE_CORP_GAME_VIEWHANDLER_H
