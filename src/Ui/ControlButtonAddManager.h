#ifndef THE_CORP_GAME_CONTROLBUTTONADDMANAGER_H
#define THE_CORP_GAME_CONTROLBUTTONADDMANAGER_H

#include "ControlButtonAddManager.h"
#include "BasicUi.h"

class Manager;

class ControlButtonAddManager : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    Manager *attachedManager = nullptr;

    explicit ControlButtonAddManager(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDMANAGER_H
