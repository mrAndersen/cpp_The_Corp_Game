#ifndef THE_CORP_GAME_BUTTON5X_H
#define THE_CORP_GAME_BUTTON5X_H

#include "Button5x.h"

class Button5x : public BasicUi {
public:
    const static int width = 52;
    const static int height = 42;

    Button5x(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_BUTTON5X_H
