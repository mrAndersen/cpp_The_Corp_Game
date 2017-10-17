#include <cmath>
#include "OfficeClerk.h"
#include "System/EntityContainer.h"
#include "System/System.h"

std::vector<Office *> Office::getNeighborOffices() {
    std::vector<Office *> result;
    std::vector<Office *> offices = EntityContainer::getOffices();

    for (auto target:offices) {
        if (target != this) {
            if ((int) target->getRight() == (int) this->left &&
                target->getWorldCoordinates().y == this->worldCoordinates.y && target->getFloor() == 1) {
                result.push_back(target);
            }

            if ((int) target->getLeft() == (int) this->right &&
                target->getWorldCoordinates().y == this->worldCoordinates.y && target->getFloor() == 1) {
                result.push_back(target);
            }

            if (
                    (int) target->getTop() == (int) this->bottom &&
                    this->worldCoordinates.x == target->getWorldCoordinates().x
                    ) {
                result.push_back(target);
            }
        }
    }

    return result;
}

void Office::updateLogic() {
    //update floor
    floor = ((int) worldCoordinates.y - ((int) worldCoordinates.y % System::gridSize)) / System::gridSize / 3;

    Entity::updateLogic();
}

int Office::getFloor() const {
    return floor;
}

void Office::setFloor(int floor) {
    Office::floor = floor;
}

void Office::renderDebugInfo() {
    if (System::debug) {
        debugInfo.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        debugInfo.setString(
                "id: " + std::to_string(id) + "\n" +
                "name: " + name + "\n" +
                "pos: {" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) +
                "}\n" +
                "left: " + std::to_string((int) left) + "," +
                "right: " + std::to_string((int) right) + "," +
                "top: " + std::to_string((int) top) + "," +
                "bottom: " + std::to_string((int) bottom) + "\n"
                        "floor: " + std::to_string(floor) + "\n"
                        "workers: " + std::to_string(getBusyWorkPlaces()) + "\n"
        );
        System::window->draw(debugInfo);
    }
}

float Office::getCost() const {
    return cost;
}

void Office::setCost(float cost) {
    Office::cost = cost;
}

void Office::spawn() {
    System::cash -= this->cost;

    spawned = true;
}

Office::Office() {
//    auto w1 = new WorkPlace({worldCoordinates.x,worldCoordinates.y - });
//    auto w2 = new WorkPlace({worldCoordinates.x,worldCoordinates.y - });
//    auto w3 = new WorkPlace({worldCoordinates.x,worldCoordinates.y +});
//    auto w4 = new WorkPlace({worldCoordinates.x,worldCoordinates.y +});


    setSelectable(true);
}

bool Office::hasFreeWorkPlaces() {
    for (int i = 0; i < 4; ++i) {
        if (!workPlaces[i]->getWorker()) {
            return true;
        }
    }

    return false;
}

void Office::addWorker(Movable *worker) {
    for (int i = 0; i < 4; ++i) {
        if (!workPlaces[i]->getWorker()) {
            workPlaces[i]->setWorker(worker);
        }
    }
}

int Office::getBusyWorkPlaces() {
    int j = 0;

    for (int i = 0; i < 4; ++i) {
        if (!workPlaces[i]->getWorker()) {
            j++;
        }
    }
    return j;
}

