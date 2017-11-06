#include "..\..\System\System.h"
#include "MainPanelOverlay.h"

MainPanelOverlay::MainPanelOverlay(float leftOffset, float topOffset) : BasicUi(leftOffset, topOffset) {
    setEType(E_MainPanelOverlay);
    setDrawOrder(D_Ui);

    setWidth(MainPanelOverlay::width);
    setHeight(MainPanelOverlay::height);

    addAnimation(S_None, Animation(this, S_None, 1, ResourceLoader::getTexture(eType)));


    time.setCharacterSize(40);
    time.setFont(*System::gameFont);
    time.setFillColor(sf::Color::White);

    initEntity();
    EntityContainer::add(this);
}

void MainPanelOverlay::update() {
    BasicUi::update();

    time.setString(System::gameTime.get());
    time.setPosition(System::cToGl(ViewHandler::left + leftOffset + 58, ViewHandler::top - topOffset + 32));

    System::window->draw(time);
}