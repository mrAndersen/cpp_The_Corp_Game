#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTMIDDLE_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTMIDDLE_H

#include "Objects/ElevatorShaftMiddle.h"

class ControlButtonAddElevatorShaftMiddle : public Entity {
    const static int width = 142;
    const static int height = 47;

    ElevatorShaftMiddle *attachedShaft = nullptr;

public:

    explicit ControlButtonAddElevatorShaftMiddle();

    void updateLogic() override;
};


#endif
