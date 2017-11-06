#ifndef THE_CORP_GAME_CONTROLPANEL_H
#define THE_CORP_GAME_CONTROLPANEL_H

namespace ControlPanel {
    extern std::map<Entities , Entity *> controls;

    void initControlPanel();

    void refreshControlPanel();

    std::map<Entities , Entity *> getControls();
}

#endif //THE_CORP_GAME_CONTROLPANEL_H
