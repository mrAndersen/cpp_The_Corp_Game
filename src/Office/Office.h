#ifndef THE_CORP_GAME_OFFICE_H
#define THE_CORP_GAME_OFFICE_H

#include "..\Basic\Entity.h"
#include "..\Component\WorkPlace.h"
#include "../Basic/Movable.h"

class WorkPlace;

class Movable;

class Office : public Entity {
protected:
    int floor = 1;

    float cost = 0;

    WorkPlace *workPlaces[4];

    Popup *popup;
    sf::Text popupText;
    std::string popupString;
public:
    Office();

    void updatePopup();

    sf::String serialize() override;

    void populate(std::vector<std::string> &array) override;

    std::string createStatsText();

    WorkPlace *const *getWorkPlaces() const;

    std::vector<Office *> getNeighborOffices();

    void setSelected(bool selected) override;

    float getCost() const;

    void setCost(float cost);

    void updateLogic() override;

    void spawn() override;

    void renderDebugInfo() override;

    int getFloor() const;

    void setFloor(int floor);

    bool hasFreeWorkPlaces();

    void addWorker(Movable *worker);

    int getBusyWorkPlaces();

    WorkPlace *getNextFreeWorkPlace();

    WorkPlace *getWorkplaceAt(int &index);

    int getWorkplaceIndex(Movable *worker);
};

#endif //THE_CORP_GAME_OFFICE_H
