#include "../../includes/Office/OfficeClerk.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"

OfficeClerk::OfficeClerk(sf::Vector2f coordinates) {
    setName("office.clerk");

    setWidth(OfficeClerk::width);
    setHeight(OfficeClerk::height);

    setWorldCoordinates(coordinates);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_OfficeClerk));
    createAnimationFrames();
    setDrawOrder(98);

    EntityContainer::add(this);
}

void OfficeClerk::updateLogic() {


}
