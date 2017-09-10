#include <SFML/Graphics.hpp>
#include <Animation/CharacterAnimation.cpp>

class BaseCharacter : public CharacterAnimation {
public:
    BaseCharacter(int x, int y) {
        sf::Texture texture;
        texture.loadFromFile("resources/braid.monster.png");
        texture.setSmooth(true);

        this->setWidth(128);
        this->setHeight(125);

        this->setX(x);
        this->setY(y);

        this->setTexture(texture);
        this->createAnimationFrames();
    }
};
