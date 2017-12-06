#include "..\..\System\System.h"
#include "MainPanelOverlay.h"

MainPanelOverlay::MainPanelOverlay(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_MainPanelOverlay);
    setDrawOrder(D_Ui);

    setWidth(MainPanelOverlay::width);
    setHeight(MainPanelOverlay::height);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));

    time.setCharacterSize(40);
    time.setFont(*System::titleFont);
    time.setFillColor(sf::Color::White);


    stats[E_Clerk] = Entity::create(E_Entity, D_Ui_Over, {30, 30}, {0, 0}, "resources/ui/stats/clerk.png", 0.7f);
    stats[E_Manager] = Entity::create(E_Entity, D_Ui_Over, {30, 30}, {0, 0}, "resources/ui/stats/manager.png", 0.7f);
    stats[E_Accountant] = Entity::create(E_Entity, D_Ui_Over, {30, 30}, {0, 0}, "resources/ui/stats/accountant.png", 0.7f);
    stats[E_Stats_Daily_Income] = Entity::create(E_Entity, D_Ui_Over, {30, 30}, {0, 0}, "resources/ui/stats/income.png", 0.7f);
    stats[E_Stats_Daily_Loss] = Entity::create(E_Entity, D_Ui_Over, {30, 30}, {0, 0}, "resources/ui/stats/loss.png", 0.7f);

    for (auto &s:{E_Clerk, E_Manager, E_Accountant, E_Stats_Daily_Income, E_Stats_Daily_Loss}) {
        sf::Text label;

        label.setFont(*System::titleFont);
        label.setFillColor(sf::Color::White);
        label.setCharacterSize(20);

        statLabels[s] = label;
    }

    initEntity();
    EntityContainer::add(this);
}

void MainPanelOverlay::update() {
    BasicUi::update();

    worldCoordinates.x = ViewHandler::right - width / 2;
    worldCoordinates.y = ViewHandler::top - height / 2;

    time.setString(System::gameTime.get());
    time.setPosition(System::cToGl(ViewHandler::right - 133, ViewHandler::top - topOffset + 32));

    int i = 0;
    for (auto &s:{E_Clerk, E_Manager, E_Accountant, E_Stats_Daily_Income, E_Stats_Daily_Loss}) {

        if(s == E_Stats_Daily_Income || s == E_Stats_Daily_Loss){
            stats[s]->setWorldCoordinates({ViewHandler::right - width + 35 + (i * 80), ViewHandler::top - 26});
        }else{
            stats[s]->setWorldCoordinates({ViewHandler::right - width + 35 + (i * 60), ViewHandler::top - 26});
        }

        statLabels[s].setString(std::to_string(EntityContainer::counters[s]));
        statLabels[s].setPosition(System::cToGl({ViewHandler::right - width + (i * 60) + 54, ViewHandler::top - 13}));

        i++;
        System::window->draw(statLabels[s]);
    }

    System::window->draw(time);
}