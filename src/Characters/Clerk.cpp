#include "../../includes/EntityAnimation/EntityAnimation.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/Characters/Clerk.h"


Clerk::Clerk(int x, int y) {
    this->setName("clerk");

    this->setWidth(128);
    this->setHeight(125);
    this->setSpeed(100);

    this->setX(x);
    this->setY(y);

    this->setTexture(ResourceLoader::getSingleTexture(Objects ::CharacterClerk));
    this->createAnimationFrames();
}