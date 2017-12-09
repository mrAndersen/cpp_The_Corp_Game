#ifndef THE_CORP_GAME_TEXTENTITY_H
#define THE_CORP_GAME_TEXTENTITY_H

#include <SFML/Graphics/Text.hpp>
#include "..\Basic\Entity.h"
#include "..\System\Enum.h"

class TextEntity : public Entity {

    sf::Text text;
    sf::Color color;

    int size;
    float speed = 100;
    float liveTimeSeconds = 5;

    //fixed offset parameters
    bool fixed = false;
    float totalEntityDistance = 0;

    float leftOffset;
    float topOffset;

public:
    float getLeftOffset() const;

    void setLeftOffset(float leftOffset);

    float getTopOffset() const;

    void setTopOffset(float topOffset);

    bool isFixed() const;

    void setFixed(bool fixed);

    void updateLogic() override;

    void setString(const sf::String &string);

    float getLiveTimeSeconds() const;

    void setLiveTimeSeconds(float liveTimeSeconds);

    float getSpeed() const;

    void setSpeed(float speed);

    TextEntity(const sf::Color &color, int size);

    sf::Text &getText();

    void setText(const sf::Text &text);
};


#endif //THE_CORP_GAME_TEXTENTITY_H
