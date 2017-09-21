#include <SFML/System.hpp>
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"

Ground::Ground(sf::Vector2f coordinates) {
    setName("ground");

    setWidth(Ground::width);
    setHeight(Ground::height);
    setTextureWidth(Ground::textureWidth);
    setTextureHeight(Ground::textureHeight);
    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_StaticGround));
    createAnimationFrames();

    EntityContainer::add(this);
}