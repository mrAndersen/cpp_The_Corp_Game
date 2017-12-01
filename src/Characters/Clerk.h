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

    std::map<int, float> dailyEarnings = {{1, 80},{2, 160},{3, 240},{4,400}};
    bool earningProcessed = false;

    std::map<int, float> dailySalaries = {{1, 64}, {2, 100}, {3, 150}, {4, 200}};
    bool salaryProcessed = false;

    float totalEarnings = 10000;

    WorkPlace *currentWorkPlace = nullptr;

    explicit Clerk(sf::Vector2f coordinates);

    virtual ~Clerk();

    void updateLogic() override;

    WorkPlace *getCurrentWorkPlace() const;

    void setCurrentWorkPlace(WorkPlace *currentWorkPlace);

    bool isInWorkPlace();

    void searchWorkPlace();

    void spawn() override;

    void createWorkPlaceRoute();

    sf::String createStatsText() override;

    void upgrade() override;
};

#endif //THE_CORP_GAME_CLERK_H
