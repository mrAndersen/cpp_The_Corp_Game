#include <SFML/System.hpp>
#include "Ground.h"
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"

Ground::Ground(sf::Vector2f coordinates) {
    setName("ground");

    setWidth(Ground::width);
    setHeight(Ground::height);
    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_StaticGround)));

    initEntity();

    EntityContainer::add(this);
}