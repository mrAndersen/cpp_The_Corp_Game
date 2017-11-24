#ifndef THE_CORP_GAME_BASICUI_H
#define THE_CORP_GAME_BASICUI_H


#include "..\Basic\Entity.h"
#include "..\System\ViewHandler.h"

class BasicUi : public Entity {
public:
    float leftOffset = 0;
    float topOffset = 0;

    bool pressed = false;
    bool fixed = true;

    BasicUi(float leftOffset, float topOffset);

    void update() override;

    bool isPressed() const;

    void setPressed(bool pressed);

    float getLeftOffset() const;

    void setLeftOffset(float leftOffset);

    float getTopOffset() const;

    void setTopOffset(float topOffset);

    bool isFixed() const;

    void setFixed(bool fixed);
};


#endif //THE_CORP_GAME_BASICUI_H
