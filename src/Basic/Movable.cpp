#include <cmath>
#include <iostream>
#include <fstream>
#include <Text/TextEntity.h>
#include "System/Enum.h"
#include "Movable.h"
#include "System/System.h"
#include "System/EntityContainer.h"
#include "Objects/Ground.h"

void Movable::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setOutlineColor(sf::Color::White);
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "id: " + std::to_string(id) + "\n" +
                "name: " + personName + "\n" +
                "pos: {" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) +
                "}\n" +
                "left: " + std::to_string((int) left) + "," +
                "right: " + std::to_string((int) right) + "," +
                "top: " + std::to_string((int) top) + "," +
                "bottom: " + std::to_string((int) bottom) + "\n" +
                "office: " + std::to_string(currentWorkPlace ? currentWorkPlace->getParentOffice()->getId() : 0) +
                "\n" +
                "state: " + std::to_string(state) + "\n" +
                "floor: " + std::to_string(floor) + "\n" +
                "speed: " + std::to_string((int) currentSpeed) + "p/s\n" +
                "selected: " + std::to_string((int) selected) + "\n"
                        "race: " + std::to_string((int) race) + " gender: " + std::to_string((int) gender)
        );
        System::window->draw(debugInfo);
    }
}

void Movable::updateLogic() {
    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * currentSpeed * System::timeFactor;

    //update floor
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;

//    if(isOnTheGround()){
//        EntityContainer::remove(this);
//    }

    //no work place
    if (!currentWorkPlace && isOnTheGround() && errorString.getString().isEmpty()) {
        valid = false;

        errorString.setString("No free work places");
        state = S_None;
    } else {
        valid = true;
    }

    //end of work day
    if (!System::gameTime.isWorkTime()) {
        state = S_GoHome;
    }

    if (state == S_GoHome) {

    }

    //falling
    if (!isOnTheGround() && isAboveGround() && direction == Direction::Down) {
        state = S_Falling;
    }

    if (state == S_Falling) {
        worldCoordinates.y -= frameDistance;
        currentSpeed = currentSpeed + fallAcceleration * frameTimeSeconds;
    }

    //stop falling
    if (isOnTheGround() && state == S_Falling) {
        //normalize
        worldCoordinates.y = System::groundLevel + Ground::height + height / 2;

        direction = Direction::None;
        if (currentWorkPlace) {
            state = S_GoToOffice;
        } else {
            state = S_None;
        }
    }

    if (state == S_Working) {
        currentSpeed = 0;
        direction = Direction::Right;
    }

    //go to office
    if (state == S_GoToOffice && currentWorkPlace) {
        if (isInWorkPlace()) {
            state = S_Working;

            worldCoordinates = currentWorkPlace->getWorldCoordinates();
            direction = Direction::Right;
        } else {

            //office is on the same floor
            if (currentWorkPlace->getParentOffice()->getFloor() == this->floor) {
                if (currentWorkPlace->getWorldCoordinates().x < this->worldCoordinates.x) {
                    direction = Direction::Left;
                } else {
                    direction = Direction::Right;
                }
            } else {
                auto elevator = searchNearestElevator();

                //go to nearest elevator
                if (elevator) {
                    state = S_GoToElevator;
                }
            }
        }
    }

    //go to elevator wait position
    if (state == S_GoToElevator) {
        auto elevator = searchNearestElevator();
        auto waitPointLeft = elevator->getLeft() - width / 2;
        auto waitPointRight = elevator->getRight() + width / 2;

        if (worldCoordinates.x < waitPointLeft && worldCoordinates.x < elevator->getLeft()) {
            direction = Direction::Right;
        }

        if (worldCoordinates.x > waitPointRight && worldCoordinates.x > elevator->getRight()) {
            direction = Direction::Left;
        }

        if ((int) worldCoordinates.x == (int) waitPointLeft ||
            (int) worldCoordinates.x == (int) waitPointRight) {

            if ((int) worldCoordinates.x == (int) waitPointLeft) {
                direction = Direction::Right;
            }

            if ((int) worldCoordinates.x == (int) waitPointRight) {
                direction = Direction::Left;
            }

            currentSpeed = 0;
            state = S_WaitForElevator;
            destinationFloor = currentWorkPlace->getParentOffice()->getFloor();
        } else {
            state = S_GoToElevator;
        }
    }

    if (state == S_WaitForElevator) {
        auto elevator = searchNearestElevator();

        //cabin here and has space - go there
        if (
                elevator->getCabin()->getFloor() == floor &&
                (int) elevator->getCabin()->getBottom() == (int) bottom &&
                elevator->getCabin()->hasFreeSpace()
                ) {
            state = S_GoToCabin;
        } else {
            //call cabin
            elevator->addToQueue(floor);
        }
    }

    if (state == S_GoToCabin) {
        auto elevator = searchNearestElevator();
        auto cabin = elevator->getCabin();
        currentSpeed = defaultSpeed;

        if (!randomedCabinPosition) {
            auto minCabinXPosition = cabin->getWorldCoordinates().x - cabin->getWidth() / 2;
            auto maxCabinXPosition = cabin->getWorldCoordinates().x + cabin->getWidth() / 2;

            randomedCabinPosition = System::getRandom(minCabinXPosition, maxCabinXPosition);
        }

        if (randomedCabinPosition > worldCoordinates.x) {
            direction = Direction::Right;
        }

        if (randomedCabinPosition < worldCoordinates.x) {
            direction = Direction::Left;
        }

        if (randomedCabinPosition == (int) worldCoordinates.x) {
            currentSpeed = 0;
            elevator->getCabin()->addMovable(this);

            if (destinationFloor) {
                elevator->addToQueue(destinationFloor);
            }

            state = S_RideInElevator;
        }
    }


    //riding
    if (state == S_RideInElevator) {
        auto elevator = searchNearestElevator();

        currentSpeed = 0;
        direction = Direction::None;

        //end of ride
        if (floor == destinationFloor && elevator->isWaiting()) {
            elevator->getCabin()->removeMovable(this);
            worldCoordinates.y = 100 + (System::gridSize * 3 * (destinationFloor - 1)) + height / 2;
            randomedCabinPosition = 0;

            state = S_None;
            destinationFloor = 0;
        }
    }


    //not working - but should
    if (
            currentWorkPlace && System::gameTime.isWorkTime() &&
            state != S_Working &&
            state != S_WaitForElevator &&
            state != S_RideInElevator &&
            state != S_GoToCabin &&
            state != S_GoToElevator
            ) {
        state = S_GoToOffice;
        currentSpeed = defaultSpeed * System::timeFactor;
    }

    //search workplace every 500ms
    if (!currentWorkPlace && isOnTheGround() && workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
        searchWorkPlace();
    }

    //movement
    if (direction == Direction::Right) {
        worldCoordinates.x += frameDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= frameDistance;
    }

    Entity::updateLogic();
}

