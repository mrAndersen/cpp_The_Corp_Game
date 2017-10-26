#ifndef THE_CORP_GAME_CLERK_H
#define THE_CORP_GAME_CLERK_H

#include <Basic/Movable.h>
#include <Office/Office.h>
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"

class Clerk : public Movable {
public:
    const static int width = 70;
    const static int height = 120;

    float hourEarning = 10.f;
    bool earningProcessed = false;

    float dailySalary = 64.f;
    bool salaryProcessed = false;

    explicit Clerk(sf::Vector2f coordinates);

    void updateLogic() override;
};

#endif //THE_CORP_GAME_CLERK_H
