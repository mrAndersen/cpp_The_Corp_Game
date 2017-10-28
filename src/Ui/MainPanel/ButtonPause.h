#ifndef THE_CORP_GAME_BUTTONPAUSE_H
#define THE_CORP_GAME_BUTTONPAUSE_H

#include <Ui/BasicUi.h>
#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <System/System.h>
#include <System/ControlPanel.h>

class ButtonPause : public BasicUi {
public:
    const static int width = 52;
    const static int height = 42;

    ButtonPause(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_BUTTONPAUSE_H
