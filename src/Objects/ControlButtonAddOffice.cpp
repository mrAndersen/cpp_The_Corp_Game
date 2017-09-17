#include <climits>
#include "../../includes/Objects/ControlButtonAddOffice.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/System/System.h"

ControlButtonAddOffice::ControlButtonAddOffice() {
    setName("button.add.office");
    setDrawOrder(INT_MAX);

    setWorldCoordinates(sf::Vector2f(ViewHandler::left + 600, ViewHandler::top - 50));

    setWidth(142);
    setHeight(47);

    setTotalFrames(1);
    setTexture(ResourceLoader::getTexture(Entities::E_ButtonAddOffice));
    createAnimationFrames();

    EntityContainer::add(this);
}

void ControlButtonAddOffice::updateLogic() {
    if (leftClicked() && !attachedOffice) {
        attachedOffice = new OfficeClerk(sf::Vector2f(System::g_x, System::g_y));
        attachedOffice->setTransparent();
    }

    if (rightClickedOutside() && attachedOffice) {
        EntityContainer::remove(attachedOffice);
        attachedOffice = nullptr;
    }

    if (leftClickedOutside() && attachedOffice) {
        attachedOffice->removeTransparency();
        attachedOffice = nullptr;
    }

    if (attachedOffice) {
        auto global = System::getGlobalMouse();

        int moduloX = (int) global.x % System::gridSize;
        int moduloY = (int) global.y % System::gridSize;

        if (moduloX != 0) {
            attachedOffice->setWorldCoordinates(sf::Vector2f(
                    global.x + moduloX,
                    global.y
            ));
        }

        if (moduloY != 0) {
            attachedOffice->setWorldCoordinates(sf::Vector2f(
                    global.x,
                    global.y + moduloY
            ));
        }

    }
}
