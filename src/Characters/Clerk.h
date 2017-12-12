#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include "..\Basic\Movable.h"

class Movable;

class Clerk : public Movable {
protected:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
//        ar & boost::serialization::base_object<Movable *>(*this);
        ar & totalEarnings;
    }

    std::map<int, float> dailyEarnings = {{1, 200},{2, 400},{3, 750},{4, 1200}};
    bool earningProcessed = false;

    std::map<int, float> dailySalaries = {{1, 64}, {2, 100}, {3, 150}, {4, 200}};
    bool salaryProcessed = false;

    float totalEarnings = 0;

    WorkPlace *currentWorkPlace = nullptr;

public:
    const static int width = 70;
    const static int height = 120;

    Clerk(sf::Vector2f coordinates);

    void populate(std::vector<std::string> &array) override;

    virtual ~Clerk();

    float getHalfHourEarning();

    float getTotalEarnings() const;

    void setTotalEarnings(float totalEarnings);

    float getDailySalary();

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
