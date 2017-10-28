#include "GroundArtifact.h"

GroundArtifact::GroundArtifact(sf::Vector2f coordinates, sf::Vector2i size, Entities type) {
    setEType(type);

    setDrawOrder(D_GroundArtifacts);
    setWidth(size.x);
    setHeight(size.y);
    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    EntityContainer::add(this);
}
