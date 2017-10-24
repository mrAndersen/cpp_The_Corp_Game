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

    setWidth(ControlButtonAddClerk::width);
    setHeight(ControlButtonAddClerk::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(E_ButtonAddClerk, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(E_ButtonAddClerk, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddClerk::update() {
    selectAnimation(S_Button_Normal);

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

        System::spawningUnit = false;
        attachedClerk = nullptr;
    }

    if (attachedClerk) {
        selectAnimation(S_Button_Pressed);
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

    worldCoordinates.x = ViewHandler::left + width / 2 + 6;
    worldCoordinates.y = ViewHandler::top - 400;

    if (currentAnimation) {
        currentAnimation->update();
    }
}
