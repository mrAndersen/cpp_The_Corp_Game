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
    time.setPosition(System::cToGl(ViewHandler::right - 138, ViewHandler::top - topOffset + 32));

    int i = 0;
    for (auto &s:{E_Clerk, E_Manager, E_Accountant}) {
        stats[s]->setWorldCoordinates({ViewHandler::right - width + 35 + (i * 60), ViewHandler::top - 26});

        statLabels[s].setPosition(System::cToGl({ViewHandler::right - width + (i * 60) + 52, ViewHandler::top - 13}));
        statLabels[s].setString(std::to_string(EntityContainer::counters[s]));
        i++;
        System::window->draw(statLabels[s]);
    }

    stats[E_Stats_Daily_Income]->setWorldCoordinates({ViewHandler::right - width + 215, ViewHandler::top - 26});
    statLabels[E_Stats_Daily_Income].setPosition(System::cToGl({ViewHandler::right - width + 232, ViewHandler::top - 13}));
    statLabels[E_Stats_Daily_Income].setString("$" + System::f_to_string(EntityContainer::counters[E_Stats_Daily_Income], 0));
    System::window->draw(statLabels[E_Stats_Daily_Income]);

    stats[E_Stats_Daily_Loss]->setWorldCoordinates({ViewHandler::right - width + 315, ViewHandler::top - 26});
    statLabels[E_Stats_Daily_Loss].setPosition(System::cToGl({ViewHandler::right - width + 332, ViewHandler::top - 13}));
    statLabels[E_Stats_Daily_Loss].setString("$" + System::f_to_string(EntityContainer::counters[E_Stats_Daily_Loss], 0));
    System::window->draw(statLabels[E_Stats_Daily_Loss]);


    System::window->draw(time);
}
