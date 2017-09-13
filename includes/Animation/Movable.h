#ifndef THE_CORP_GAME_ENTITYANIMATION_CPP_H
#define THE_CORP_GAME_ENTITYANIMATION_CPP_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../System/Enum.h"

class Movable {

protected:
    //parameters
    std::string name = "";
    sf::Vector2f worldCoordinates;

    int width = 0;
    int height = 0;

    float health = 100;
    float distancePassed = 0;

    //animation properties
    int totalFrames = 8;
    int currentFrame = 0;

    Direction direction = Direction::Right;

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Clock clock;
    sf::Clock liveClock;

    //frame coordinates inside sprite
    std::vector<sf::IntRect> frames = {};

    //milliseconds
    float animationResolution = 500;
    float totalAnimationFrameTimeMs = 0;
    float frameTimeMs = 0;

    //pixels per second
    float speed = 0;

    void renderCurrentFrame();

public:
    bool clicked(sf::Vector2f targetCoordinates);

    void updateFrameTime();

    bool isAnimationResolutionReached();

    void createAnimationFrames();

    void update();

    void updateAnimation();

    void updateLogic();

public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    Direction getDirection() const;

    void setDirection(Direction direction);

    float getSpeed() const;

    void setSpeed(float speed);

    const sf::Texture &getTexture() const;

    void setTexture(const sf::Texture &texture);
};

#endif //THE_CORP_GAME_ENTITYANIMATION_CPP_H
