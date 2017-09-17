//
// Created by AMD_PC on 17.09.2017.
//

#ifndef THE_CORP_GAME_CONTROLPANEL_H
#define THE_CORP_GAME_CONTROLPANEL_H

#include "../Animation/Entity.h"

namespace ControlPanel {

    extern Entity *newClerkButton;
    extern Entity *newOfficeButton;

    void initControlPanel();

    void refreshControlPanel();
}

#endif //THE_CORP_GAME_CONTROLPANEL_H
