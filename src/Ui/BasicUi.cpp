#include "BasicUi.h"

BasicUi::BasicUi(float leftOffset, float topOffset) {
    this->leftOffset = leftOffset;
    this->topOffset = topOffset;
}

void BasicUi::update() {
    worldCoordinates.x = ViewHandler::left + leftOffset;
    worldCoordinates.y = ViewHandler::top - topOffset;

    if (currentAnimation) {
        currentAnimation->update();
    }
}

bool BasicUi::isPressed() const {
    return pressed;
}

void BasicUi::setPressed(bool pressed) {
    BasicUi::pressed = pressed;
}
