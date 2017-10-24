#ifndef THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
#define THE_CORP_GAME_CONTROLBUTTONADDCLERK_H

#include "Characters/Clerk.h"

class ControlButtonAddClerk : public Entity {
public:
    const static int width = 60;
    const static int height = 62;

    Clerk *attachedClerk = nullptr;

    explicit ControlButtonAddClerk();

    void update() override;
};

#endif //THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
