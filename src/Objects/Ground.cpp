#include <SFML/System.hpp>
#include "Ground.h"
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"

Ground::Ground(sf::Vector2f coordinates) {
    setName("ground");

    setWidth(Ground::width);
    setHeight(Ground::height);
    setTextureWidth(Ground::textureWidth);
    setTextureHeight(Ground::textureHeight);
    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    addTexture(ResourceLoader::getTexture(Entities::E_StaticGround));
    createAnimationFrames();

    EntityContainer::add(this);
}