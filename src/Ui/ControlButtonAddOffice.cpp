#include <climits>
#include <cmath>
#include "ControlButtonAddOffice.h"
#include "..\System\EntityContainer.h"
#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "..\Office\OfficeClerk.h"
#include "../System/ResourceLoader.h"

ControlButtonAddOffice::ControlButtonAddOffice(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddOffice);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddOffice::width);
    setHeight(ControlButtonAddOffice::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddOffice::update() {
    state = S_Button_Normal;

    bool spawnCondition = attachedOffice &&
                          System::cash >= attachedOffice->getCost() &&
                          !attachedOffice->isBelowGround() &&
                          !attachedOffice->intersectsWithObjects() &&
                          (!attachedOffice->getNeighborOffices().empty() || attachedOffice->isOnTheGround());

    if (leftClicked() && !attachedOffice && !System::spawningUnit) {
        attachedOffice = new OfficeClerk(sf::Vector2f(System::g_x, System::g_y));
        attachedOffice->setTransparent();
    }

    if (rightClickedOutside() && attachedOffice) {
        EntityContainer::remove(attachedOffice);

        System::spawningUnit = false;
        attachedOffice = nullptr;
    }

    //spawn
    if (leftClickedOutside() && spawnCondition) {
        attachedOffice->setNormal();
        attachedOffice->spawn();

        System::spawningUnit = false;
        attachedOffice = nullptr;
    }

    if (attachedOffice) {
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();
        state = S_Button_Pressed;

        float normalizedX = global.x - ((int) global.x % System::gridSize) + System::gridSize;
        float normalizedY = global.y - ((int) global.y % System::gridSize) + System::gridSize / 2;

        attachedOffice->setWorldCoordinates(sf::Vector2f(normalizedX, normalizedY));

        if (!spawnCondition) {
            attachedOffice->setInvalid();

            //placement error
            if (attachedOffice && (attachedOffice->intersectsWithObjects() || attachedOffice->getNeighborOffices().empty() || !attachedOffice->isOnTheGround())) {
                attachedOffice->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedOffice->getCost()) {
                attachedOffice
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(std::abs(System::cash - attachedOffice->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedOffice->setTransparent();
        }
    }

    BasicUi::update();
}
