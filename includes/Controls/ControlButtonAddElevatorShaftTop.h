#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTTOP_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTTOP_H

#include "../Office/ElevatorShaftMiddle.h"
#include "../Office/ElevatorShaftTop.h"

class ControlButtonAddElevatorShaftTop : public Entity {
    const static int width = 142;
    const static int height = 47;

    ElevatorShaftTop *attachedShaft = nullptr;
public:
    explicit ControlButtonAddElevatorShaftTop();

    void updateLogic() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H