#ifndef THE_CORP_GAME_BUTTON1X_H
#define THE_CORP_GAME_BUTTON1X_H

class Button1x : public BasicUi {
public:
    const static int width = 52;
    const static int height = 42;

    Button1x(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_BUTTON1X_H
