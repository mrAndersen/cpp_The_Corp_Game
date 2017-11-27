#include <cmath>
#include "Accountant.h"
#include "Clerk.h"
#include "../System/EntityContainer.h"

Accountant::Accountant(sf::Vector2f coordinates) : Movable(E_Accountant, width, height) {
    setDefaultSpeed(165);

    setCost(500);
    setWorldCoordinates(coordinates);
    setSelectable(true);

    setDrawOrder(D_Characters);
    initEntity();

    EntityContainer::add(this);
}

void Accountant::spawn() {
    recalculateAccountantsBonus();
    Movable::spawn();
}

const std::map<int, float> &Accountant::getBuffPercentages() const {
    return buffPercentages;
}

WorkPlace *Accountant::getCurrentWorkPlace() const {
    return currentWorkPlace;
}

void Accountant::setCurrentWorkPlace(WorkPlace *currentWorkPlace) {
    Accountant::currentWorkPlace = currentWorkPlace;
}

void Accountant::updateLogic() {
    Movable::updateLogic();

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
}

void Accountant::searchWorkPlace() {
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

void Accountant::createWorkPlaceRoute() {
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

bool Accountant::isInWorkPlace() {
    return
            currentWorkPlace &&
            floor == currentWorkPlace->getParentOffice()->getFloor() &&
            (int) worldCoordinates.x == (int) currentWorkPlace->getWorldCoordinates().x;
}

std::string Accountant::createStatsText() {
    auto s = Movable::createStatsText();

    s = s + "Global earning modificator: " + System::f_to_string(buffPercentages[level] * workingModificator) + "%\n";

    return s;
}
