#ifndef THE_CORP_GAME_CONTROLPANEL_H
#define THE_CORP_GAME_CONTROLPANEL_H

namespace ControlPanel {
    extern std::map<Entities , Entity *> controls;
    extern std::map<std::string , Entity *> mainMenu;

    void initControlPanel();

    void initMainMenu();
}

#endif //THE_CORP_GAME_CONTROLPANEL_H
