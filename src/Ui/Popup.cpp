#include "..\System\ViewHandler.h"
#include "..\System\System.h"
#include "..\System\ResourceLoader.h"
#include "..\System\EntityContainer.h"
#include "Popup.h"

Popup::Popup(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_Popup);
    setDrawOrder(D_Ui);
    setVisible(false);
    setManualUpdate(true);

    setWidth(Popup::width);
    setHeight(Popup::height);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));
    initEntity();

    EntityContainer::add(this);
}

void Popup::update() {
    BasicUi::update();
}
