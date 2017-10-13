#include <cmath>
#include <iostream>
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"
#include "../../includes/Text/TextEntity.h"

Clerk::Clerk(sf::Vector2f coordinates) {
    setName("clerk");

    setWidth(Clerk::width);
    setHeight(Clerk::height);
    setTotalFrames(24);
    setDefaultSpeed(130);
    setCost(500);

    setWorldCoordinates(coordinates);

    setTexture(ResourceLoader::getTexture(Entities::E_Clerk));
    setDrawOrder(100);
    createAnimationFrames();

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
        if (System::gameTime.getHour() == System::endWorkHour && System::gameTime.getMinute() == 0 && !salaryProcessed) {
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