#ifndef CORP_GAME_CLERK
#define CORP_GAME_CLERK

#include <SFML/Graphics.hpp>
#include <Animation/EntityAnimation.cpp>
#include <System/ResourceLoader.cpp>

class Clerk : public EntityAnimation {
public:
    Clerk(int x, int y) {
        this->setName("clerk");

        this->setWidth(128);
        this->setHeight(125);
        this->setSpeed(100);

        this->setX(x);
        this->setY(y);

        this->setTexture(ResourceLoader::getSingleTexture(Objects ::CharacterClerk));
        this->createAnimationFrames();
    }
};

#endif
