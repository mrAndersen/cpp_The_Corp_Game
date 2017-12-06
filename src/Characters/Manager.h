#ifndef THE_CORP_GAME_MANAGER_H
#define THE_CORP_GAME_MANAGER_H

#include "../Basic/Movable.h"

class Manager : public Movable {
public:
    const static int width = 70;
    const static int height = 120;

    Movable *currentTarget = nullptr;
    sf::Clock targetSearchResolution;

    std::map<int, float> dailySalaries = {{1, 120}, {2, 200}, {3, 350}, {4, 500}};
    bool salaryProcessed = false;

    bool buffInProgress = false;
    sf::Clock buffingProcedureClock;

    int buffDurationGameHours = 2;
    std::map<int, float> buffStrengths = {{1, 1.2}, {2, 1.5}, {3, 2}, {4, 2.5}};

    int targetsBuffed = 0;

    explicit Manager(sf::Vector2f coordinates);

    void updateLogic() override;

    void createBuffTargetDestination();

    sf::String createStatsText() override;

    float getDailySalary();

    Movable *searchTarget();
};

#endif //THE_CORP_GAME_MANAGER_H
