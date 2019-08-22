#include "OfficeClerk.h"
#include "../System/ResourceLoader.h"
#include "../System/EntityContainer.h"

OfficeClerk::OfficeClerk(sf::Vector2f coordinates) : Office() {
    setEType(E_OfficeDefault);
    setWidth(OfficeClerk::width);
    setHeight(OfficeClerk::height);
    setCost(2500);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 6, ResourceLoader::getTexture(eType)));

    setDrawOrder(D_Offices);
    initEntity();

    EntityContainer::add(this);
}

void OfficeClerk::updateLogic() {
    Office::updateLogic();
}
