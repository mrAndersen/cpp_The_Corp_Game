#ifndef THE_CORP_GAME_VIEWHANDLER_H
#define THE_CORP_GAME_VIEWHANDLER_H

#include "Enum.h"

namespace ViewHandler {
    extern float zoomFactor;
    extern Direction viewDirectionMovement;
    extern sf::View* view;
    extern sf::Clock viewClock;

    extern float top;
    extern float right;
    extern float bottom;
    extern float left;

    void handleViewScroll();

    void handleViewScrollKeyPress(sf::Event e);
}
#endif //THE_CORP_GAME_VIEWHANDLER_HF