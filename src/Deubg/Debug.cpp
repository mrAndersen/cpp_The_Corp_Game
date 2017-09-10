#include <SFML/Graphics.hpp>

class Debug {
public:
    void refreshTitleStats(sf::RenderWindow *w, int fps) {
        w->setTitle("New world [" + std::to_string(fps) + "]");
    }
};
