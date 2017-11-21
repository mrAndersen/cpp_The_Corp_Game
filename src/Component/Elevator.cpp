#include "..\System\EntityContainer.h"

void Elevator::finish() {
    if (topShaft) {
        left = topShaft->getLeft();
        right = topShaft->getRight();
        top = topShaft->getTop();
    }

    topShaft->setElevator(this);
    EntityContainer::addElevator(this);
}

void Elevator::addCabin(ElevatorCabin *cabin) {
    this->cabin = cabin;
}

void Elevator::addTopSection(ElevatorShaftTop *shaft) {
    this->topShaft = shaft;
}

void Elevator::addMiddleSection(ElevatorShaftMiddle *shaft) {
    middleShafts.push_back(shaft);
}

void Elevator::drawDebug() {

    sf::RectangleShape rect;
    sf::Vector2f position(left, System::groundLevel + 40);

    rect.setPosition(System::cToGl(position));
    rect.setSize({20, 20});
    rect.setFillColor(sf::Color::Green);
    System::window->draw(rect);


    if (System::debug > 0) {
        sf::Text text;
        std::string ds;

        text.setFillColor(sf::Color::White);
        text.setFont(*System::debugFont);
        text.setCharacterSize(20);
        text.setPosition(System::cToGl(position));
        ds = "waiting:" + std::to_string(waiting) + ";boarding:" + std::to_string(boarding);
        ds = ds + ";direction:";

        if (direction == Up) {
            ds = ds + "Up;";
        }

        if (direction == Down) {
            ds = ds + "Down;";
        }

        if (direction == None) {
            ds = ds + "None;";
        }

//        ds = ds + std::to_string(waitClock.getElapsedTime().asSeconds()) + ";";
        ds = ds + "q ";

        for (auto i:queue) {
            ds += std::to_string(i) + ",";
        }

        text.setString(ds);
        System::window->draw(text);
    }
}

void Elevator::update() {
    auto frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    auto distance = frameTimeSeconds * cabin->getSpeed() * System::timeFactor;
    auto waitTime = 0.5f;

    //spam fucking button
    if (!cabin->getCurrentPeople().empty()) {
        for (auto &p:cabin->getCurrentPeople()) {
            addToQueue(p->getFinalDestination()->getFloor());
        }
    }

    if (queue.empty() && cabin->getCurrentPeople().empty()) {
        direction = None;
    }

    if (!waiting && !queue.empty()) {
        auto nextFloor = queue.front();
        auto nextTarget = getFloorBottom(nextFloor) + cabin->getHeight() / 2;
        auto currentPosition = cabin->getWorldCoordinates();

        if (direction == Up) {
            cabin->setWorldCoordinates({currentPosition.x, currentPosition.y + distance});

            if (cabin->getWorldCoordinates().y >= nextTarget) {
                cabin->setWorldCoordinates({cabin->getWorldCoordinates().x, nextTarget});
                waiting = true;
                waitClock.restart();
                queue.pop_front();
            }
        }

        if (direction == Down) {
            cabin->setWorldCoordinates({currentPosition.x, currentPosition.y - distance});

            if (cabin->getWorldCoordinates().y <= nextTarget) {
                cabin->setWorldCoordinates({cabin->getWorldCoordinates().x, nextTarget});
                waiting = true;
                waitClock.restart();
                queue.pop_front();
            }
        }
    }

    //boarding
    if (waitClock.getElapsedTime().asSeconds() >= waitTime && !cabin->getCurrentPeople().empty()) {
        auto people = cabin->getCurrentPeople();
        auto finishedEntering = 0;

        for (auto p:people) {
            if (p->getState() == S_None && p->getLeft() >= cabin->getLeft() && p->getRight() <= cabin->getRight()) {
                finishedEntering++;
            }
        }

        waiting = finishedEntering != people.size();
    }

    //emtpy cabin to dest floor
    if (cabin->getCurrentPeople().empty() && !queue.empty() && waitClock.getElapsedTime().asSeconds() >= waitTime) {
        waiting = false;
    }
}

void Elevator::addToQueue(int floor) {
    //same floor
    if (floor == cabin->getFloor()) {
        return;
    }

    //don't add lower then target if we go up
    if (!queue.empty() && direction == Up && floor < cabin->getFloor()) {
        return;
    }

    if (!queue.empty() && direction == Down && floor > cabin->getFloor()) {
        return;
    }

    if (queue.empty() && floor > cabin->getFloor()) {
        direction = Up;
    }

    if (queue.empty() && floor < cabin->getFloor()) {
        direction = Down;
    }

    if (std::find(queue.begin(), queue.end(), floor) == queue.end()) {
        queue.push_back(floor);

        if (direction == Up) {
            std::sort(queue.begin(), queue.end(), std::less<int>());
        }

        if (direction == Down) {
            std::sort(queue.begin(), queue.end(), std::greater<int>());
        }
    }
}

float Elevator::getTop() const {
    return top;
}

void Elevator::setTop(float top) {
    Elevator::top = top;
}

float Elevator::getLeft() const {
    return left;
}

void Elevator::setLeft(float left) {
    Elevator::left = left;
}

float Elevator::getRight() const {
    return right;
}

void Elevator::setRight(float right) {
    Elevator::right = right;
}

ElevatorCabin *Elevator::getCabin() const {
    return cabin;
}

void Elevator::setCabin(ElevatorCabin *cabin) {
    Elevator::cabin = cabin;
}

bool Elevator::isWaiting() const {
    return waiting;
}

void Elevator::setWaiting(bool waiting) {
    Elevator::waiting = waiting;
}

int Elevator::getBoarding() const {
    return boarding;
}

void Elevator::decBoarding() {
    boarding--;
}

void Elevator::incBoarding() {
    boarding++;
}

const std::deque<int> &Elevator::getQueue() const {
    return queue;
}

float Elevator::getFloorBottom(int floor) {
    return System::groundLevel + Ground::height + (floor - 1) * 150;
}
