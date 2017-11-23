#include <cmath>
#include <iostream>
#include <fstream>
#include "..\Text\TextEntity.h"
#include "..\Background\Ground.h"
#include "..\System\EntityContainer.h"
#include "Movable.h"
#include "..\System\System.h"
#include "../Ui/MainPanel/ButtonPause.h"


void Movable::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setOutlineColor(sf::Color::White);
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "state: " + std::to_string(state) + "\n" +
                "dests: " + std::to_string(destinations.size()) + "\n" +
                "group: " + groupName + "\n" +
                "a_state: " + std::to_string(currentAnimation->getState()) + "\n" +
                "speed: " + std::to_string(currentSpeed) + "\n" +
                "mv: " + std::to_string(moving) + "\n"
                        "cdst: " + std::to_string(currentDST)
        );

        if (!destinations.empty()) {
            sf::Vertex lines[20];

            lines[0].position = System::cToGl(worldCoordinates);
            lines[0].color = selected ? sf::Color::Green : sf::Color::Yellow;

            int i = 1;
            for (auto d:destinations) {
                sf::RectangleShape shape;
                shape.setPosition(System::cToGl(d.getCoordinates()));
                shape.setFillColor(selected ? sf::Color::Green : sf::Color::Yellow);
                shape.setOrigin({5, 5});
                shape.setSize({10, 10});

                lines[i].position = System::cToGl(d.getCoordinates());
                lines[i].color = sf::Color::Yellow;
                i++;

                System::window->draw(shape);
            }

            System::window->draw(lines, destinations.size() + 1, sf::LineStrip);
        }

        if (System::debug > 1) {
            sf::VertexArray quad(sf::LineStrip, 5);

            quad[0].position = System::cToGl({rect.left, rect.top});
            quad[0].color = sf::Color::Red;

            quad[1].position = System::cToGl({rect.left + width, rect.top});
            quad[1].color = sf::Color::Red;

            quad[2].position = System::cToGl({rect.left + width, rect.top - height});
            quad[2].color = sf::Color::Red;

            quad[3].position = System::cToGl({rect.left, rect.top - height});
            quad[3].color = sf::Color::Red;

            quad[4].position = System::cToGl({rect.left, rect.top});
            quad[4].color = sf::Color::Red;

            System::window->draw(quad);
        }


        System::window->draw(debugInfo);
    }
}

