#ifndef THE_CORP_GAME_POPUP_H
#define THE_CORP_GAME_POPUP_H

#include "../Basic/Entity.h"
#include "BasicUi.h"
#include "PopupButton.h"

class Popup : public BasicUi {
public:
    const static int width = 300;
    const static int height = 496;

    sf::Text popupText;
    sf::Text popupTitle;

    std::map<std::string, PopupButton*> buttons;

    explicit Popup(float leftOffset, float topOffset);

    sf::Text &getPopupText();

    sf::Text &getPopupTitle();

    void update() override;

    const std::map<std::string, PopupButton *> &getButtons() const;

    void setButtons(const std::map<std::string, PopupButton *> &buttons);
};


#endif //THE_CORP_GAME_POPUP_H
