#ifndef THE_CORP_GAME_SAVEMANAGER_H
#define THE_CORP_GAME_SAVEMANAGER_H

#include <string>

class SaveManager {
public:
    int saveCurrentState(const std::string &fileName = "save.dat");

    void handleSaveEvent();

};


#endif //THE_CORP_GAME_SAVEMANAGER_H
