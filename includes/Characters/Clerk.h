#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include "../System/ResourceLoader.h"
#include "../Animation/Movable.h"

class Clerk : public Movable {
public:
    const static int width = 128;
    const static int height = 120;

    float hourEarning = 10.f;
    bool earningProcessed = false;

    float dailySalary = 64.f;
    bool salaryProcessed = false;

    sf::Clock hourEarningHintClock;

    explicit Clerk(sf::Vector2f coordinates);

    void updateLogic();
};

#endif //THE_CORP_GAME_CLERK_H
