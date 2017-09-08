#ifndef THE_CORP_GAME_BASE_CHARACTER_H
#define THE_CORP_GAME_BASE_CHARACTER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class BaseCharacter {
public:
    int x = 0;
    int y = 0;

    int width = 55;
    int height = 85;

    sf::RenderWindow renderWindow;

    BaseCharacter(const sf::RenderWindow &renderWindow, int y, int x);

    void redraw();
};

void BaseCharacter::redraw() {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    rectangle.setFillColor(sf::Color(55, 11, 255));
    rectangle.setPosition(x, y);

    renderWindow.draw(rectangle);
}

BaseCharacter::BaseCharacter(const sf::RenderWindow &renderWindow, int y, int x) {
    this->x = x;
    this->y = y;

    redraw();
}

#endif