void Movable::updateLogic() {
    Entity::updateLogic();

    updateFloor();

    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * currentSpeed * System::timeFactor;

    if (buffed && System::gameTime == buffEnd) {
        workingModificator = 1.f;
        buffed = false;
    }

    if (!spawned) {
        return;
    }

    if (isAboveGround() && !isOnTheFloor() && state == S_None) {
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
        currentSpeed = currentSpeed + fallAcceleration * frameTimeSeconds * System::timeFactor;

        if (isOnTheGround() || isBelowGround()) {
            worldCoordinates.y = System::groundLevel + Ground::height + height / 2;
            currentSpeed = 0;
            state = S_None;
        }
    }

    if (state == S_Smoking && System::gameTime.diffMinutes(smokeStarted) >= smokePeriodMinutes) {
        state = S_None;
    }

    if (state == S_Walk) {
        currentSpeed = defaultSpeed;

        auto local = destinations.front();
        auto final = destinations.back();

        if ((int) worldCoordinates.y != (int) local.getCoordinates().y) {
            state = S_None;
            direction = None;
        } else {
            if (moving) {
                if (worldCoordinates.x < local.getCoordinates().x) {
                    direction = Right;
                }

                if (worldCoordinates.x > local.getCoordinates().x) {
                    direction = Left;
                }

                if (direction == Right) {
                    worldCoordinates.x += frameDistance;
                }

                if (direction == Left) {
                    worldCoordinates.x -= frameDistance;
                }

                //normalize
                if (worldCoordinates.x < local.getCoordinates().x && direction == Left) {
                    worldCoordinates.x = local.getCoordinates().x;
                }

                if (worldCoordinates.x > local.getCoordinates().x && direction == Right) {
                    worldCoordinates.x = local.getCoordinates().x;
                }
            }

            if ((int) worldCoordinates.x == (int) local.getCoordinates().x) {
                if (local.getType() == DST_Elevator_Waiting) {
                    currentDST = DST_Elevator_Waiting;
                    targetElevator->addToQueue(floor);

                    if (targetElevator->getCabin()->getBottom() == bottom &&
                        targetElevator->getCabin()->hasFreeSpace() && targetElevator->isWaiting()) {

                        targetElevator->getCabin()->addMovable(this);
                        destinations.pop_front();
                    } else {
                        state = S_None;

                        if (targetElevator && worldCoordinates.x < targetElevator->getLeft()) {
                            direction = Right;
                        }

                        if (targetElevator && worldCoordinates.x > targetElevator->getRight()) {
                            direction = Left;
                        }
                    }
                }

                if (local.getType() == DST_Elevator_Inside_Cabin) {
                    currentDST = DST_Elevator_Inside_Cabin;

                    targetElevator->decBoarding();
                    targetElevator->addToQueue(final.getFloor());
                    destinations.pop_front();
                }

                if (local.getType() == DST_Workplace) {
                    currentDST = DST_Workplace;
                    destinations.pop_front();

                    state = S_Working;
                    direction = Right;
                    setDrawOrder(D_Characters_Working, true);

                    worldCoordinates.y = final.getCoordinates().y + 3;
                    worldCoordinates.x = final.getCoordinates().x;

                    moving = false;
                }

                if (local.getType() == DST_Buff_Position) {
                    currentDST = DST_Buff_Position;
                    destinations.pop_front();

                    state = S_Working;
                    direction = Right;

                    worldCoordinates.y = final.getCoordinates().y;
                    worldCoordinates.x = final.getCoordinates().x;

                    moving = false;
                }

                if (local.getType() == DST_SmokeArea) {
                    currentDST = DST_SmokeArea;
                    state = S_Smoking;
                    smokeStarted = System::gameTime;

                    moving = false;
                    destinations.pop_front();
                }

                if (local.getType() == DST_Home) {
                    currentDST = DST_Home;
                    state = S_None;
                    visible = false;

                    moving = false;
                    destinations.pop_front();
                }

                if (local.getType() == DST_Elevator_Exiting) {
                    currentDST = DST_Elevator_Exiting;
                    targetElevator->getCabin()->removeMovable(this);
                    targetElevator = nullptr;

                    //to proceed behind shafts
                    setDrawOrder(D_ElevatorShafts - 1, true);
                    destinations.pop_front();
                }

                if (local.getType() == DST_Unknown) {
                    currentDST = DST_Unknown;
                    destinations.pop_front();
                }

                if (local.getCoordinates() == final.getCoordinates()) {
                    //revert draw order
                    setDrawOrder(D_Characters, true);
                }
            }
        }
    }

    //one-time-exec
    //time to go home
    if (System::gameTime.isDayEndHour() && !moving) {

        moving = true;
        setDrawOrder(D_Characters, true);
        destinations.clear();

        //denormalize character
        worldCoordinates.y = getFloorBottom(floor) + height / 2;
        createHomeRoute();
    }
}

void Movable::createHomeRoute() {
    auto home = searchNearestOutside();

    if (floor == 1) {
        destinations.push_back(Destination::createHomeDST(this, home));
    } else {
        targetElevator = searchNearestElevator();
        targetElevator->incBoarding();

        if (targetElevator) {
            destinations.push_back(Destination::createElevatorWaitingDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorCabinDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorExitingDST(targetElevator, this, home));
            destinations.push_back(Destination::createHomeDST(this, home));
        }
    }
}

