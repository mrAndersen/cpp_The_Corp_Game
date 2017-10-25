#include <SFML/System.hpp>
#include "Ground.h"
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"

Ground::Ground(sf::Vector2f coordinates) {
    setEType(E_StaticGround);
    setWidth(Ground::width);
    setHeight(Ground::height);
    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));

    initEntity();

    EntityContainer::add(this);
}