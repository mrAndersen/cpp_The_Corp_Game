#include <System/Enum.h>
#include "QAddAccountant.h"
#include "Question.h"

QAddAccountant::QAddAccountant(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddAccountant) {
    popup->setPopupTitleString("Accountant");
}
