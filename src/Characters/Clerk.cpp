#include <math.h>
#include <iostream>
#include "../../includes/Animation/Movable.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/Characters/Clerk.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Objects/Ground.h"
#include "../../includes/System/System.h"

Clerk::Clerk(sf::Vector2f coordinates) {
    setName("clerk");

    setWidth(Clerk::width);
    setHeight(Clerk::height);
    setTotalFrames(24);
    setDefaultSpeed(300);
    setCost(500);

    setWorldCoordinates(coordinates);

    setTexture(ResourceLoader::getTexture(Entities::E_Clerk));
    setDrawOrder(100);
    createAnimationFrames();

    EntityContainer::add(this);
}

void Clerk::updateLogic() {

    if (state == S_Working) {
        sf::Text hourEarningHint;

        hourEarningHint.setCharacterSize(30);
        hourEarningHint.setFillColor(System::c_green);
        hourEarningHint.setFont(*System::gameFont);
        hourEarningHint.setString("+" + System::to_string_with_precision(hourEarning) + "$");

        //earning every hour
        if (System::gameTime.getMinute() == 0 && !earningProcessed) {
            System::cash = System::cash + hourEarning;
            earningProcessed = true;
        }

        //earning hint
        if (System::gameTime.getMinute() <= 35 && System::gameTime.getMinute() >= 0) {
            if (hourEarningHintClock.getElapsedTime().asMilliseconds() * System::timeFactor >= 1000) {
                auto position = System::cFromGl(hourEarningHint.getPosition());
                position.x = worldCoordinates.x + width / 4;
                position.y = worldCoordinates.y + height / 2 + 24 + System::gameTime.getMinute() * 2;


                hourEarningHint.setPosition(System::cToGl(position));
                System::window->draw(hourEarningHint);
            }
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