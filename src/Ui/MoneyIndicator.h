#ifndef THE_CORP_GAME_MONEYINDICATOR_H
#define THE_CORP_GAME_MONEYINDICATOR_H

#include <Basic/Entity.h>

class MoneyIndicator : public Entity {

    const static int width = 394;
    const static int height = 156;

    sf::Text moneyString;
public:
    explicit MoneyIndicator(sf::Vector2f coordinates);

    void update() override;
};


#endif //THE_CORP_GAME_MONEYINDICATOR_H
