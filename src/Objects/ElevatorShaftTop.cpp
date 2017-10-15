#include "../../includes/Office/ElevatorShaftTop.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Office/ElevatorShaftMiddle.h"


ElevatorShaftTop::ElevatorShaftTop(sf::Vector2f coordinates) {
    setName("elevator.shaft.top");

    setWidth(ElevatorShaftTop::width);
    setHeight(ElevatorShaftTop::height);
    setCost(1000);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ElevatorShaftTop));
    setDrawOrder(98);
    createAnimationFrames();

    EntityContainer::add(this);
}

bool ElevatorShaftTop::hasMiddleShaftOnTheBottom() {
    for (auto e:EntityContainer::getItems()) {

        if (auto d = dynamic_cast<ElevatorShaftMiddle *>(e) && e->getTop() == bottom) {
            return true;
        }
    }

    return false;
}


