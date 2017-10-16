#ifndef THE_CORP_GAME_CONTROLCASHINDICATOR_H
#define THE_CORP_GAME_CONTROLCASHINDICATOR_H


#include "Text/TextEntity.h"

class ControlCashIndicator : public TextEntity {
public:
    ControlCashIndicator(const sf::Color &color, int size);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLCASHINDICATOR_H
