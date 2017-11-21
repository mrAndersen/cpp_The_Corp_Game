#include "../System/EntityContainer.h"
#include "Manager.h"
#include "Clerk.h"

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

    if (state == S_None && isSpawned()) {
        if (!currentTarget && targetSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
            currentTarget = searchTarget();
            targetSearchResolution.restart();
        }

        if (currentTarget) {
            moving = true;
            currentTarget->setWillBeBuffed(true);
            setDrawOrder(D_Characters, true);

            createBuffTargetDestination();
        }
    }
}

void Manager::createBuffTargetDestination() {
    if (floor == currentTarget->getFloor()) {
        if (currentTarget->getEType() == E_Clerk) {
            auto clerk = dynamic_cast<Clerk *>(currentTarget);
            destinations.push_back(Destination::createBuffPlaceDST(clerk));
        }
    } else {
        targetElevator = searchNearestElevator();
        targetElevator->incBoarding();

        if (targetElevator) {
            destinations.push_back(Destination::createElevatorWaitingDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorCabinDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorExitingDST(targetElevator, this, currentTarget->getWorldCoordinates()));

            if (currentTarget->getEType() == E_Clerk) {
                auto clerk = dynamic_cast<Clerk *>(currentTarget);
                destinations.push_back(Destination::createBuffPlaceDST(clerk));
            }
        }
    }
}

Movable *Manager::searchTarget() {
    auto targets = EntityContainer::getGroupItems("movable");

    for (auto &e:targets) {
        auto movable = dynamic_cast<Movable *>(e);

        if (!movable->isBuffed() && !movable->isWillBeBuffed()) {
            return movable;
        }
    }

    return nullptr;
}
