#include "QAddElevator.h"

QAddElevator::QAddElevator(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddElevator) {
    popup->getPopupTitle().setString("Elevator");
}
