#ifndef THE_CORP_GAME_OFFICEDEFAULT_H
#define THE_CORP_GAME_OFFICEDEFAULT_H

#include "Office.h"

class OfficeClerk: public Office {
public:
    const static int width = 600;
    const static int height = 150;

    explicit OfficeClerk(sf::Vector2f coordinates);

    void updateLogic() override;
};

#endif
