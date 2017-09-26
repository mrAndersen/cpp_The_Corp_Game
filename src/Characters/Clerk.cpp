#include "../../includes/Animation/Movable.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"

Clerk::Clerk(sf::Vector2f coordinates) {
    setName("clerk");

    setWidth(Clerk::width);
    setHeight(Clerk::height);
    setTotalFrames(24);
    setSpeed(300);
    setCost(500);

    setWorldCoordinates(coordinates);

    setTexture(ResourceLoader::getTexture(Entities::E_Clerk));
    setDrawOrder(100);
    createAnimationFrames();

    EntityContainer::add(this);
}

void Clerk::updateLogic() {







    Movable::updateLogic();
}