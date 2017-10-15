#include "../../includes/Controls/ControlButtonAddElevator.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/System/System.h"
#include "../../includes/Text/TextEntity.h"

ControlButtonAddElevator::ControlButtonAddElevator() {
    setName("button.add.elevator");
    setDrawOrder(INT_MAX);

    setWorldCoordinates(sf::Vector2f(ViewHandler::left + 750, ViewHandler::top - 50));

    setWidth(142);
    setHeight(47);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ButtonAddElevator));
    createAnimationFrames();

    EntityContainer::add(this);
}

void ControlButtonAddElevator::updateLogic() {
    bool spawnCondition = attachedShaft &&
                          System::cash >= attachedShaft->getCost() &&
                          !attachedShaft->isBelowGround() &&
                          !attachedShaft->intersectsWith() &&
                          (!attachedShaft->getNeighborOffices().empty() || attachedShaft->isOnTheGround());

    if (leftClicked() && !attachedShaft) {
        attachedShaft = new ElevatorShaft(sf::Vector2f(System::g_x, System::g_y));
        attachedShaft->setTransparent();
    }

    if (rightClickedOutside() && attachedShaft) {
        EntityContainer::remove(attachedShaft);

        System::spawningUnit = false;
        attachedShaft = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedShaft->setNormal();
        attachedShaft->spawn();

        auto *spent = new TextEntity(System::c_red, 30);
        auto position = attachedShaft->getWorldCoordinates();
        position.y += attachedShaft->getHeight() / 2;

        spent->setLiveTimeSeconds(4);
        spent->setWorldCoordinates(position);
        spent->setString("-" + System::f_to_string(attachedShaft->getCost()) + "$");

        System::spawningUnit = false;
        attachedShaft = nullptr;
    }

    if (attachedShaft) {
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();

        float normalizedX = global.x - ((int) global.x % System::gridSize) + System::gridSize / 2;
        float normalizedY = global.y - ((int) global.y % System::gridSize) + System::gridSize / 2;

        attachedShaft->setWorldCoordinates(sf::Vector2f(normalizedX, normalizedY));

        if (!spawnCondition) {
            attachedShaft->setInvalid();

            //placement error
            if (attachedShaft && (attachedShaft->intersectsWith() || attachedShaft->getNeighborOffices().empty() ||
                                  !attachedShaft->isOnTheGround())) {
                attachedShaft->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedShaft->getCost()) {
                attachedShaft
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(abs(System::cash - attachedShaft->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedShaft->setTransparent();
        }
    }
}
