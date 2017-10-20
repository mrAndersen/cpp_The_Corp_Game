#include "OfficeClerk.h"
#include "System/ResourceLoader.h"
#include "System/EntityContainer.h"

OfficeClerk::OfficeClerk(sf::Vector2f coordinates) : Office() {
    setName("office.clerk");

    setWidth(OfficeClerk::width);
    setHeight(OfficeClerk::height);
    setCost(2500);

    setWorldCoordinates(coordinates);
    addAnimation(S_None, Animation(this, S_None, 6, ResourceLoader::getTexture(E_OfficeDefault)));

    setDrawOrder(D_Offices);
    initEntity();

    EntityContainer::add(this);
}

void OfficeClerk::updateLogic() {
    Office::updateLogic();
}

std::string OfficeClerk::serialize() {
    return Entity::serialize();
}
