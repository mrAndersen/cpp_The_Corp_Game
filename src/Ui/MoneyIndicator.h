#ifndef THE_CORP_GAME_MONEYINDICATOR_H
#define THE_CORP_GAME_MONEYINDICATOR_H

#include <Basic/Entity.h>
#include "BasicUi.h"

class MoneyIndicator : public BasicUi {
    sf::Text moneyString;

public:
    const static int width = 378;
    const static int height = 136;

    explicit MoneyIndicator(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_MONEYINDICATOR_H
