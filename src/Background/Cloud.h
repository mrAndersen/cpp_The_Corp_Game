#ifndef THE_CORP_GAME_CLOUD_H
#define THE_CORP_GAME_CLOUD_H

#include "..\Basic\Entity.h"

class Cloud : public Entity {
protected:
    int speed = 100;
    sf::Vector2f size;

public:
    Cloud(Entities type, sf::Vector2f coordinates, sf::Vector2f size, float scale, int speed);

    void updateLogic() override;

    int getSpeed() const;

    void setSpeed(int speed);

    static void createRandomCloud();
};


#endif //THE_CORP_GAME_CLOUD_H
