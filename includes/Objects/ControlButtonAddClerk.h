#ifndef THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
#define THE_CORP_GAME_CONTROLBUTTONADDCLERK_H

#include "../Characters/Clerk.h"

class ControlButtonAddClerk : public Entity {
public:
    const static int width = 142;
    const static int height = 47;

    Clerk *attachedClerk = nullptr;

    explicit ControlButtonAddClerk();

    void updateLogic();
};

#endif //THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
