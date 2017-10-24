#ifndef THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H
#define THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H

#include <Basic/Entity.h>
#include "Office/Office.h"
#include <System/ViewHandler.h>

class ControlButtonAddOffice : public Entity {
public:
    const static int width = 60;
    const static int height = 62;

    Office *attachedOffice = nullptr;

    explicit ControlButtonAddOffice();

    void update() override;
};
#endif //THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H
