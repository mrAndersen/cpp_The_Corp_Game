#include <SFML/System.hpp>
#include <climits>
#include "ControlButtonAddClerk.h"
#include "System/EntityContainer.h"
#include "System/ViewHandler.h"
#include "System/System.h"
#include "Text/TextEntity.h"

ControlButtonAddClerk::ControlButtonAddClerk() {
    setName("button.add.clerk");
    setDrawOrder(INT_MAX);

    setWidth(142);
    setHeight(47);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(E_ButtonAddClerk, S_None)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddClerk::updateLogic() {
    bool spawnCondition = attachedClerk &&
                          System::cash >= attachedClerk->getCost() &&
                          !attachedClerk->isBelowGround();

    if (leftClicked() && !attachedClerk && !System::spawningUnit) {
        attachedClerk = new Clerk({System::g_x, System::g_y});
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

        auto *spent = new TextEntity(System::c_red, 30);
        auto position = attachedClerk->getWorldCoordinates();
        position.y += attachedClerk->getHeight() / 2;

        spent->setLiveTimeSeconds(4);
        spent->setWorldCoordinates(position);
        spent->setString("-" + System::f_to_string(attachedClerk->getCost()) + "$");

        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    if (attachedClerk) {
        System::spawningUnit = true;
        attachedClerk->setWorldCoordinates(System::getGlobalMouse());

        if (!spawnCondition) {
            attachedClerk->setInvalid();

            //placement error
            if (attachedClerk && attachedClerk->isBelowGround() &&
                attachedClerk->getErrorString().getString().isEmpty()) {
                attachedClerk->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedClerk->getCost() && attachedClerk->getErrorString().getString().isEmpty()) {
                attachedClerk->getErrorString().setString("Not enough cash");
            }
        } else {
            attachedClerk->setTransparent();
        }
    }
}
