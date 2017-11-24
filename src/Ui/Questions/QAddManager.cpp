#include "QAddManager.h"

QAddManager::QAddManager(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddManager) {
    popup->setPopupTextString("Manager");
}
