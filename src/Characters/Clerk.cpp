#include <iostream>
#include <cmath>
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "Clerk.h"

Clerk::Clerk(sf::Vector2f coordinates) : Movable(E_Clerk, Clerk::width, Clerk::height) {
    setDefaultSpeed(165);

    setCost(500);
    setWorldCoordinates(coordinates);
    setSelectable(true);

    setDrawOrder(D_Characters);
    initEntity();

    EntityContainer::add(this);
}

void Clerk::updateLogic() {
    Movable::updateLogic();

    if (level == 1 && totalEarnings >= 1000) {
        upgradeAvailable = true;
    }

    if (level == 2 && totalEarnings >= 2500) {
        upgradeAvailable = true;
    }

    if (level == 3 && totalEarnings >= 5000) {
        upgradeAvailable = true;
    }

    if (level == 4) {
        upgradeAvailable = false;
    }

    //search workplace every 500ms
    if (!currentWorkPlace && workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
        searchWorkPlace();
        workPlaceSearchResolution.restart();
    }

    //one-time-exec
    //not working but should
    if (System::gameTime.isWorkTime() && !isInWorkPlace() && currentWorkPlace && state != S_Working &&
        state != S_Smoking && state != S_Falling && !moving) {

        visible = true;
        moving = true;
        setDrawOrder(D_Characters, true);

        createWorkPlaceRoute();
    }

    //one-time-exec
    //go smoke
    if (
            smoking && !moving && !buffed && !willBeBuffed &&
            isInWorkPlace() && state == S_Working &&
            System::gameTime.getHour() >= 12 &&
            System::getRandom(0, System::fps * 1000) <= 30
            ) {

        moving = true;
        setDrawOrder(D_Characters, true);

        //denormalize character
        worldCoordinates.y = getFloorBottom(floor) + height / 2;
        createSmokeAreaRoute();
    }

    if (state == S_Working) {
        //earning every half hour
        if (System::gameTime.isEarningHour() && !earningProcessed) {
            auto earning = dailyEarnings[level] / 8 / 2 * workingModificator;

            System::cash += earning;
            totalEarnings += earning;

            auto *earningHint = new TextEntity(System::c_green, 25);
            auto position = worldCoordinates;
            position.y += height / 2;

            earningHint->setSpeed(100);
            earningHint->setLiveTimeSeconds(2);
            earningHint->setWorldCoordinates(position);
            earningHint->setString("+" + System::f_to_string(earning) + "$");

            earningProcessed = true;
        }

        //reset earning processing
        if (System::gameTime.getMinute() == 1 || System::gameTime.getMinute() == 31) {
            earningProcessed = false;
        }

        //salary every day
        if (System::gameTime.getHour() == System::endWorkHour && System::gameTime.getMinute() == 0 &&
            !salaryProcessed) {
            System::cash = System::cash - dailySalaries[level];
            salaryProcessed = true;
        }

        //reset salary processing
        if (System::gameTime.getHour() == 0 && System::gameTime.getMinute() == 0) {
            salaryProcessed = false;
        }
    }


}

WorkPlace *Clerk::getCurrentWorkPlace() const {
    return currentWorkPlace;
}

void Clerk::setCurrentWorkPlace(WorkPlace *currentWorkPlace) {
    Clerk::currentWorkPlace = currentWorkPlace;
}

bool Clerk::isInWorkPlace() {
    return
            currentWorkPlace &&
            floor == currentWorkPlace->getParentOffice()->getFloor() &&
            (int) worldCoordinates.x == (int) currentWorkPlace->getWorldCoordinates().x;
}

void Clerk::createWorkPlaceRoute() {
    if (floor == currentWorkPlace->getParentOffice()->getFloor()) {
        destinations.push_back(Destination::createWorkplaceDST(this));
    } else {
        targetElevator = searchNearestElevator();

        if (targetElevator) {
            targetElevator->incBoarding();
            destinations.push_back(Destination::createElevatorWaitingDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorCabinDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorExitingDST(targetElevator, this,
                                                                         currentWorkPlace->getWorldCoordinates()));
            destinations.push_back(Destination::createWorkplaceDST(this));
        }
    }
}

void Clerk::searchWorkPlace() {
    if (!this->currentWorkPlace && this->isSpawned()) {
        auto offices = EntityContainer::getGroupItems("offices");
        std::map<float, WorkPlace *> buffer;

        for (auto e:offices) {
            auto office = dynamic_cast<Office *>(e);

            if (office->hasFreeWorkPlaces() && office->isSpawned()) {

                for (int i = 0; i < 4; ++i) {
                    auto wc = office->getWorkPlaces()[i]->getWorldCoordinates();

                    auto distance = std::fabs(std::sqrt(
                            std::pow(worldCoordinates.x - wc.x, 2) +
                            std::pow(worldCoordinates.y - wc.y, 2)));

                    buffer[distance] = office->getWorkPlaces()[i];
                }
            }
        }

        if (!buffer.empty()) {
            currentWorkPlace = buffer.begin()->second->getParentOffice()->getNextFreeWorkPlace();
            currentWorkPlace->setWorker(this);
        }
    }
}

std::string Clerk::createStatsText() {
    auto s = Movable::createStatsText();

    s = s + "Daily salary: " + System::f_to_string(dailySalaries[level]) + "$\n";
    s = s + "Earned total: " + System::f_to_string(totalEarnings) + "$\n";
    s = s + "Earning/h: " + System::f_to_string(dailyEarnings[level] / 8 * workingModificator) + "$\n";
    s = s + "Motivation: " + (buffed ? (buffStart.get() + " - " + buffEnd.get()) : "Not buffed") + "\n";

    if (upgradeAvailable) {
        s = s + "Upgrade: Yes!\n";
    } else {
        if (level == 1) {
            s = s + "Upgrade: " + System::f_to_string(1000 - totalEarnings, 0) + "$ more total earnings\n";
        }


    }

    return s;
}

void Clerk::upgrade() {
    lastUpgradeTimer.restart();

    if (level == 1 && totalEarnings < 1000) {
        return;
    }

    if (level == 2 && totalEarnings < 2500) {
        return;
    }

    if (level == 3 && totalEarnings < 5000) {
        return;
    }

    if (level == 4) {
        return;
    }


    Movable::upgrade();
}
