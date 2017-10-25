#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "Chair.h"

Chair::Chair(sf::Vector2f coordinates) {
    setEType(E_Chair);
    setWidth(Chair::width);
    setHeight(Chair::height);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));

    setDrawOrder(D_Chair);
    initEntity();

    EntityContainer::add(this);
}
