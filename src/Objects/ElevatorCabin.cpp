//
// Created by mrAndersen on 16.10.2017.
//

#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "ElevatorCabin.h"

ElevatorCabin::ElevatorCabin(sf::Vector2f coordinates) {
    setName("elevator.cabin");

    setWidth(ElevatorCabin::width);
    setHeight(ElevatorCabin::height);
    setCost(500);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ElevatorCabin));
    setDrawOrder(98);
    createAnimationFrames();

    EntityContainer::add(this);
}

float ElevatorCabin::getCost() const {
    return cost;
}

void ElevatorCabin::setCost(float cost) {
    ElevatorCabin::cost = cost;
}

bool ElevatorCabin::isSpawned() const {
    return spawned;
}

void ElevatorCabin::setSpawned(bool spawned) {
    ElevatorCabin::spawned = spawned;
}
