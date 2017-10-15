#include <climits>
#include "../../includes/System/ControlPanel.h"
#include "../../includes/System/ViewHandler.h"
#include "../../includes/Controls/ControlButtonAddClerk.h"
#include "../../includes/Controls/ControlButtonAddOffice.h"
#include "../../includes/Text/TextEntity.h"
#include "../../includes/Controls/ControlCashIndicator.h"
#include "../../includes/Controls/ControlTimeIndicator.h"

namespace ControlPanel {
    std::map<std::string, Entity *> controls;

    void initControlPanel() {
        auto *b_add_clerk = new ControlButtonAddClerk();
        auto *b_add_office = new ControlButtonAddOffice();

        auto *c_cash_indicator = new ControlCashIndicator(sf::Color::Black, 50);
        auto *c_time_indicator = new ControlTimeIndicator(sf::Color::Black, 20);


        controls[b_add_clerk->getName()] = b_add_clerk;
        controls[b_add_office->getName()] = b_add_office;
        controls[c_cash_indicator->getName()] = c_cash_indicator;
        controls[c_time_indicator->getName()] = c_time_indicator;
    }

    void refreshControlPanel() {
        int i = 0;
        for (auto control : controls) {
            control.second->setWorldCoordinates(
                    sf::Vector2f(ViewHandler::left + 600 + i * control.second->getWidth() + i * 20,
                                 ViewHandler::top - 50));
            control.second->update();
            i++;
        }
    }
}


