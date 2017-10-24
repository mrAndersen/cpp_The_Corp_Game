#ifndef THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H
#define THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H


#include <Basic/Entity.h>
#include <Objects/ElevatorCabin.h>

class ControlButtonAddElevatorCabin : public Entity {
    const static int width = 142;
    const static int height = 47;

    ElevatorCabin *attachedCabin = nullptr;

public:
    explicit ControlButtonAddElevatorCabin();

    void updateLogic() override;
};


#endif //THE_CORP_GAME_CONTROLBUTTONADDELEVATORCABIN_H
