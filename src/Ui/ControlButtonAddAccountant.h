#ifndef THE_CORP_GAME_CONTROLBUTTONADDACCOUNTANT_H
#define THE_CORP_GAME_CONTROLBUTTONADDACCOUNTANT_H


#include "../Characters/Accountant.h"
#include "BasicUi.h"

class ControlButtonAddAccountant : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    Accountant *attachedAccountant = nullptr;

    explicit ControlButtonAddAccountant(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDACCOUNTANT_H
