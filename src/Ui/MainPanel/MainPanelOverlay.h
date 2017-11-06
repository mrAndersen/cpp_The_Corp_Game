#ifndef THE_CORP_GAME_MAINPANELOVERLAY_H
#define THE_CORP_GAME_MAINPANELOVERLAY_H

#include "..\..\Ui\BasicUi.h"
#include "..\..\System\ResourceLoader.h"
#include "..\..\System\EntityContainer.h"
#include "..\..\System\System.h"
#include "..\..\System\ControlPanel.h"

class MainPanelOverlay : public BasicUi {
public:
    const static int width = 388;
    const static int height = 66;

    sf::Text time;

    MainPanelOverlay(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_MAINPANELOVERLAY_H
