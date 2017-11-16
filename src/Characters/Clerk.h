#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include "..\Basic\Movable.h"
#include "..\Office\Office.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"

class Clerk : public Movable {
public:
    const static int width = 70;
    const static int height = 120;

    float dailyEarning = 80;
    bool earningProcessed = false;

    float dailySalary = 64;
    bool salaryProcessed = false;

    WorkPlace *currentWorkPlace = nullptr;
    sf::Clock workPlaceSearchResolution;

    explicit Clerk(sf::Vector2f coordinates);

    void updateLogic() override;

    WorkPlace *getCurrentWorkPlace() const;

    void setCurrentWorkPlace(WorkPlace *currentWorkPlace);

    bool isInWorkPlace();

    void searchWorkPlace();

    void createWorkPlaceRoute();
};

#endif //THE_CORP_GAME_CLERK_H
