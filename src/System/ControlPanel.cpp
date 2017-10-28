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
#include <Ui/MainPanel/MainPanelOverlay.h>
#include <Ui/MainPanel/ButtonPause.h>
#include <Ui/MainPanel/Button1x.h>
#include <Ui/MainPanel/Button5x.h>
#include <Ui/MainPanel/Button10x.h>
#include "ControlPanel.h"

namespace ControlPanel {
    std::map<Entities , Entity *> controls;

    void initControlPanel() {
        controls[E_Indicator_Money] = new MoneyIndicator(MoneyIndicator::width / 2, MoneyIndicator::height / 2);
        controls[E_MainPanelOverlay] = new MainPanelOverlay({(float) System::screenWidth - MainPanelOverlay::width / 2, MainPanelOverlay::height / 2});

        controls[E_ButtonPause] = new ButtonPause({(float) System::screenWidth - 345, 26});
        controls[E_Button1x] = new Button1x({(float) System::screenWidth - 293, 26});
        controls[E_Button5x] = new Button5x({(float) System::screenWidth - 241, 26});
        controls[E_Button10x] = new Button10x({(float) System::screenWidth - 189, 26});

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


