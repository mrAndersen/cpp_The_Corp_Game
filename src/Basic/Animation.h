#ifndef THE_CORP_GAME_ANIMATION_H
#define THE_CORP_GAME_ANIMATION_H


#include <System/Enum.h>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <SFML/System/Clock.hpp>
#include "Entity.h"

class Entity;
class Animation {
    Entity *entity = nullptr;

    States state = S_None;
    std::vector<sf::IntRect> frames = {};

    int totalFrames = 8;
    int currentFrame = 0;
    float scale = 1.f;

    sf::Sprite sprite;
    float animationResolution = 500000;
    sf::Texture *texture;

    float width;
    float height;

    sf::Clock frameClock;
public:
    Animation(Entity *entity, States state, int totalFrames, sf::Texture *texture);

    Entity *getEntity() const;

    void setEntity(Entity *entity);

    States getState() const;

    void update();

    void setState(States state);

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

    float getAnimationResolution() const;

    void setAnimationResolution(float animationResolution);

    sf::Texture *getTexture() const;

    void setTexture(sf::Texture *texture);
};


#endif //THE_CORP_GAME_ANIMATION_H
