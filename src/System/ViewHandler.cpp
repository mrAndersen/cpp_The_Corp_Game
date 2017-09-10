#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/View.hpp>
#include <System/Direction.h>
#include <SFML/Graphics/RenderWindow.hpp>

class ViewHandler {
protected:
    sf::Clock viewScrollClock;
public:
    sf::View handleViewScroll(sf::RenderWindow *w, sf::View &view, Direction &viewDirectionMovement) {
        int frameTimeMs = viewScrollClock.restart().asMilliseconds();

        if (frameTimeMs > 20) {
            if (viewDirectionMovement == Direction::Left) {
                view.move(-2, 0);
            }

            if (viewDirectionMovement == Direction::Right) {
                view.move(2, 0);
            }

            if (viewDirectionMovement == Direction::Up) {
                view.move(0, -2);
            }

            if (viewDirectionMovement == Direction::Down) {
                view.move(0, 2);
            }
        }

        w->setView(view);
    }
};
