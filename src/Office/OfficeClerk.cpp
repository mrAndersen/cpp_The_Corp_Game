#include "../../includes/Office/OfficeClerk.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"

OfficeClerk::OfficeClerk(sf::Vector2f coordinates) {
    setName("office.clerk");

    setWidth(OfficeClerk::width);
    setHeight(OfficeClerk::height);
    setCost(2500);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_OfficeClerk));
    setDrawOrder(98);
    createAnimationFrames();

    EntityContainer::add(this);
}

void OfficeClerk::updateLogic() {
    Office::updateLogic();
}

std::string OfficeClerk::serialize() {
    return Entity::serialize();
}
