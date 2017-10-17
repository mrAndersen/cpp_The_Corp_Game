#ifndef THE_CORP_GAME_TEXTENTITY_H
#define THE_CORP_GAME_TEXTENTITY_H

#include <SFML/Graphics/Text.hpp>
#include "System/Enum.h"
#include "Animation/Entity.h"

class TextEntity : public Entity {

    sf::Text text;
    sf::Color color;

    int size;
    float speed = 100;
    float liveTimeSeconds = 5;

    //fixed offset parameters
    bool fixed = false;
    float totalEntityDistance = 0;
    float screenLeft = 0;
    float screenTop = 0;

    Direction direction = Direction::Up;

public:
    float getScreenLeft() const;

    void setScreenLeft(float screenLeft);

    float getScreenTop() const;

    void setScreenTop(float screenTop);

    bool isFixed() const;

    void setFixed(bool fixed);

    void update() override;

    void setString(const std::string &string);

    float getLiveTimeSeconds() const;

    void setLiveTimeSeconds(float liveTimeSeconds);

    Direction getDirection() const;

    float getSpeed() const;

    void setSpeed(float speed);

    void setDirection(Direction direction);

    TextEntity(const sf::Color &color, int size);

    sf::Text &getText();

    void setText(const sf::Text &text);
};


#endif //THE_CORP_GAME_TEXTENTITY_H