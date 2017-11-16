#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H

class ControlButtonAddElevator : public BasicUi {
public:
    const static int width = 60;
    const static int height = 62;

    ControlButtonAddElevator(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATOR_H
