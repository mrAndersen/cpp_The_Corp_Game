#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include "..\Office\Office.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "..\Basic\Movable.h"

class Movable;

class Clerk : public Movable {
public:
    const static int width = 70;
    const static int height = 120;

    float dailyEarning = 80;
    bool earningProcessed = false;

    float dailySalary = 64;
    bool salaryProcessed = false;

    float totalEarnings = 0;

    WorkPlace *currentWorkPlace = nullptr;
    sf::Clock workPlaceSearchResolution;

    explicit Clerk(sf::Vector2f coordinates);

    void updateLogic() override;

    WorkPlace *getCurrentWorkPlace() const;

    void setCurrentWorkPlace(WorkPlace *currentWorkPlace);

    bool isInWorkPlace();

    void searchWorkPlace();

    void createWorkPlaceRoute();

    std::string createStatsText() override;
};

#endif //THE_CORP_GAME_CLERK_H
