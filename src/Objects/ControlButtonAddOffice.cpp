#include <climits>
#include "../../includes/Objects/ControlButtonAddOffice.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/System/System.h"

ControlButtonAddOffice::ControlButtonAddOffice() {
    setName("button.add.office");
    setDrawOrder(INT_MAX);

    setWorldCoordinates(sf::Vector2f(ViewHandler::left + 600, ViewHandler::top - 50));

    setWidth(142);
    setHeight(47);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ButtonAddOffice));
    createAnimationFrames();

    EntityContainer::add(this);
}

void ControlButtonAddOffice::updateLogic() {
    bool spawnCondition = attachedOffice &&
                          System::cash >= attachedOffice->getCost() &&
                          !attachedOffice->isBelowGround() &&
                          !attachedOffice->intersectsWith() &&
                          (!attachedOffice->getNeighborOffices().empty() || attachedOffice->isOnTheGround());


    if (leftClicked() && !attachedOffice) {
        attachedOffice = new OfficeClerk(sf::Vector2f(System::g_x, System::g_y));
        attachedOffice->setTransparent();
    }

    if (rightClickedOutside() && attachedOffice) {
        EntityContainer::remove(attachedOffice);
        attachedOffice = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedOffice->setNormal();
        attachedOffice->spawn();

        attachedOffice = nullptr;
    }

    if (attachedOffice) {
        auto global = System::getGlobalMouse();

        float normalizedX = global.x - ((int) global.x % System::gridSize) + System::gridSize / 2;
        float normalizedY = global.y - ((int) global.y % System::gridSize) + System::gridSize / 2;

        attachedOffice->setWorldCoordinates(sf::Vector2f(normalizedX, normalizedY));

        if (!spawnCondition) {
            attachedOffice->setInvalid();
        } else {
            attachedOffice->setTransparent();
        }
    }
}
