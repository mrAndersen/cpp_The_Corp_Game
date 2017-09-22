#include "../../includes/Office/OfficeClerk.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Office/Office.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"

std::vector<Office *> Office::getNeighborOffices() {
    std::vector<Office *> result;
    std::vector<Office *> offices = EntityContainer::getOffices();

    for (auto target:offices) {
        if (target != this) {
            if ((int) target->getRight() == (int) this->left &&
                target->getWorldCoordinates().y == this->worldCoordinates.y && floor == target->getFloor() == 1) {
                result.push_back(target);
            }

            if ((int) target->getLeft() == (int) this->right &&
                target->getWorldCoordinates().y == this->worldCoordinates.y && floor == target->getFloor() == 1) {
                result.push_back(target);
            }

            if ((int) target->getTop() == (int) this->bottom && this->worldCoordinates.x > target->getLeft() &&
                this->worldCoordinates.x < target->getRight()) {
                result.push_back(target);
            }
        }
    }

//    if (result.size() >= 2) {
//        std::sort(result.begin(), result.end());
//        result.erase(std::unique(result.begin(), result.end()));
//    }


    return result;
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
