#ifndef THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H
#define THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H

#include "../Basic/Entity.h"
#include "../Office/Office.h"
#include "BasicUi.h"
#include "../System/ViewHandler.h"
#include "../System/System.h"

class ControlButtonAddOffice : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    Office *attachedOffice = nullptr;

    explicit ControlButtonAddOffice(float leftOffset, float topOffset);

    void update() override;
};
#endif //THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H