void Movable::createSmokeAreaRoute() {
    auto smokeArea = searchNearestOutside();

    if (floor == 1) {
        destinations.push_back(Destination::createSmokeAreaDST(this, smokeArea));
    } else {
        targetElevator = searchNearestElevator();

        if (targetElevator) {
            targetElevator->incBoarding();
            destinations.push_back(Destination::createElevatorWaitingDST(targetElevator, this));

            if (worldCoordinates.x < targetElevator->getLeft()) {
                worldCoordinates.x += 1;
            }

            if (worldCoordinates.x > targetElevator->getRight()) {
                worldCoordinates.x -= 1;
            }

            destinations.push_back(Destination::createElevatorCabinDST(targetElevator, this));
            destinations.push_back(Destination::createElevatorExitingDST(targetElevator, this, smokeArea));
            destinations.push_back(Destination::createSmokeAreaDST(this, smokeArea));
        }
    }
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

    //40% smoking people
    if (System::getRandom(0, 100) <= 40) {
        smoking = true;
    }

    switch (System::getRandom(1, 3)) {
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

    switch (System::getRandom(1, 2)) {
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
    addAnimation(S_Play, gender, race, 24);
    addAnimation(S_Walk, gender, race, 24);
    addAnimation(S_Working, gender, race, 24);
    addAnimation(S_Smoking, gender, race, 66, 2750000);

    setGroupName("movable");
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

bool Movable::isSpawned() const {
    return spawned;
}

int Movable::getFloor() const {
    return floor;
}

void Movable::setFloor(int floor) {
    Movable::floor = floor;
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
        int weight = el->getBoarding() == 0 ? distance : el->getBoarding() * distance;

        buffer[weight] = el;
    }

    return buffer.begin()->second;
}

void Movable::addAnimation(States state, Gender gender, Race race, int frames, int duration) {
    auto texture = ResourceLoader::getCharacterTexture(eType, state, gender, race);

    if (texture) {
        auto animation = Animation(this, state, frames, texture, duration);
        Entity::addAnimation(state, animation);
    } else {
        auto animation = Animation(this, state, frames,
                                   ResourceLoader::getCharacterTexture(eType, state, G_Male, R_White), duration);
        Entity::addAnimation(state, animation);
    }
}

void Movable::updateFloor() {
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;
}

sf::Vector2f Movable::searchNearestOutside() {


    return {-450, 150};
}

float Movable::getFloorBottom(int floor) {
    return System::groundLevel + Ground::height + (floor - 1) * 150;
}

float Movable::getFloorBottom(sf::Vector2f coordinates) {
    auto floor = ((int) coordinates.y - ((int) coordinates.y % System::gridSize)) / System::gridSize / 3;
    return getFloorBottom(floor);
}

//@todo optimize for only local shafts
bool Movable::isCrossingShafts() {
    auto shafts = EntityContainer::getGroupItems("shafts");

    for (auto shaft:shafts) {
        if (rect.intersects(shaft->getRect())) {
            return true;
        }
    }

    return false;
}

const std::deque<Destination> &Movable::getDestinations() const {
    return destinations;
}

void Movable::setDestinations(const std::deque<Destination> &destinations) {
    Movable::destinations = destinations;
}

Destination *Movable::getFinalDestination() {
    if (destinations.empty()) {
        return nullptr;
    }

    return &destinations.back();
}

bool Movable::isBuffed() const {
    return buffed;
}

void Movable::setBuffed(bool buffed) {
    Movable::buffed = buffed;
}

bool Movable::isWillBeBuffed() const {
    return willBeBuffed;
}

void Movable::setWillBeBuffed(bool willBeBuffed) {
    Movable::willBeBuffed = willBeBuffed;
}

float Movable::getWorkingModificator() const {
    return workingModificator;
}

void Movable::setWorkingModificator(float workingModificator) {
    Movable::workingModificator = workingModificator;
}

const GameTime &Movable::getBuffStart() const {
    return buffStart;
}

void Movable::setBuffStart(const GameTime &buffStart) {
    Movable::buffStart = buffStart;
}

const GameTime &Movable::getBuffEnd() const {
    return buffEnd;
}

void Movable::setBuffEnd(const GameTime &buffEnd) {
    Movable::buffEnd = buffEnd;
}





































