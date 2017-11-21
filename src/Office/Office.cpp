#include <cmath>
#include "..\Text\TextEntity.h"
#include "OfficeClerk.h"
#include "..\System\EntityContainer.h"
#include "..\System\System.h"

Office::Office() {
    setGroupName("offices");

    workPlaces[0] = new WorkPlace(worldCoordinates, this);
    workPlaces[1] = new WorkPlace(worldCoordinates, this);
    workPlaces[2] = new WorkPlace(worldCoordinates, this);
    workPlaces[3] = new WorkPlace(worldCoordinates, this);

    setSelectable(true);
}


std::vector<Office *> Office::getNeighborOffices() {
    std::vector<Office *> result;
    std::vector<Entity *> offices = EntityContainer::getGroupItems("offices");

    for (auto e:offices) {
        auto target = dynamic_cast<Office *>(e);

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

    workPlaces[0]->setWorldCoordinates({worldCoordinates.x - width / 2 + 70, worldCoordinates.y - 11});
    workPlaces[1]->setWorldCoordinates({worldCoordinates.x - width / 2 + 220, worldCoordinates.y - 11});
    workPlaces[2]->setWorldCoordinates({worldCoordinates.x - width / 2 + 372, worldCoordinates.y - 11});
    workPlaces[3]->setWorldCoordinates({worldCoordinates.x - width / 2 + 516, worldCoordinates.y - 11});

    for (auto w:workPlaces) {
        w->update();
    }

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
                "type: " + std::to_string(eType) + "\n" +
                "pos: {" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) +
                "}\n" +
                "left: " + std::to_string((int) left) + "," +
                "right: " + std::to_string((int) right) + "," +
                "top: " + std::to_string((int) top) + "," +
                "bottom: " + std::to_string((int) bottom) + "\n"
                        "floor: " + std::to_string(floor) + "\n"
                        "workers: " + std::to_string(getBusyWorkPlaces()) + "\n"
        );

        for (auto &workPlace : workPlaces) {
            workPlace->drawDebug();
        }

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

    auto *spent = new TextEntity(System::c_red, 30);
    auto position = worldCoordinates;
    position.y += height / 2;

    spent->setLiveTimeSeconds(4);
    spent->setWorldCoordinates(position);
    spent->setString("-" + System::f_to_string(cost) + "$");

    Entity::spawn();
}

bool Office::hasFreeWorkPlaces() {
    for (auto &workPlace : workPlaces) {
        if (!workPlace->getWorker()) {
            return true;
        }
    }

    return false;
}

void Office::addWorker(Movable *worker) {
    for (auto &workPlace : workPlaces) {
        if (!workPlace->getWorker()) {
            workPlace->setWorker(worker);
        }
    }
}

int Office::getBusyWorkPlaces() {
    int j = 0;

    for (auto &workPlace : workPlaces) {
        if (workPlace->getWorker() != nullptr) {
            j++;
        }
    }
    return j;
}

WorkPlace *Office::getNextFreeWorkPlace() {
    for (auto &workPlace : workPlaces) {
        if (!workPlace->getWorker()) {
            return workPlace;
        }
    }

    return nullptr;
}

WorkPlace *const *Office::getWorkPlaces() const {
    return workPlaces;
}

