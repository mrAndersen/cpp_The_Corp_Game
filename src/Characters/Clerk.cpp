#include <cmath>
#include <iostream>
#include "System/ResourceLoader.h"
#include "Clerk.h"
#include "System/EntityContainer.h"
#include "System/System.h"
#include "Text/TextEntity.h"

Clerk::Clerk(sf::Vector2f coordinates) : Movable() {
    setName("clerk");
    setWidth(Clerk::width);
    setHeight(Clerk::height);

    addAnimation(S_None, Animation(this, S_None, 24, ResourceLoader::getTexture(E_Clerk, S_None)));

    addAnimation(S_GoToOffice, Animation(this, S_GoToOffice, 24, ResourceLoader::getTexture(E_Clerk, S_GoToOffice)));
    addAnimation(S_GoToElevator, Animation(this, S_GoToElevator, 24, ResourceLoader::getTexture(E_Clerk, S_GoToElevator)));
    addAnimation(S_GoToCabin, Animation(this, S_GoToCabin, 24, ResourceLoader::getTexture(E_Clerk, S_GoToCabin)));

    addAnimation(S_Working, Animation(this, S_Working, 24, ResourceLoader::getTexture(E_Clerk, S_Working)));

    setDefaultSpeed(130);

    setCost(500);
    setWorldCoordinates(coordinates);
    setSelectable(true);


    setDrawOrder(1000);
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