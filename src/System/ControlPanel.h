#ifndef THE_CORP_GAME_CONTROLPANEL_H
#define THE_CORP_GAME_CONTROLPANEL_H

#include "../System/Enum.h"
#include "../Ui/MoneyIndicator.h"
#include "../Ui/MainPanel/MainPanelOverlay.h"
#include "../Ui/MainPanel/ButtonPause.h"
#include "../Ui/MainPanel/Button1x.h"
#include "../Ui/MainPanel/Button5x.h"
#include "../Ui/MainPanel/Button10x.h"
#include "../Ui/Questions/QAddClerk.h"
#include "../Ui/Questions/QAddManager.h"
#include "../Ui/Questions/QAddOffice.h"
#include "../Ui/Questions/QAddElevator.h"
#include "../Ui/ControlButtonAddClerk.h"
#include "../Ui/ControlButtonAddManager.h"
#include "../Ui/ControlButtonAddOffice.h"
#include "../Ui/ControlButtonAddElevatorCabin.h"
#include "../Ui/ControlButtonAddElevatorShaftMiddle.h"
#include "../Ui/ControlButtonAddElevatorShaftTop.h"
#include "../Ui/ControlButtonAddElevator.h"
#include <map>

class Entity;

namespace ControlPanel {
    extern std::map<Entities , Entity *> controls;

    void initControlPanel();

    std::map<Entities , Entity *> getControls();
}

#endif //THE_CORP_GAME_CONTROLPANEL_H
