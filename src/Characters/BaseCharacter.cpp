#include <SFML/Graphics.hpp>
#include <Animation/EntityAnimation.cpp>

class BaseCharacter : public EntityAnimation {
public:
    BaseCharacter(int x, int y) {
        sf::Texture texture;
        texture.loadFromFile("resources/braid.monster.png");
        texture.setSmooth(true);

        this->setWidth(128)

        this->setHeight(125);
        this->setSpeed(128);

        this->setX(x);
        this->setY(y);

        this->setTexture(texture);
        this->createAnimationFrames();
    }
};
