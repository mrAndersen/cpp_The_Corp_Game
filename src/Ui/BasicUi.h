#ifndef THE_CORP_GAME_BASICUI_H
#define THE_CORP_GAME_BASICUI_H


#include <Basic/Entity.h>
#include <System/ViewHandler.h>

class BasicUi : public Entity {
public:
    float leftOffset = 0;
    float topOffset = 0;

    bool pressed = false;

    BasicUi(float leftOffset, float topOffset);

    void update() override;

    bool isPressed() const;

    void setPressed(bool pressed);
};


#endif //THE_CORP_GAME_BASICUI_H
