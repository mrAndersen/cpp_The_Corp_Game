#ifndef THE_CORP_GAME_ENTITY_H
#define THE_CORP_GAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

class Entity {

protected:
    //parameters
    std::string name = "";
    float health = 100;

    sf::Vector2f worldCoordinates;
    int width = 0;
    int height = 0;

    //animation properties
    std::vector<sf::IntRect> frames = {};
    int totalFrames = 8;
    int currentFrame = 0;
    float scale = 1.f;
    sf::Sprite sprite;
    sf::Texture* texture;
    int drawOrder = 1;

    sf::Clock frameClock;
    sf::Clock liveClock;

    //milliseconds
    float animationResolution = 500;
    float totalAnimationFrameTimeMs = 0;
    float frameTimeMs = 0;

    //property map
    std::map<std::string, int> properties;

public:
    void createAnimationFrames();

    void updateFrameTime();

    bool isAnimationResolutionReached();

    void update();

    void updateAnimation();

    virtual void renderCurrentFrame();

    bool mouseIn();

    bool leftClicked();

    bool rightClicked();

    bool leftClickedOutside();

    bool rightClickedOutside();

    void setTransparent();

    void removeTransparency();

    virtual void updateLogic();
public:
    int getDrawOrder() const;

    void setDrawOrder(int drawOrder);

    const std::string &getName() const;

    void setName(const std::string &name);

    float getHealth() const;

    void setHealth(float health);

    const sf::Vector2f &getWorldCoordinates() const;

    void setWorldCoordinates(const sf::Vector2f &worldCoordinates);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const std::vector<sf::IntRect> &getFrames() const;

    void setFrames(const std::vector<sf::IntRect> &frames);

    int getTotalFrames() const;

    void setTotalFrames(int totalFrames);

    int getCurrentFrame() const;

    void setCurrentFrame(int currentFrame);

    float getScale() const;

    void setScale(float scale);

    sf::Sprite &getSprite();

    void setSprite(const sf::Sprite &sprite);

    sf::Texture *getTexture() const;

    void setTexture(sf::Texture *texture);

    const sf::Clock &getLiveClock() const;

    void setLiveClock(const sf::Clock &liveClock);

    float getAnimationResolution() const;

    void setAnimationResolution(float animationResolution);

    float getTotalAnimationFrameTimeMs() const;

    void setTotalAnimationFrameTimeMs(float totalAnimationFrameTimeMs);

    float getFrameTimeMs() const;

    void setFrameTimeMs(float frameTimeMs);

    void setInvalid();

    std::string serialize();
};


#endif //THE_CORP_GAME_ENTITY_H
