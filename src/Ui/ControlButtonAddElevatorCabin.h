#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H


#include "..\Basic\Entity.h"
#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "BasicUi.h"

class ControlButtonAddElevatorCabin : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    ElevatorCabin *attachedCabin = nullptr;

    explicit ControlButtonAddElevatorCabin(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H
