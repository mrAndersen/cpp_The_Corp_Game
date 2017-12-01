#ifndef THE_CORP_GAME_MANAGER_H
#define THE_CORP_GAME_MANAGER_H

#include "../Basic/Movable.h"

class Manager : public Movable {
public:
    const static int width = 70;
    const static int height = 120;

    Movable *currentTarget = nullptr;
    sf::Clock targetSearchResolution;

    float dailySalary = 100;
    bool salaryProcessed = false;

    bool buffInProgress = false;
    sf::Clock buffingProcedureClock;

    int buffDurationGameHours = 2;
    float buffStrength = 1.2f;

    int targetsBuffed = 0;

    explicit Manager(sf::Vector2f coordinates);

    void updateLogic() override;

    void createBuffTargetDestination();

    sf::String createStatsText() override;

    Movable *searchTarget();
};

#endif //THE_CORP_GAME_MANAGER_H
