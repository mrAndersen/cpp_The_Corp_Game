#include <SFML/System.hpp>
#include "../../includes/Objects/Ground.h"

Ground::Ground(sf::Vector2f coordinates) {
    this->setName("ground");

    this->setWidth(Ground::width);
    this->setHeight(Ground::height);

    this->setWorldCoordinates(coordinates);

//    this->setTexture(ResourceLoader::getSingleTexture(Objects::CharacterClerk));
    this->createAnimationFrames();
}