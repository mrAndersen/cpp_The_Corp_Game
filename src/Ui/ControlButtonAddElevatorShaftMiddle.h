#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTMIDDLE_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORSHAFTMIDDLE_H

#include "../Basic/Entity.h"
#include "../Objects/ElevatorShaftMiddle.h"
#include "BasicUi.h"
#include <climits>
#include <cmath>
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"
#include "../System/System.h"

class ControlButtonAddElevatorShaftMiddle : public BasicUi {
    const static int width = 60;
    const static int height = 62;

    ElevatorShaftMiddle *attachedShaft = nullptr;

public:
    explicit ControlButtonAddElevatorShaftMiddle(float leftOffset, float topOffset);

    void update() override;
};


#endif
