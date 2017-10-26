#include <climits>
#include <Basic/Entity.h>
#include <Ui/ControlButtonAddClerk.h>
#include <Ui/ControlButtonAddOffice.h>
#include <Ui/MoneyIndicator.h>
#include <Ui/Questions/Question.h>
#include <Ui/ControlButtonAddElevator.h>
#include <Ui/ControlButtonAddElevatorCabin.h>
#include <Ui/Questions/QAddClerk.h>
#include <Ui/Questions/QAddOffice.h>
#include <Ui/Questions/QAddElevator.h>
#include "ControlPanel.h"

namespace ControlPanel {
    std::map<Entities , Entity *> controls;

    void initControlPanel() {
        controls[E_Indicator_Money] = new MoneyIndicator({0, 0});

        controls[E_Question_Mark_ButtonAddClerk] = new QAddClerk(4 + Question::width / 2, 300);
        controls[E_ButtonAddClerk] = new ControlButtonAddClerk(4 + ControlButtonAddClerk::width / 2 + Question::width + 2, 300);

        controls[E_Question_Mark_ButtonAddOffice] = new QAddOffice(4 + Question::width / 2, 362);
        controls[E_ButtonAddOffice] = new ControlButtonAddOffice(4 + ControlButtonAddOffice::width / 2 + Question::width + 2, 362);

        controls[E_Question_Mark_ButtonAddElevator] = new QAddElevator(4 + Question::width / 2, 424);
        controls[E_ButtonAddElevatorCabin] = new ControlButtonAddElevatorCabin(4 + Question::width + 2 + ControlButtonAddElevator::width +  ControlButtonAddElevatorCabin::width / 2 + 10, 424);

        controls[E_ButtonAddElevator] = new ControlButtonAddElevator(4 + ControlButtonAddElevator::width / 2 + Question::width + 2, 424);
    }

    void refreshControlPanel() {
        for (auto c:controls) {
            c.second->update();
        }
    }

    std::map<Entities, Entity *> getControls() {
        return controls;
    }
}


