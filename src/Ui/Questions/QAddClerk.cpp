#include "QAddClerk.h"

QAddClerk::QAddClerk(float leftOffset, float topOffset) : Question(leftOffset, topOffset, E_Question_Mark_ButtonAddClerk) {
    popup->setPopupTitleString("Clerk");

    std::string s;
    s = System::formatNewLines("Your main unit - clerk. Warhorse of your company, works as all your employees from 10:00 AM till 9:00 PM. Has four levels of skill: \n", 40);
    s = s + "\t- 1. Yields 10$ per hour\n\t\t  Basic cost is 500$\n";
    s = s + "\t- 2. Yields 15$ per hour\n\t\t  Upgrades for additional 250$\n";
    s = s + "\t- 3. Yields 20$ per hour\n\t\t  Upgrades for additional 350$\n";
    s = s + "\t- 4. Yields 25$ per hour\n";

    popup->setPopupTextString(s);
}
