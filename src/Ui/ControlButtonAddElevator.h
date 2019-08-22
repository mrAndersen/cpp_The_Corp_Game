#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H

#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"
#include "../System/ViewHandler.h"
#include "../System/System.h"
#include "../System/ControlPanel.h"
#include "BasicUi.h"

class ControlButtonAddElevator : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    ControlButtonAddElevator(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
