#include <System/EntityContainer.h>
#include "Elevator.h"

void Elevator::finish() {
    if(!topShaft){
        throw std::invalid_argument("Invalid elevator, top shaft unset");
    }

    if (topShaft) {
        left = topShaft->getLeft();
        right = topShaft->getRight();
        top = topShaft->getTop();
    }

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
