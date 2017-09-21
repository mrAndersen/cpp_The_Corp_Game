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

    setWorldCoordinates(coordinates);

    setTexture(ResourceLoader::getTexture(Entities::E_MovableClerk));
    setDrawOrder(100);
    createAnimationFrames();

    EntityContainer::add(this);
}

void Clerk::updateLogic() {
    float frameDistance = (frameTimeMs / 1000) * speed;

    if (direction == Direction::Down) {
        //falling
        worldCoordinates.y = worldCoordinates.y - frameDistance;
        speed = speed + fallAcceleration * (frameTimeMs / 1000);
    }

    if (worldCoordinates.y - height / 2 <= System::groundLevel + Ground::height) {
        direction = Direction::Right;
        speed = 300;
    }

    Movable::updateLogic();
}