#ifndef THE_CORP_GAME_CONTROLTIMEINDICATOR_H
#define THE_CORP_GAME_CONTROLTIMEINDICATOR_H


#include "Text/TextEntity.h"

class ControlTimeIndicator : public TextEntity {
public:
    ControlTimeIndicator(const sf::Color &color, int size);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLTIMEINDICATOR_H
