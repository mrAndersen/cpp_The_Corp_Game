#ifndef THE_CORP_GAME_POPUP_H
#define THE_CORP_GAME_POPUP_H

#include "..\Basic\Entity.h"
#include "BasicUi.h"

class Popup : public BasicUi {
public:
    const static int width = 300;
    const static int height = 500;

    explicit Popup(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_POPUP_H
