#include <Basic/Animation.h>
#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "Tree.h"

Tree::Tree(sf::Vector2f coordinates, Entities type) {
    setEType(type);

    setDrawOrder(D_Trees);
    setWidth(Tree::width);
    setHeight(Tree::height);
    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    EntityContainer::add(this);
}
