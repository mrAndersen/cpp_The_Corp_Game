#include "../../includes/Office/ElevatorShaft.h"
#include "../../includes/System/EntityContainer.h"

ElevatorShaft::ElevatorShaft(sf::Vector2f coordinates) {
    setName("elevator.shaft");

    setWidth(ElevatorShaft::width);
    setHeight(ElevatorShaft::height);
    setCost(1000);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ElevatorShaftMiddle));
    setDrawOrder(98);
    createAnimationFrames();

    EntityContainer::add(this);
}
