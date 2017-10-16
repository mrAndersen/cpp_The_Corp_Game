#include "ElevatorShaftMiddle.h"
#include "System/EntityContainer.h"

ElevatorShaftMiddle::ElevatorShaftMiddle(sf::Vector2f coordinates) {
    setName("elevator.shaft.middle");

    setWidth(ElevatorShaftMiddle::width);
    setHeight(ElevatorShaftMiddle::height);
    setCost(1000);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ElevatorShaftMiddle));
    setDrawOrder(98);
    createAnimationFrames();

    EntityContainer::add(this);
}


