#ifndef THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
#define THE_CORP_GAME_CONTROLBUTTONADDCLERK_H

#include "BasicUi.h"
#include <SFML/System.hpp>
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"

class Clerk;

class ControlButtonAddClerk : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    Clerk *attachedClerk = nullptr;

    explicit ControlButtonAddClerk(float leftOffset, float topOffset);

    void update() override;
};

#endif //THE_CORP_GAME_CONTROLBUTTONADDCLERK_H
