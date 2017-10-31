#include <cmath>
#include <iostream>
#include <fstream>
#include <Text/TextEntity.h>
#include <Background/Ground.h>
#include "System/EntityContainer.h"
#include "Movable.h"


void Movable::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setOutlineColor(sf::Color::White);
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "s: " + std::to_string(state) + "\n" +
                "dests: " + std::to_string(destinations.size()) + "\n" +
                "speed: " + std::to_string(currentSpeed) + "\n" +
                "mv: " + std::to_string(moving) + "\n"
        );

        if (!destinations.empty()) {
            sf::Vertex line[destinations.size() + 1];

            line[0].position = System::cToGl(worldCoordinates);
            line[0].color = sf::Color::Yellow;

            int i = 1;
            for (auto d:destinations) {
                sf::RectangleShape shape;
                shape.setPosition(System::cToGl(d.getCoordinates()));
                shape.setFillColor(sf::Color::Yellow);
                shape.setOrigin({5, 5});
                shape.setSize({10, 10});

                line[i].position = System::cToGl(d.getCoordinates());
                line[i].color = sf::Color::Yellow;
                i++;

                System::window->draw(shape);
            }

            System::window->draw(line, destinations.size() + 1, sf::Lines);
        }


        System::window->draw(debugInfo);
    }
}

