#include "ControlButtonAddElevatorShaftMiddle.h"


ControlButtonAddElevatorShaftMiddle::ControlButtonAddElevatorShaftMiddle(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_ButtonAddElevatorShaftMiddle);
    setDrawOrder(D_Ui);

    setWidth(ControlButtonAddElevatorShaftMiddle::width);
    setHeight(ControlButtonAddElevatorShaftMiddle::height);

    addAnimation(S_Button_Normal, Animation(this, S_Button_Normal, 1, ResourceLoader::getTexture(eType, S_Button_Normal)));
    addAnimation(S_Button_Pressed, Animation(this, S_Button_Pressed, 1, ResourceLoader::getTexture(eType, S_Button_Pressed)));

    setVisible(false);
    initEntity();
    EntityContainer::add(this);
}

void ControlButtonAddElevatorShaftMiddle::update() {
    if (!visible) {
        return;
    }

    state = S_Button_Normal;

    bool spawnCondition = attachedShaft &&
                          System::cash >= attachedShaft->getCost() &&
                          !attachedShaft->isBelowGround() &&
                          !attachedShaft->intersectsWithObjects() &&
                          (attachedShaft->isOnTheGround() || attachedShaft->hasMiddleShaftOnTheBottom());

    if(mouseIn()){
        System::selectionCooldown.restart();
    }

    if (leftClicked() && !attachedShaft && !System::spawningUnit) {
        attachedShaft = new ElevatorShaftMiddle(sf::Vector2f(System::g_x, System::g_y));
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

        System::spawningUnit = false;
        attachedShaft = nullptr;
    }

    if (attachedShaft) {
        System::selectionCooldown.restart();
        System::spawningUnit = true;
        auto global = System::getGlobalMouse();

        float x = roundf(global.x - ((int) global.x % System::gridSize) + width / 2);
        float y = roundf(global.y - ((int) global.y % System::gridSize) + System::gridSize / 2);

        x = System::roundToMultiple(x);
        y = System::roundToMultiple(y);

        attachedShaft->setWorldCoordinates({x, y});

        if (!spawnCondition) {
            attachedShaft->setInvalid();

            //placement error
            if (attachedShaft &&
                (attachedShaft->intersectsWithObjects() || attachedShaft->getNeighborOffices().empty() ||
                 !attachedShaft->isOnTheGround())) {
                attachedShaft->getErrorString().setString("Invalid placement position");
            }

            //cash error
            if (System::cash < attachedShaft->getCost()) {
                attachedShaft
                        ->getErrorString()
                        .setString(
                                "Not enough cash, need " +
                                System::f_to_string(std::abs(System::cash - attachedShaft->getCost())) +
                                "$ more"
                        );
            }
        } else {
            attachedShaft->setTransparent();
        }
    }

    BasicUi::update();
}
