#ifndef THE_CORP_GAME_POPUP_H
#define THE_CORP_GAME_POPUP_H

#include "..\Basic\Entity.h"
#include "BasicUi.h"

class Popup : public BasicUi {
public:
    const static int width = 300;
    const static int height = 500;

    sf::Text popupText;
    std::string popupTextString;

    sf::Text popupTitle;
    std::string popupTitleString;

    explicit Popup(float leftOffset, float topOffset);

    const sf::Text &getPopupText() const;

    void setPopupText(const sf::Text &popupText);

    const std::string &getPopupTextString() const;

    void setPopupTextString(const std::string &popupTextString);

    const sf::Text &getPopupTitle() const;

    void setPopupTitle(const sf::Text &popupTitle);

    const std::string &getPopupTitleString() const;

    void setPopupTitleString(const std::string &popupTitleString);

    void update() override;
};


#endif //THE_CORP_GAME_POPUP_H
