#ifndef THE_CORP_GAME_COG_H
#define THE_CORP_GAME_COG_H

#include <Ui/BasicUi.h>

class Cog : public BasicUi {
public:
    const static int width = 36;
    const static int height = 40;

    Cog(float leftOffset, float topOffset);

    void update() override;
};


#endif //THE_CORP_GAME_COG_H
