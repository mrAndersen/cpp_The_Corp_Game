#include <SFML/System.hpp>
#include "ControlButtonAddClerk.h"
#include "..\System\ViewHandler.h"
#include "..\System\System.h"

ControlButtonAddClerk::ControlButtonAddClerk(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddClerk);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddClerk::width);
    setHeight(ControlButtonAddClerk::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddClerk::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedClerk &&
                          System::cash >= attachedClerk->getCost() && !intersectsWithObjects() &&
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
        state = S_Button_Pressed;
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

    BasicUi::update();
}
