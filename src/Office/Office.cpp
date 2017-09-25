#include "../../includes/Office/OfficeClerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/System/System.h"

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

            if ((int) target->getTop() == (int) this->bottom && this->worldCoordinates.x > target->getLeft() &&
                this->worldCoordinates.x < target->getRight()) {
                result.push_back(target);
            }
        }
    }

    return result;
}

bool Office::intersectsWith() {
    std::vector<Office *> result;
    std::vector<Office *> offices = EntityContainer::getOffices();

    for (auto target:offices) {
        if (target != this) {
            if (this->rect.intersects(target->getRect())) {
                return true;
            }
        }
    }

    return false;
}

void Office::updateLogic() {
    floor = (int) ((worldCoordinates.y - height / 2) / 100);

    Entity::updateLogic();
}

int Office::getFloor() const {
    return floor;
}

void Office::setFloor(int floor) {
    Office::floor = floor;
}

void Office::renderDebugInfo() {
    if (System::animationDebug) {
        info.setPosition(System::cToGl(worldCoordinates.x + width / 2, worldCoordinates.y + height / 2));
        info.setString(
                "pos: {" + std::to_string(worldCoordinates.x) + "," + std::to_string(worldCoordinates.y) + "}\n" +
                "left: " + std::to_string(left) + "\n" +
                "right: " + std::to_string(right) + "\n" +
                "top: " + std::to_string(top) + "\n" +
                "bottom: " + std::to_string(bottom) + "\n"
                        "floor: " + std::to_string(floor) + "\n"
        );
        System::window->draw(info);
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
}

bool Office::hasFreeWorkPlaces() {
    return workers.size() < 4;
}


