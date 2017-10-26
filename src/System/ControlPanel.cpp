#include <climits>
#include <Basic/Entity.h>
#include <Ui/ControlButtonAddClerk.h>
#include <Ui/ControlButtonAddOffice.h>
#include <Ui/MoneyIndicator.h>
#include <Ui/Question.h>
#include "ControlPanel.h"

namespace ControlPanel {
    std::vector<Entity *> controls;

    void initControlPanel() {
        controls.push_back(new MoneyIndicator({0, 0}));

        controls.push_back(new Question(4 + Question::width / 2, 300));
        controls.push_back(new ControlButtonAddClerk(4 + ControlButtonAddClerk::width / 2 + Question::width + 2, 300));

        controls.push_back(new Question(4 + Question::width / 2, 362));
        controls.push_back(new ControlButtonAddOffice(4 + ControlButtonAddOffice::width / 2 + Question::width + 2, 362));
    }

    void refreshControlPanel() {
        for (auto c:controls) {
            c->update();
        }
    }
}


