#include "QAddManager.h"

QAddManager::QAddManager(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddManager) {
    popup->getPopupTitle().setString(ResourceLoader::getTranslation("units.titles.manager"));
    popup->getPopupText().setString(ResourceLoader::getTranslation("units.descriptions.manager"));
}
