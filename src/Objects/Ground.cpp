#include <SFML/System.hpp>
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/ResourceLoader.h"

Ground::Ground(sf::Vector2f coordinates) {
    this->setName("ground");

    this->setWidth(Ground::width);
    this->setHeight(Ground::height);

    this->setWorldCoordinates(coordinates);

    this->setTotalFrames(1);
    this->setTexture(ResourceLoader::getSingleTexture(Entities::StaticGround));
    this->createAnimationFrames();
}