void Movable::updateLogic() {
    Entity::updateLogic();

    updateFloor();

    float frameDistance = frameTimeSeconds * currentSpeed * System::timeFactor;

    if(!spawned){
        return;
    }

    if (isAboveGround() && state == S_None) {
        state = S_Falling;
    }

    if (moving) {
        state = !destinations.empty() ? S_Walk : S_None;
    }

    if (state == S_None) {
        currentSpeed = 0;
    }

    if (state == S_Falling) {
        worldCoordinates.y -= frameDistance;
        currentSpeed = currentSpeed + fallAcceleration * frameTimeSeconds;

        if (isOnTheGround() || isBelowGround()) {
            worldCoordinates.y = System::groundLevel + Ground::height + height / 2;
            currentSpeed = 0;
            state = S_None;
        }
    }

    if (state == S_Walk) {
        currentSpeed = defaultSpeed;
        auto local = destinations.front();

        if ((int) worldCoordinates.y != (int) local.getCoordinates().y) {
            stop();
        } else {
            if (worldCoordinates.x < local.getCoordinates().x) {
                direction = Right;
            }

            if (worldCoordinates.x > local.getCoordinates().x) {
                direction = Left;
            }

            if ((int) worldCoordinates.x == (int) local.getCoordinates().x) {
                auto elevator = searchNearestElevator();

                if (local.getType() == DST_Elevator_Waiting) {
                    elevator->addToQueue(floor);

                    if (elevator->getCabin()->getBottom() == bottom && elevator->getCabin()->hasFreeSpace()) {
                        destinations.pop_front();
                    } else {
                        stop();
                    }
                }

                if (local.getType() == DST_Elevator_Inside_Cabin) {
                    auto final = destinations.back();

                    elevator->getCabin()->addMovable(this);
                    elevator->addToQueue(final.getFloor());
                    destinations.pop_front();
                }

                if (local.getType() == DST_Workplace || local.getType() == DST_SmokeArea) {
                    destinations.pop_front();
                }

                if (local.getType() == DST_Elevator_Exiting) {
                    elevator->getCabin()->removeMovable(this);
                    destinations.pop_front();
                }

                if (local.getType() == DST_Unknown) {
                    destinations.pop_front();
                }
            }

            if (direction == Right) {
                worldCoordinates.x += frameDistance;
            }

            if (direction == Left) {
                worldCoordinates.x -= frameDistance;
            }
        }
    }

    //sit and work
    if (isInWorkPlace() && moving) {
        state = S_Working;
        direction = Right;

        destinations.clear();
        worldCoordinates.y = currentWorkPlace->getWorldCoordinates().y;
        moving = false;
    }

    //search workplace every 500ms
    if (!currentWorkPlace && workPlaceSearchResolution.getElapsedTime().asMilliseconds() >= 500) {
        searchWorkPlace();
    }

    //ONE TIME EXEC
    //go smoke
    if (isInWorkPlace() && state == S_Working && !moving && System::gameTime.getHour() == 12) {
        moving = true;
        auto smokeArea = findNearestOutside();

        if (floor == 1) {
            destinations.push_back({{smokeArea.x, System::groundLevel + Ground::height + height / 2}, DST_SmokeArea});
        } else {
            //elevator riding
            auto elevator = searchNearestElevator();

            if(worldCoordinates.x < elevator->getLeft()){
                destinations.push_back({{elevator->getLeft() - 50, worldCoordinates.y}, DST_Elevator_Waiting});

                //some motion from the chair
                worldCoordinates.x += 1;
            }

            if(worldCoordinates.x > elevator->getRight()){
                destinations.push_back({{elevator->getRight() + 50, worldCoordinates.y}, DST_Elevator_Waiting});

                //some motion from the chair
                worldCoordinates.x -= 1;
            }

            destinations.push_back({{elevator->getCabin()->getWorldCoordinates().x, worldCoordinates.y}, DST_Elevator_Inside_Cabin});

            if (smokeArea.x > elevator->getRight()) {
                destinations.push_back({{elevator->getRight() + 50, System::groundLevel + Ground::height + height / 2}, DST_Elevator_Exiting});
            }

            if (smokeArea.x < elevator->getLeft()) {
                destinations.push_back({{elevator->getLeft() - 50, System::groundLevel + Ground::height + height / 2}, DST_Elevator_Exiting});
            }

            destinations.push_back({{smokeArea.x, System::groundLevel + Ground::height + height / 2}, DST_SmokeArea});
        }
    }

    //ONE TIME EXEC
    //not working but should
    if (System::gameTime.isWorkTime() && !isInWorkPlace() && currentWorkPlace && state != S_Working && state != S_Smoking && state != S_Falling && !moving) {
        moving = true;

        if (floor == currentWorkPlace->getParentOffice()->getFloor()) {
            destinations.push_back({{currentWorkPlace->getWorldCoordinates().x, currentWorkPlace->getParentOffice()->getBottom() + height / 2}, DST_Workplace});
        } else {
            //elevator riding
            auto elevator = searchNearestElevator();

            if (elevator) {
                if(worldCoordinates.x < elevator->getLeft()){
                    destinations.push_back({{elevator->getLeft() - 50, worldCoordinates.y}, DST_Elevator_Waiting});
                }

                if(worldCoordinates.x > elevator->getRight()){
                    destinations.push_back({{elevator->getRight() + 50, worldCoordinates.y}, DST_Elevator_Waiting});
                }

                destinations.push_back({{elevator->getCabin()->getWorldCoordinates().x, worldCoordinates.y}, DST_Elevator_Inside_Cabin});

                if (currentWorkPlace->getWorldCoordinates().x > elevator->getRight()) {
                    destinations.push_back({{elevator->getRight() + 50, elevator->getFloorBottom(currentWorkPlace->getParentOffice()->getFloor()) + height / 2}, DST_Elevator_Exiting});
                }

                if (currentWorkPlace->getWorldCoordinates().x < elevator->getLeft()) {
                    destinations.push_back({{elevator->getLeft() - 50, elevator->getFloorBottom(currentWorkPlace->getParentOffice()->getFloor()) + height / 2}, DST_Elevator_Exiting});
                }

                destinations.push_back({{currentWorkPlace->getWorldCoordinates().x, currentWorkPlace->getParentOffice()->getBottom() + height / 2}, DST_Workplace});
            }
        }
    }

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

Movable::Movable(Entities type, int width, int height) : Entity(type) {
    this->width = width;
    this->height = height;

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

    gender = G_Male;

    addAnimation(S_None, gender, race, 24);
    addAnimation(S_Walk, gender, race, 24);
    addAnimation(S_Working, gender, race, 24);
    addAnimation(S_Smoking, gender, race, 66, 2750000);
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
        auto offices = EntityContainer::searchEntitiesByGroup(System::officeGroup);
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

    return buffer.begin()->second;
}

void Movable::addAnimation(States state, Gender gender, Race race, int frames, int duration) {
    Animation animation(this, state, frames, ResourceLoader::getCharacterTexture(eType, state, gender, race), duration);
    Entity::addAnimation(state, animation);
}

void Movable::updateFloor() {
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;
}

void Movable::stop() {
    state = S_None;
    direction = None;
}

sf::Vector2f Movable::findNearestOutside() {
    auto offices = EntityContainer::searchEntitiesByGroup(System::officeGroup);
    auto shafts = EntityContainer::searchEntitiesByGroup(System::elevatorShafts);
    std::vector<Entity *> objects;

    objects.reserve(offices.size() + shafts.size());
    objects.insert(objects.end(), offices.begin(), offices.end());
    objects.insert(objects.end(), shafts.begin(), shafts.end());

    std::map<int, Entity *> lefts;
    std::map<int, Entity *> rights;

    for (auto e:objects) {
        auto distance = std::fabs(e->getLeft() - worldCoordinates.x);
        lefts[distance] = e;
    }

    for (auto e:objects) {
        auto distance = std::fabs(e->getRight() - worldCoordinates.x);
        rights[distance] = e;
    }

    auto l = lefts.begin()->second;
    auto r = lefts.begin()->second;


    return {-100, 150};
}




































