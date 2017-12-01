#include "../System/EntityContainer.h"
#include "Manager.h"
#include "Clerk.h"
#include "Accountant.h"

Manager::Manager(sf::Vector2f coordinates) : Movable(E_Manager, Manager::width, Manager::height) {
    setDefaultSpeed(165);

    setCost(750);
    setWorldCoordinates(coordinates);
    setSelectable(true);

    setDrawOrder(D_Characters);
    initEntity();

    EntityContainer::add(this);
}

void Manager::updateLogic() {
    Movable::updateLogic();

    if (state == S_None && spawned) {
        if (!currentTarget && targetSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
            currentTarget = searchTarget();
            targetSearchResolution.restart();
        }

        //one-time-exec
        if (currentTarget && !moving) {
            moving = true;

            currentTarget->setWillBeBuffed(true);

            setDrawOrder(D_Characters, true);
            createBuffTargetDestination();
        }
    }

    if (state == S_Working && currentTarget && !buffInProgress && !currentTarget->isBuffed()) {
        buffingProcedureClock.restart();

        currentTarget->setWorkingModificator(currentTarget->getWorkingModificator() * buffStrengths[level]);
        currentTarget->setBuffed(true);
        currentTarget->setWillBeBuffed(false);
        currentTarget->setBuffStart(System::gameTime);
        currentTarget->setBuffEnd(System::gameTime + (buffDurationGameHours * 60));
        targetsBuffed++;
        buffInProgress = true;

        auto *buffHint = new TextEntity(System::c_blue, 30);
        auto position = currentTarget->getWorldCoordinates();
        position.y += currentTarget->getHeight() / 2 + 10;

        buffHint->setSpeed(100);
        buffHint->setLiveTimeSeconds(2);
        buffHint->setWorldCoordinates(position);

        if(currentTarget->getEType() == E_Accountant){
            currentTarget->recalculateAccountantsBonus();
            buffHint->setString("Earning modificator +" + System::f_to_string((currentTarget->getWorkingModificator() * 100) - 100) + "%");
        }

        if(currentTarget->getEType() == E_Clerk){
            buffHint->setString("Earnings + " + System::f_to_string((currentTarget->getWorkingModificator() * 100) - 100) + "%");
        }

    }

    if (state == S_Working && buffInProgress && buffingProcedureClock.getElapsedTime().asSeconds() >= 10 / System::timeFactor) {
        buffInProgress = false;
        currentTarget = nullptr;
        state = S_None;
    }
}

void Manager::createBuffTargetDestination() {
    if (floor == currentTarget->getFloor()) {
        if (currentTarget->getEType() == E_Clerk) {
            auto clerk = dynamic_cast<Clerk *>(currentTarget);
            destinations.push_back(Destination::createBuffPlaceDST(clerk));
        }

        if (currentTarget->getEType() == E_Accountant) {
            auto accountant = dynamic_cast<Accountant *>(currentTarget);
            destinations.push_back(Destination::createBuffPlaceDST(accountant));
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

            if (currentTarget->getEType() == E_Accountant) {
                auto accountant = dynamic_cast<Accountant *>(currentTarget);
                destinations.push_back(Destination::createBuffPlaceDST(accountant));
            }
        }
    }
}

Movable *Manager::searchTarget() {
    auto targets = EntityContainer::getGroupItems("movable");

    for (auto &e:targets) {
        auto movable = dynamic_cast<Movable *>(e);

        if (!movable->isBuffed() && !movable->isWillBeBuffed() && movable->getState() == S_Working) {
            return movable;
        }
    }

    return nullptr;
}

sf::String Manager::createStatsText() {

    auto s = Movable::createStatsText();

    s = s + "Daily salary: " + System::f_to_string(dailySalaries[level]) + "$\n";
    s = s + "Employees motivated: " + std::to_string(targetsBuffed) + "\n";

    return s;
}
