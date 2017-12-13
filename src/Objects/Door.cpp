#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include "Door.h"

Door::Door(sf::Vector2f coordinates) {
    setEType(E_Door);

    setDrawOrder(D_Ui - 1);
    setWidth(Door::width);
    setHeight(Door::height);

    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 64, ResourceLoader::getTexture(eType), 2666666));
    initEntity();

    EntityContainer::add(this);
}

void Door::updateLogic() {

    //remove after animation finished
    if (liveClock.getElapsedTime().asMicroseconds() >= currentAnimation->getAnimationResolution() * currentAnimation->getTotalFrames() / System::timeFactor) {
        EntityContainer::remove(this);
    }
}
