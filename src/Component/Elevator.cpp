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
    sf::Vector2f position(left, top);

    rect.setPosition(System::cToGl(position));
    rect.setSize({20, 20});
    rect.setFillColor(sf::Color::Green);
    System::window->draw(rect);


    if (System::debug > 0) {
        sf::Text text;
        std::string ds;

        text.setFillColor(sf::Color::Black);
        text.setFont(*System::debugFont);
        text.setCharacterSize(20);
        text.setPosition(System::cToGl(position));
        ds = "b:" + std::to_string(boarding) + "d:" + std::to_string(direction) + "q:";

        for (auto i:queue) {
            ds += std::to_string(i) + ",";
        }

        text.setString(ds);
        System::window->draw(text);
    }
}

void Elevator::update() {
    if (!waiting) {
        float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
        float frameDistance = frameTimeSeconds * cabin->getSpeed() * System::timeFactor;

        auto next = queue.front();
        auto current = cabin->getWorldCoordinates();
        auto nextCoord = sf::Vector2f(cabin->getWorldCoordinates().x,
                                      next * System::gridSize * 3 + System::gridSize / 2);

        if (direction == Up) {
            if (current.y + 100 >= nextCoord.y) {
                frameDistance = frameDistance / 2;
            }

            cabin->setWorldCoordinates({current.x, current.y + frameDistance});
        }

        if (direction == Down) {
            if (current.y - 100 <= nextCoord.y) {
                frameDistance = frameDistance / 2;
            }

            cabin->setWorldCoordinates({current.x, current.y - frameDistance});
        }

        if (current.y > nextCoord.y && direction == Up) {
            cabin->setWorldCoordinates({current.x, nextCoord.y});
            waiting = true;
        }

        if (current.y < nextCoord.y && direction == Down) {
            cabin->setWorldCoordinates({current.x, nextCoord.y});
            waiting = true;
        }

        if ((int) current.y == (int) nextCoord.y) {
            cabin->setWorldCoordinates(nextCoord);

            if (!queue.empty()) {
                queue.erase(queue.begin());
            }

            waiting = true;
        }
    }

    if (cabin->getCurrentPeople().empty() && queue.empty()) {
        waiting = true;
    } else {
        auto people = cabin->getCurrentPeople();
        auto finishedEntering = 0;

        for (auto p:people) {
            if (p->getState() == S_None && p->getLeft() >= cabin->getLeft() && p->getRight() <= cabin->getRight()) {
                finishedEntering++;
            }
        }

        waiting = finishedEntering != people.size();
    }

    if (queue.empty()) {
        direction = None;
    }
}

void Elevator::addToQueue(int floor) {
    if (queue.size() == cabin->getCapacity()) {
        return;
    }

    if (queue.empty() && floor > cabin->getFloor() && direction == None) {
        direction = Up;
    }

    if (queue.empty() && floor < cabin->getFloor() && direction == None) {
        direction = Down;
    }

    if (direction == Up && floor < cabin->getFloor()) {
        return;
    }

    if (direction == Down && floor > cabin->getFloor()) {
        return;
    }

    if (std::find(queue.begin(), queue.end(), floor) == queue.end() && this->cabin->getFloor() != floor) {
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
