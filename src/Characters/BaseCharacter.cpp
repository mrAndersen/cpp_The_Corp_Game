#include <SFML/Graphics.hpp>

class BaseCharacter {
public:
    int x = 0;
    int y = 0;

    int width = 55;
    int height = 85;

    BaseCharacter(sf::RenderWindow &w, int y, int x) {
        this->x = x;
        this->y = y;

        draw(w);
    }

    void draw(sf::RenderWindow &w) {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));

        rectangle.setFillColor(sf::Color(55, 11, 255));
        rectangle.setPosition(x, y);

        w.draw(rectangle);
    }

    virtual ~BaseCharacter() = default;
};
