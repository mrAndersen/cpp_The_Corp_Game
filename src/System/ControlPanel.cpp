#include <climits>
#include "../../includes/System/ControlPanel.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/Objects/ControlButtonAddClerk.h"
#include "../../includes/Objects/ControlButtonAddOffice.h"

namespace ControlPanel {
    std::map<std::string, Entity *> controls;

    void initControlPanel() {
        auto *b_add_clerk = new ControlButtonAddClerk();
        auto *b_add_office = new ControlButtonAddOffice();


        controls[b_add_clerk->getName()] = b_add_clerk;
        controls[b_add_office->getName()] = b_add_office;
    }

    void refreshControlPanel() {
        int i = 0;
        for (auto control : controls) {
            control.second->setWorldCoordinates(
                    sf::Vector2f(ViewHandler::left + 600 + i * control.second->getWidth() + i * 20, ViewHandler::top - 50));
            i++;
        }
    }
}


