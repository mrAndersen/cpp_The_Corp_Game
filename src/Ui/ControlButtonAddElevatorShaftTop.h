#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTTOP_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTTOP_H

#include "Objects/ElevatorShaftMiddle.h"
#include "Objects/ElevatorShaftTop.h"
#include "BasicUi.h"

class ControlButtonAddElevatorShaftTop : public BasicUi {
    const static int width = 60;
    const static int height = 62;

    ElevatorShaftTop *attachedShaft = nullptr;
public:
    explicit ControlButtonAddElevatorShaftTop(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H