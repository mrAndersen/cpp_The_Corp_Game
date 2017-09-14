#ifndef THE_CORP_GAME_STATIC_H
#define THE_CORP_GAME_STATIC_H

#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Static {

protected:
    //parameters
    std::string name = "";
    sf::Vector2f worldCoordinates;

    int width = 0;
    int height = 0;

    //animation properties
    int totalFrames = 8;
    int currentFrame = 0;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape rect;

    sf::Clock clock;
    sf::Clock liveClock;

    //frame coordinates inside sprite
    std::vector<sf::IntRect> frames = {};

    //milliseconds
    float animationResolution = 500;
    float totalAnimationFrameTimeMs = 0;
    float frameTimeMs = 0;

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
    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const sf::Sprite &getSprite() const;

    void setSprite(const sf::Sprite &sprite);

    const sf::Texture &getTexture() const;

    void setTexture(const sf::Texture &texture);
};

#endif //THE_CORP_GAME_STATIC_H
