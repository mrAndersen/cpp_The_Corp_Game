#ifndef THE_CORP_GAME_MAINPANELOVERLAY_H
#define THE_CORP_GAME_MAINPANELOVERLAY_H

#include "..\..\Ui\BasicUi.h"
#include "..\..\System\ResourceLoader.h"
#include "..\..\System\EntityContainer.h"
#include "..\..\System\System.h"
#include "..\..\System\ControlPanel.h"

class MainPanelOverlay : public BasicUi {
public:
    const static int width = 936;
    const static int height = 66;

    sf::Text time;
    std::map<Entities, Entity*> stats;
    std::map<Entities, sf::Text> statLabels;

    MainPanelOverlay(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_MAINPANELOVERLAY_H
