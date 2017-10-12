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
    bool spawnCondition = attachedClerk &&
                          System::cash >= attachedClerk->getCost() &&
                          !attachedClerk->isBelowGround();

    if (leftClicked() && !attachedClerk && !System::spawningUnit) {
        attachedClerk = new Clerk(sf::Vector2f(System::g_x, System::g_y));
    }

    if (rightClickedOutside() && attachedClerk) {
        EntityContainer::remove(attachedClerk);


        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedClerk->setNormal();
        attachedClerk->setDirection(Direction::Down);
        attachedClerk->spawn();


        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    if (attachedClerk) {
        System::spawningUnit = true;
        attachedClerk->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedClerk->setInvalid();

            if (System::cash < attachedClerk->getCost()) {
                attachedClerk->getErrorString().setString("Not enough cash");
            }
        } else {
            attachedClerk->setTransparent();
        }
    }
}