bool Movable::hasReachedWorldEdges() {
    return !((worldCoordinates.x + width / 2) <= System::worldWidth / 2 &&
             (worldCoordinates.x - width / 2) >= -System::worldWidth / 2);
}

float Movable::getCurrentSpeed() const {
    return currentSpeed;
}

void Movable::setCurrentSpeed(float currentSpeed) {
    Movable::currentSpeed = currentSpeed;
}

float Movable::getFallAcceleration() const {
    return fallAcceleration;
}

void Movable::setFallAcceleration(float fallAcceleration) {
    Movable::fallAcceleration = fallAcceleration;
}

std::string Movable::serialize() {
    return Entity::serialize();
}

Movable::Movable() : Entity() {
    personName = ResourceLoader::getRandomName(gender);

    auto rnd = System::getRandom(1, 3);

    switch (rnd) {
        case 1:
            race = R_White;
            break;
        case 2:
            race = R_Black;
            break;
        case 3:
            race = R_Asian;
            break;
        default:
            race = R_White;
    }

    auto rnd2 = System::getRandom(1, 2);

    switch (rnd2) {
        case 1:
            gender = G_Male;
            break;
        case 2:
            gender = G_Female;
            break;
        default:
            gender = G_Male;
    }
}

float Movable::getDefaultSpeed() const {
    return defaultSpeed;
}

void Movable::setDefaultSpeed(float defaultSpeed) {
    Movable::defaultSpeed = defaultSpeed;
}

float Movable::getCost() const {
    return cost;
}

void Movable::setCost(float cost) {
    Movable::cost = cost;
}

void Movable::spawn() {
    System::cash -= this->cost;

    auto *spent = new TextEntity(System::c_red, 30);
    auto position = worldCoordinates;
    position.y += height / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(this->getCost()) + "$");

    recalculateBoundaries();

    if (isAboveGround()) {
        direction = Direction::Down;
        state = S_Falling;
    }

    Entity::spawn();
}

void Movable::searchWorkPlace() {
    if (!this->currentWorkPlace && this->isSpawned()) {
        for (auto office:EntityContainer::getOffices()) {
            if (office->hasFreeWorkPlaces() && office->isSpawned()) {

                currentWorkPlace = office->getNextFreeWorkPlace();
                currentWorkPlace->setWorker(this);

                return;
            }
        }
    }
}

bool Movable::isSpawned() const {
    return spawned;
}

int Movable::getFloor() const {
    return floor;
}

void Movable::setFloor(int floor) {
    Movable::floor = floor;
}

bool Movable::isInWorkPlace() {
    return
            currentWorkPlace &&
            floor == currentWorkPlace->getParentOffice()->getFloor() &&
            (int) worldCoordinates.x == (int) currentWorkPlace->getWorldCoordinates().x;
}

const std::string &Movable::getPersonName() const {
    return personName;
}

void Movable::setPersonName(const std::string &personName) {
    Movable::personName = personName;
}

Gender Movable::getGender() const {
    return gender;
}

void Movable::setGender(Gender gender) {
    Movable::gender = gender;
}

Elevator *Movable::searchNearestElevator() {
    auto elevators = EntityContainer::getElevators();

    if (elevators.empty()) {
        return nullptr;
    }

    std::map<int, Elevator *> buffer;

    for (auto el:elevators) {
        auto elevatorCenter = el->getLeft() + el->getCabin()->getWidth() / 2;
        int distance = std::abs((int) worldCoordinates.x - (int) elevatorCenter);

        buffer[distance] = el;
    }

    return buffer.begin().operator*().second;
}

int Movable::getDestinationFloor() const {
    return destinationFloor;
}

void Movable::setDestinationFloor(int destinationFloor) {
    Movable::destinationFloor = destinationFloor;
}


