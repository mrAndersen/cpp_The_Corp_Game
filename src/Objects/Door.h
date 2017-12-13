#ifndef THE_CORP_GAME_DOOR_H
#define THE_CORP_GAME_DOOR_H


#include <Basic/Entity.h>

class Door : public Entity {
public:
    static const int width = 64;
    static const int height = 136;

    explicit Door(sf::Vector2f coordinates);

    void updateLogic() override;
};


#endif //THE_CORP_GAME_DOOR_H
