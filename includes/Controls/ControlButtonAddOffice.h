#ifndef THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H
#define THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H

#include "../Animation/Entity.h"
#include "../Office/Office.h"

class ControlButtonAddOffice : public Entity {
public:
    const static int width = 142;
    const static int height = 47;

    Office *attachedOffice = nullptr;

    explicit ControlButtonAddOffice();

    void updateLogic() override;
};
#endif //THE_CORP_GAME_CONTROLBUTTONADDOFFICE_H