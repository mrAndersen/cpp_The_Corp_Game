#ifndef THE_CORP_GAME_POPUPBUTTON_H
#define THE_CORP_GAME_POPUPBUTTON_H


#include <Basic/Entity.h>

class PopupButton : public BasicUi {
public:
    const static int width = 100;
    const static int height = 32;

protected:
    sf::Text text;
    std::string string;
    sf::Color color = sf::Color(255, 255, 255, 255);
public:
    PopupButton();

    const sf::Text &getText() const;

    void setText(const sf::Text &text);

    const std::string &getString() const;

    void setString(const std::string &string);

    void update() override;

    const sf::Color &getColor() const;

    void setColor(const sf::Color &color);
};


#endif //THE_CORP_GAME_POPUPBUTTON_H
