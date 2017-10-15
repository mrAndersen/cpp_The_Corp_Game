#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H

#include "../Office/ElevatorShaft.h"

class ControlButtonAddElevator : public Entity {
    const static int width = 142;
    const static int height = 47;

    ElevatorShaft *attachedShaft = nullptr;

public:

    explicit ControlButtonAddElevator();

    void updateLogic() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
