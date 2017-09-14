#include "../../includes/Animation/Movable.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/Characters/Clerk.h"


Clerk::Clerk(sf::Vector2f coordinates) {
    this->setName("clerk");

    this->setWidth(Clerk::width);
    this->setHeight(Clerk::height);
    this->setTotalFrames(24);
    this->setSpeed(100);

    this->setWorldCoordinates(coordinates);

    this->setTexture(ResourceLoader::getSingleTexture(Objects::CharacterClerk));
    this->createAnimationFrames();
}