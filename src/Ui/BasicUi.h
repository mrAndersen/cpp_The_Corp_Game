#ifndef THE_CORP_GAME_BASICUI_H
#define THE_CORP_GAME_BASICUI_H


#include <Basic/Entity.h>

class BasicUi : public Entity {
public:
    float leftOffset = 0;
    float topOffset = 0;

    BasicUi(float leftOffset, float topOffset);
};


#endif //THE_CORP_GAME_BASICUI_H
