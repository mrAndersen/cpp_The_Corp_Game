#include <SFML/System.hpp>
#include "Ground.h"
#include "..\System\ResourceLoader.h"
#include "..\System/EntityContainer.h"
#include "Cloud.h"

Cloud::Cloud(Entities type, sf::Vector2f coordinates, sf::Vector2f size, float scale, int speed, Scenes lType) {
    this->speed = speed;
    this->size = size;
    this->lType = lType;

    setEType(type);
    setDrawOrder(D_BG_Mountain_2 + 1);

    setWidth((int) size.x);
    setHeight((int) size.y);
    setWorldCoordinates(coordinates);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    currentAnimation->getSprite().setScale({scale, scale});
    EntityContainer::add(this);
}

void Cloud::updateLogic() {
    Entity::updateLogic();

    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * speed * System::timeFactor;

    worldCoordinates.x += frameDistance;

    if(lType == SC_Main_Menu){
        if(this->left > ViewHandler::right){
            this->worldCoordinates.x = -(this->size.x / 2);
        }
    }

    if(lType == SC_Game){
        if(this->left > System::worldWidth / 2){
            this->worldCoordinates.x = -System::worldWidth / 2 - size.x;
        }
    }
}

int Cloud::getSpeed() const {
    return speed;
}

void Cloud::setSpeed(int speed) {
    Cloud::speed = speed;
}

void Cloud::createRandomCloud(Scenes lType) {
    Entities clouds[4] = {E_Cloud1, E_Cloud2, E_Cloud3, E_Cloud4};
    sf::Vector2f cloudSizes[4] = {{712, 242}, {548, 174}, {274, 134}, {276, 106}};
    sf::Vector2f coordinates;

    auto type = System::getRandom(0, 3);
    auto scale = System::getRandom(30, 60);
    auto speed = System::getRandom(20, 35);

    if(lType == SC_Main_Menu){
        coordinates.y = System::getRandom(0, System::screenHeight);
        coordinates.x = System::getRandom(-100, System::screenWidth - (int) (cloudSizes[type].x / 2));
    }

    if(lType == SC_Game){
        coordinates.y = System::getRandom(500, 5000);
        coordinates.x = System::getRandom(-System::worldWidth / 2, System::worldWidth / 2 - (int)(cloudSizes[type].x / 2));
    }

    auto cloud = new Cloud(clouds[type], coordinates, cloudSizes[type], (float)scale / 100, speed, lType);
}
