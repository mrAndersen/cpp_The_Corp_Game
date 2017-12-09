#ifndef THE_CORP_GAME_POPUPBUTTON_H
#define THE_CORP_GAME_POPUPBUTTON_H


#include <Basic/Entity.h>
#include <functional>

class PopupButton : public BasicUi {
public:
    const static int width = 100;
    const static int height = 32;

protected:
    sf::Text text;
    sf::String string;
    sf::Color color = sf::Color(255, 255, 255, 255);
    int textOffset = 0;

public:
    std::function<void(PopupButton *self)> callback;

    PopupButton();

    sf::Text &getText();

    void setText(const sf::Text &text);

    const sf::String &getString() const;

    void setString(const sf::String &string);

    void update() override;

    const sf::Color &getColor() const;

    void setColor(const sf::Color &color);
};


#endif //THE_CORP_GAME_POPUPBUTTON_H
