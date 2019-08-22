#include <cmath>
#include <iostream>
#include <fstream>
#include "../Text/TextEntity.h"
#include "../Background/Ground.h"
#include "../System/EntityContainer.h"
#include "../Characters/Accountant.h"
#include "../Characters/Clerk.h"
#include "../System/System.h"
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

            quad[0].position = System::cToGl({(float) rect.left, (float) rect.top});
            quad[0].color = sf::Color::Red;

            quad[1].position = System::cToGl({(float) rect.left + width, (float) rect.top});
            quad[1].color = sf::Color::Red;

            quad[2].position = System::cToGl({(float) rect.left + width, (float) rect.top - height});
            quad[2].color = sf::Color::Red;

            quad[3].position = System::cToGl({(float) rect.left, (float) rect.top - height});
            quad[3].color = sf::Color::Red;

            quad[4].position = System::cToGl({(float) rect.left, (float) rect.top});
            quad[4].color = sf::Color::Red;

            System::window->draw(quad);
        }


        System::window->draw(debugInfo);
    }
}

void Movable::updateLogic() {
    Entity::updateLogic();

    updateFloor();
    updatePopup();

    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * currentSpeed * System::timeFactor;

    if (buffed && System::gameTime == buffEnd) {
        workingModificator = 1.f;
        buffed = false;
    }

    if (!spawned) {
        return;
    }

    if (moving) {
        state = !destinations.empty() ? S_Walk : S_None;
    }

    if (state == S_None) {
        currentSpeed = 0;
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

                //going towards home - open door
                if (local.getType() == DST_Home) {
                    if (!door && std::fabs(local.getCoordinates().x - worldCoordinates.x) <= 200) {
                        door = new Door(local.getCoordinates());

                        if (direction == Right) {
                            door->setDirection(Right);
                        }

                        if (direction == Left) {
                            door->setDirection(Left);
                        }
                    }
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

                    direction = System::getRandom(0, 100) <= 50 ? Right : Left;

                    moving = false;
                    destinations.pop_front();
                }

                if (local.getType() == DST_Home) {
                    currentDST = DST_Home;
                    state = S_None;
                    visible = false;

                    moving = false;
                    goingHome = false;
                    setDrawOrder(D_Characters, true);

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
            }
        }
    }

    //one-time-exec
    //time to go home
    if (System::gameTime.isRestTime() && visible && !goingHome) {

        moving = true;
        goingHome = true;
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

        if (targetElevator) {
            targetElevator->incBoarding();

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

Movable::Movable(Entities type, int width, int height) : Entity(type) {
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

    if (type != E_Clerk) {
        gender = G_Male;
    }

    setWidth(width);
    setHeight(height);
    setSerializable(true);

    personName = ResourceLoader::getRandomName(gender);

    popup = new Popup(0, 0);
    popup->setVisible(false);
    popup->setFixed(false);

    auto upgrade = new PopupButton;
    upgrade->setString(ResourceLoader::getTranslation("buttons.upgrade"));
    upgrade->setFixed(false);

    auto fire = new PopupButton;
    fire->setString(ResourceLoader::getTranslation("buttons.fire"));
    fire->setFixed(false);
    fire->setColor(System::c_yellow);

    popup->buttons["upgrade"] = upgrade;
    popup->buttons["fire"] = fire;

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


    loadAnimations();
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
    EntityContainer::counters[eType]++;

    System::cash -= this->cost;
    worldCoordinates.y = getFloorBottom(floor) + height / 2;

    auto *spent = new TextEntity(System::c_red, 30);
    auto position = worldCoordinates;
    position.y += height / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(this->getCost(), 0) + "$");

    recalculateBoundaries();

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

void Movable::addAnimation(States state, Gender gender, Race race, int level, int frames, int duration) {
    auto texture = ResourceLoader::getCharacterTexture(eType, state, gender, race, level);

    if (texture) {
        auto animation = Animation(this, state, frames, texture, duration);
        Entity::addAnimation(state, animation);
    } else {
        auto animation = Animation(this, state, frames, ResourceLoader::getCharacterTexture(eType, state, gender, R_White, 1), duration);
        Entity::addAnimation(state, animation);
    }
}

void Movable::updateFloor() {
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;
}

sf::Vector2f Movable::searchNearestOutside() {
    auto factor = (float) System::getRandom(0, 150);

    return {-450 + factor, 150};
}

float Movable::getFloorBottom(int floor) {
    return 0 + Ground::height + (floor - 1) * 150;
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


void Movable::upgrade() {
    lastUpgradeTimer.restart();
    level = level < 4 ? level + 1 : 4;

    animations.clear();
    loadAnimations();
}

void Movable::loadAnimations() {
    addAnimation(S_None, gender, race, level, 24);
    addAnimation(S_Play, gender, race, level, 24);
    addAnimation(S_Walk, gender, race, level, 24);
    addAnimation(S_Working, gender, race, level, 24);
    addAnimation(S_Smoking, gender, race, level, 63, 2750000);
}

void Movable::updatePopup() {
    if (!popup->isVisible() || !visible) {
        for (auto &e:popup->buttons) {
            e.second->setVisible(false);
        }

        return;
    }

    popup->getPopupText().setString(createStatsText());
    popup->getPopupText().setCharacterSize(16);

    popup->getPopupTitle().setString(personName);
    popup->setWorldCoordinates({worldCoordinates.x, worldCoordinates.y + popup->getHeight() / 2 + height / 2 + 20});

    for (auto &e:popup->buttons) {
        e.second->setVisible(true);

        if (e.first == "upgrade") {
            e.second->setWorldCoordinates({popup->getLeft() + 10 + PopupButton::width / 2, popup->getTop() - PopupButton::height / 2 - 10});

            if (e.second->isPressed() && lastUpgradeTimer.getElapsedTime().asMilliseconds() >= 500 && upgradeAvailable) {
                upgrade();
            }

            if (upgradeAvailable) {
                e.second->setColor(System::c_green);
            } else {
                e.second->setColor(System::c_red);
            }
        }

        if (e.first == "fire") {
            e.second->setWorldCoordinates({popup->getLeft() + 10 + PopupButton::width / 2, popup->getTop() - PopupButton::height / 2 - PopupButton::height - 10});

            if (e.second->isPressed()) {
                popup->setVisible(false);
                EntityContainer::remove(this);
            }
        }
    }
}

void Movable::setSelected(bool selected) {
    Entity::setSelected(selected);
    popup->setVisible(selected);
}

sf::String Movable::createStatsText() {
    sf::String s;

    if (System::debug) {
        s += "Id: " + std::to_string(id) + "\n";
        s += "Race: " + std::to_string(race) + "\n";
        s += "Gender: " + std::to_string(gender) + "\n";
    }

    if (eType == E_Clerk) {
        s += ResourceLoader::getTranslation("popup.text.role") + ": " + ResourceLoader::getTranslation("units.titles.clerk") + "\n";
    }

    s += ResourceLoader::getTranslation("popup.text.level") + ": " + std::to_string(level) + "\n";
    s += ResourceLoader::getTranslation("popup.text.state") + ": " + ResourceLoader::getStateTextNotation(state) + "\n";
    s += ResourceLoader::getTranslation("popup.text.smoking") + ": " + (smoking == 1 ? ResourceLoader::getTranslation("a.yes") : ResourceLoader::getTranslation("a.no")) + "\n";

    return s;
}

int Movable::getLevel() const {
    return level;
}

void Movable::recalculateAccountantsBonus() {
    auto movables = EntityContainer::getGroupItems("movable");
    auto totalBonus = 1.f;

    for (auto &e:movables) {
        if (e->getEType() == E_Accountant) {
            auto d = dynamic_cast<Accountant *>(e);

            totalBonus += (d->getBuffPercentages().at(d->getLevel()) / 100) * d->getWorkingModificator();
        }
    }

    System::accountantsBonus = totalBonus;
}

Popup *Movable::getPopup() const {
    return popup;
}

void Movable::setPopup(Popup *popup) {
    Movable::popup = popup;
}

bool Movable::insideElevator() {
    auto shafts = EntityContainer::getGroupItems("shafts");

    for (auto &e:shafts) {
        if (e->getRect().intersects(rect)) {
            return true;
        }
    }

    return false;
}

bool Movable::isCrossingOffices() {
    std::vector<Entity *> offices = EntityContainer::getGroupItems("offices");

    if (offices.empty()) {
        return false;
    }

    for (auto &e:offices) {
        if (e->getRect().contains(rect.left, rect.top) && e->getRect().contains(rect.left + width, rect.top - height)) {
            return true;
        }
    }

    return false;
}

bool Movable::isSmoking() const {
    return smoking;
}

void Movable::setSmoking(bool smoking) {
    Movable::smoking = smoking;
}

const GameTime &Movable::getSmokeStarted() const {
    return smokeStarted;
}

void Movable::setSmokeStarted(const GameTime &smokeStarted) {
    Movable::smokeStarted = smokeStarted;
}

Race Movable::getRace() const {
    return race;
}

void Movable::setRace(Race race) {
    Movable::race = race;
}

void Movable::setLevel(int level) {
    Movable::level = level;
}

std::map<std::string, sf::String> Movable::getSerializeParameters() {
    auto parameters = Entity::getSerializeParameters();

    parameters["defaultSpeed"] = std::to_string(defaultSpeed);
    parameters["currentSpeed"] = std::to_string(currentSpeed);
    parameters["moving"] = std::to_string(moving);
    parameters["goingHome"] = std::to_string(goingHome);
    parameters["smoking"] = std::to_string(smoking);
    parameters["buffed"] = std::to_string(buffed);
    parameters["willBeBuffed"] = std::to_string(willBeBuffed);
    parameters["willBeBuffed"] = std::to_string(willBeBuffed);
    parameters["buffStart"] = buffStart.get();
    parameters["buffEnd"] = buffEnd.get();
    parameters["smokeStarted"] = smokeStarted.get();
    parameters["workingModificator"] = std::to_string(workingModificator);
    parameters["upgradeAvailable"] = std::to_string(upgradeAvailable);

    parameters["cost"] = std::to_string(cost);
    parameters["floor"] = std::to_string(floor);
    parameters["personName"] = personName;

    parameters["gender"] = std::to_string(gender);
    parameters["race"] = std::to_string(gender);
    parameters["level"] = std::to_string(level);

//    std::deque<Destination> destinations;
//    Elevator *targetElevator = nullptr;

    return parameters;
}







































