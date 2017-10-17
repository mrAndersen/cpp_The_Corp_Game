#include <climits>
#include <Controls/ControlButtonAddElevatorCabin.h>
#include "ControlPanel.h"
#include "ViewHandler.h"
#include "Controls/ControlButtonAddClerk.h"
#include "Controls/ControlButtonAddOffice.h"
#include "Text/TextEntity.h"
#include "Controls/ControlCashIndicator.h"
#include "Controls/ControlTimeIndicator.h"
#include "Controls/ControlButtonAddElevatorShaftMiddle.h"
#include "Controls/ControlButtonAddElevatorShaftTop.h"

namespace ControlPanel {
    std::map<std::string, Entity *> controls;

    void initControlPanel() {
        auto *b_add_clerk = new ControlButtonAddClerk();
        auto *b_add_office = new ControlButtonAddOffice();

        auto *b_add_elevator_middle = new ControlButtonAddElevatorShaftMiddle();
        auto *b_add_elevator_top = new ControlButtonAddElevatorShaftTop();
        auto *b_add_elevator_cabin = new ControlButtonAddElevatorCabin();

        auto *c_cash_indicator = new ControlCashIndicator(sf::Color::Black, 50);
        auto *c_time_indicator = new ControlTimeIndicator(sf::Color::Black, 20);


        controls[b_add_clerk->getName()] = b_add_clerk;
        controls[b_add_office->getName()] = b_add_office;

        controls[b_add_elevator_middle->getName()] = b_add_elevator_middle;
        controls[b_add_elevator_top->getName()] = b_add_elevator_top;
        controls[b_add_elevator_cabin->getName()] = b_add_elevator_cabin;

        controls[c_cash_indicator->getName()] = c_cash_indicator;
        controls[c_time_indicator->getName()] = c_time_indicator;
    }

    void refreshControlPanel() {
        int i = 0;
        for (auto control : controls) {
            control.second->setWorldCoordinates(
                    sf::Vector2f(
                            ViewHandler::left + 600 + i * control.second->getWidth() + i * 20,
                            ViewHandler::top - 50)
            );
            control.second->update();
            i++;
        }
    }
}


