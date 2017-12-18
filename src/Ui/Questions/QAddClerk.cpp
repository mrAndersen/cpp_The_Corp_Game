#include "QAddClerk.h"

QAddClerk::QAddClerk(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddClerk) {
    popup->getPopupTitle().setString(ResourceLoader::getTranslation("units.titles.clerk"));
    popup->getPopupText().setString(ResourceLoader::getTranslation("units.descriptions.clerk"));
}
