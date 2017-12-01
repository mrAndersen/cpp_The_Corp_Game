#ifndef THE_CORP_GAME_ACCOUNTANT_H
#define THE_CORP_GAME_ACCOUNTANT_H


#include "../Basic/Movable.h"

class Accountant : public Movable {
public:
    Accountant(sf::Vector2f coordinates);

private:
    const static int width = 70;
    const static int height = 120;

    std::map<int, float> buffPercentages = {{1, 1},{2, 1.5},{3, 2},{4, 2.5}};
    bool earningProcessed = false;

    std::map<int, float> dailySalaries = {{1, 150}, {2, 250}, {3, 500}, {4, 750}};
    bool salaryProcessed = false;

    WorkPlace *currentWorkPlace = nullptr;
public:
    void spawn() override;

    const std::map<int, float> &getBuffPercentages() const;

    WorkPlace *getCurrentWorkPlace() const;

    void setCurrentWorkPlace(WorkPlace *currentWorkPlace);

    void searchWorkPlace();

    void createWorkPlaceRoute();

    bool isInWorkPlace();

    sf::String createStatsText() override;
protected:
    void updateLogic() override;
};


#endif //THE_CORP_GAME_ACCOUNTANT_H
