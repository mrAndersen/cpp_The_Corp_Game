#include "BasicUi.h"

BasicUi::BasicUi(float leftOffset, float topOffset) {
    this->leftOffset = leftOffset;
    this->topOffset = topOffset;

    selectable = false;
}

void BasicUi::update() {
    recalculateBoundaries();

    if (fixed) {
        worldCoordinates.x = ViewHandler::left + leftOffset;
        worldCoordinates.y = ViewHandler::top - topOffset;
    }

    if (currentAnimation && visible) {
        selectAnimation(state);
        currentAnimation->update();
    }
}

bool BasicUi::isPressed() const {
    return pressed;
}

void BasicUi::setPressed(bool pressed) {
    BasicUi::pressed = pressed;
}

float BasicUi::getLeftOffset() const {
    return leftOffset;
}

void BasicUi::setLeftOffset(float leftOffset) {
    BasicUi::leftOffset = leftOffset;
}

float BasicUi::getTopOffset() const {
    return topOffset;
}

void BasicUi::setTopOffset(float topOffset) {
    BasicUi::topOffset = topOffset;
}

bool BasicUi::isFixed() const {
    return fixed;
}

void BasicUi::setFixed(bool fixed) {
    BasicUi::fixed = fixed;
}
