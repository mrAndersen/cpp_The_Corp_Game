#ifndef THE_CORP_GAME_POPUP_H
#define THE_CORP_GAME_POPUP_H

#include "..\Basic\Entity.h"
#include "BasicUi.h"
#include "PopupButton.h"

class Popup : public BasicUi {
public:
    const static int width = 300;
    const static int height = 496;

    sf::Text popupText;
    std::string popupTextString;

    sf::Text popupTitle;
    std::string popupTitleString;

    std::map<std::string, PopupButton*> buttons;

    explicit Popup(float leftOffset, float topOffset);

    virtual ~Popup();

    sf::Text &getPopupText();

    void setPopupText(const sf::Text &popupText);

    const std::string &getPopupTextString() const;

    void setPopupTextString(const std::string &popupTextString);

    sf::Text &getPopupTitle();

    void setPopupTitle(const sf::Text &popupTitle);

    const std::string &getPopupTitleString() const;

    void setPopupTitleString(const std::string &popupTitleString);

    void update() override;
};


#endif //THE_CORP_GAME_POPUP_H
