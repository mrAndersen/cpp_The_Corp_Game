#include <iostream>
#include "System/ResourceLoader.h"
#include "Clerk.h"
#include "System/System.h"

Clerk::Clerk(sf::Vector2f coordinates) : Movable(E_Clerk, Clerk::width, Clerk::height) {
    setDefaultSpeed(150);

    setCost(500);
    setWorldCoordinates(coordinates);
    setSelectable(true);

    setDrawOrder(D_Characters);
    initEntity();

    System::salaryTotal += dailySalary;
    EntityContainer::add(this);
}

void Clerk::updateLogic() {

    if (state == S_Working) {
        sf::Text hourEarningHint;

        hourEarningHint.setCharacterSize(30);
        hourEarningHint.setFillColor(System::c_green);
        hourEarningHint.setFont(*System::gameFont);
        hourEarningHint.setString("+" + System::f_to_string(hourEarning) + "$");

        //earning every hour
        if (System::gameTime.isEarningHour() && !earningProcessed) {
            System::cash = System::cash + hourEarning;

            auto *earningHint = new TextEntity(System::c_green, 25);
            auto position = worldCoordinates;
            position.y += height / 2;

            earningHint->setSpeed(100 * System::timeFactor);
            earningHint->setLiveTimeSeconds(2 / System::timeFactor);
            earningHint->setWorldCoordinates(position);
            earningHint->setString("+" + System::f_to_string(hourEarning) + "$");

            earningProcessed = true;
        }


        //reset earning processing
        if (System::gameTime.getMinute() == 1) {
            earningProcessed = false;
        }

        //salary every day
        if (System::gameTime.getHour() == System::endWorkHour && System::gameTime.getMinute() == 0 &&
            !salaryProcessed) {
            System::cash = System::cash - dailySalary;
            salaryProcessed = true;
        }

        //reset salary processing
        if (System::gameTime.getHour() == 0 && System::gameTime.getMinute() == 0) {
            salaryProcessed = false;
        }
    }

    Movable::updateLogic();
}