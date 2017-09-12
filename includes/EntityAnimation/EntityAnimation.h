#ifndef THE_CORP_GAME_ENTITYANIMATION_CPP_H
#define THE_CORP_GAME_ENTITYANIMATION_CPP_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../System/Enum.h"

class EntityAnimation {
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const sf::Sprite &getSprite() const;

    void setSprite(const sf::Sprite &sprite);

    const sf::Texture &getTexture() const;

    void setTexture(const sf::Texture &texture);

    float getAnimationResolution() const;

    void setAnimationResolution(float animationResolution);

    float getSpeed() const;

    void setSpeed(float speed);

protected:
    std::string name = "";

    float x = 0;
    float y = 0;

    int width = 0;
    int height = 0;

    int totalFrames = 8;
    int currentFrame = 0;

    Direction direction = Direction::Right;

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Time timeSinceCreation;
    sf::Clock clock;

    //frame coordinates inside sprite
    std::vector<sf::IntRect> frames;

    //milliseconds
    float animationResolution = 500;
    float totalAnimationFrameTimeMs = 0;
    float frameTimeMs = 0;

    //pixels per second
    float speed = 120;

    void renderCurrentFrame();

public:
    bool contains(float x, float y);

    void updateFrameTime();

    bool isAnimationResolutionReached();

    void createAnimationFrames();

    void updateAnimation();

    Direction getDirection() const;

    void setDirection(Direction direction);
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
