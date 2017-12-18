#include "QAddOffice.h"

QAddOffice::QAddOffice(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddOffice) {
    popup->getPopupTitle().setString(ResourceLoader::getTranslation("units.titles.office"));
    popup->getPopupText().setString(ResourceLoader::getTranslation("units.descriptions.office"));
}
