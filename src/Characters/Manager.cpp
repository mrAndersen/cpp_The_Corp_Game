#include "../System/EntityContainer.h"
#include "Manager.h"

Manager::Manager(sf::Vector2f coordinates) : Movable(E_Manager, Manager::width, Manager::height) {
    setDefaultSpeed(150);

    setCost(1000);
    setWorldCoordinates(coordinates);
    setSelectable(true);

    setDrawOrder(D_Characters);
    initEntity();

    System::salaryTotal += dailySalary;
    EntityContainer::add(this);
}

void Manager::updateLogic() {
    Movable::updateLogic();
}
