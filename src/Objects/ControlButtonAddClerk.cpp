#include <SFML/System.hpp>
#include <climits>
#include "../../includes/Objects/ControlButtonAddClerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/System/System.h"

ControlButtonAddClerk::ControlButtonAddClerk() {
    setName("button.add.clerk");
    setDrawOrder(INT_MAX);

    setWorldCoordinates(sf::Vector2f(ViewHandler::left + 600, ViewHandler::top - 50));

    setWidth(142);
    setHeight(47);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ButtonAddClerk));
    createAnimationFrames();

    EntityContainer::add(this);
}

void ControlButtonAddClerk::updateLogic() {

    if (leftClicked() && !attachedClerk) {
        attachedClerk = new Clerk(sf::Vector2f(System::g_x, System::g_y));

    }

    if (rightClickedOutside() && attachedClerk) {
        EntityContainer::remove(attachedClerk);
        attachedClerk = nullptr;
    }

    //spawn
    if (leftClickedOutside() && attachedClerk && !attachedClerk->isBelowGround()) {
        attachedClerk->removeTransparency();
        attachedClerk->setDirection(Direction::Down);
        attachedClerk = nullptr;
    }

    if (attachedClerk) {
        attachedClerk->setWorldCoordinates(System::getGlobalMouse());

        if (attachedClerk->isBelowGround()) {
            attachedClerk->setInvalid();
        } else {
            attachedClerk->setTransparent();
        }
    }
}
