#include <climits>
#include <Basic/Entity.h>
#include <Ui/ControlButtonAddClerk.h>
#include <Ui/ControlButtonAddElevatorShaftMiddle.h>
#include <Ui/ControlButtonAddElevatorShaftTop.h>
#include <Ui/ControlButtonAddOffice.h>
#include <Ui/ControlButtonAddElevatorCabin.h>
#include <Ui/MoneyIndicator.h>
#include "ControlPanel.h"
#include "ViewHandler.h"

namespace ControlPanel {
    std::map<std::string, Entity *> controls;

    void initControlPanel() {
        auto *b_add_clerk = new ControlButtonAddClerk();
        auto *b_add_office = new ControlButtonAddOffice();

        auto *b_add_elevator_middle = new ControlButtonAddElevatorShaftMiddle();
        auto *b_add_elevator_top = new ControlButtonAddElevatorShaftTop();
        auto *b_add_elevator_cabin = new ControlButtonAddElevatorCabin();

        auto *c_cash_indicator = new MoneyIndicator({0,0});
//        auto *c_time_indicator = new ControlTimeIndicator(sf::Color::Black, 20);


        controls[b_add_clerk->getName()] = b_add_clerk;
        controls[b_add_office->getName()] = b_add_office;

        controls[b_add_elevator_middle->getName()] = b_add_elevator_middle;
        controls[b_add_elevator_top->getName()] = b_add_elevator_top;
        controls[b_add_elevator_cabin->getName()] = b_add_elevator_cabin;

        controls[c_cash_indicator->getName()] = c_cash_indicator;
//        controls[c_time_indicator->getName()] = c_time_indicator;
    }

    void refreshControlPanel() {
        for (auto control : controls) {
            control.second->update();
        }
    }
}


