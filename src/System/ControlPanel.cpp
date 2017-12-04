#include <climits>
#include <Ui/MainPanel/Cog.h>
#include "..\Ui\ControlButtonAddAccountant.h"
#include "..\Basic\Entity.h"
#include "..\Ui\ControlButtonAddClerk.h"
#include "..\Ui\ControlButtonAddOffice.h"
#include "..\Ui\MoneyIndicator.h"
#include "..\Ui\Questions/Question.h"
#include "..\Ui\ControlButtonAddElevator.h"
#include "..\Ui\ControlButtonAddElevatorCabin.h"
#include "..\Ui\Questions/QAddClerk.h"
#include "..\Ui\Questions/QAddOffice.h"
#include "..\Ui\Questions/QAddElevator.h"
#include "..\Ui\MainPanel/MainPanelOverlay.h"
#include "..\Ui\MainPanel/ButtonPause.h"
#include "..\Ui\MainPanel/Button1x.h"
#include "..\Ui\MainPanel/Button5x.h"
#include "..\Ui\MainPanel/Button10x.h"
#include "..\Ui\ControlButtonAddElevatorShaftMiddle.h"
#include "..\Ui\ControlButtonAddElevatorShaftTop.h"
#include "..\Ui\ControlButtonAddManager.h"
#include "..\Ui\Questions/QAddManager.h"
#include "..\Ui\Questions/QAddAccountant.h"
#include "ControlPanel.h"
#include "mingw.thread.h"

namespace ControlPanel {
    std::map<Entities , Entity *> controls;
    std::map<std::string , Entity *> mainMenu;

    void initMainMenu() {
        auto screenCenterX = System::screenWidth / 2;
        auto screenCenterY = System::screenHeight / 2;

        auto resume = new PopupButton;
        resume->setTextOffset(3);
        resume->setColor(System::c_blue);
        resume->getText().setFont(*System::titleFontI8N);
        resume->getText().setCharacterSize(20);
        resume->setLeftOffset(screenCenterX);
        resume->setTopOffset(screenCenterY - 14);
        resume->setString("Resume");
        resume->setVisible(false);
        resume->callback = []() {
            System::changeScene(SC_Game);
        };

        auto start = new PopupButton;
        start->setTextOffset(3);
        start->setColor(System::c_green);
        start->getText().setFont(*System::titleFontI8N);
        start->getText().setCharacterSize(20);
        start->setLeftOffset(screenCenterX);
        start->setTopOffset(screenCenterY + 18);
        start->setString("Start");
        start->callback = []() {
            if(System::loadingScene == SC_Main_Menu){
                mainMenu.clear();

                std::thread loader([](){
                    System::loadingScene = SC_Game;

                    ResourceLoader::loadGameTextures();
                    ResourceLoader::loadNames();

                    EntityContainer::initBackground();
                    ControlPanel::initControlPanel();

                    System::changeScene(SC_Game);
                });

                loader.detach();
            }
        };

        auto quit = new PopupButton;
        quit->setTextOffset(2);
        quit->setColor(System::c_red);
        quit->getText().setFont(*System::titleFontI8N);
        quit->getText().setCharacterSize(20);
        quit->setLeftOffset(screenCenterX);
        quit->setTopOffset(screenCenterY + 50);
        quit->setString("Quit");
        quit->callback = []() {
            System::window->close();
        };

        mainMenu["resume"] = resume;
        mainMenu["start"] = start;
        mainMenu["quit"] = quit;
    }

    void initControlPanel() {
        controls[E_Indicator_Money] = new MoneyIndicator(MoneyIndicator::width / 2, MoneyIndicator::height / 2);
        controls[E_MainPanelOverlay] = new MainPanelOverlay((float) System::screenWidth - MainPanelOverlay::width / 2, MainPanelOverlay::height / 2);

		controls[E_ButtonPause] = new ButtonPause((float)System::screenWidth - 345, 26);
        controls[E_Button1x] = new Button1x((float) System::screenWidth - 293, 26);
        controls[E_Button5x] = new Button5x((float) System::screenWidth - 241, 26);
        controls[E_Button10x] = new Button10x((float) System::screenWidth - 189, 26);
        controls[E_Cog] = new Cog((float) System::screenWidth - 25, 26);

        controls[E_Question_Mark_ButtonAddClerk] = new QAddClerk(4 + Question::width / 2, 300);
        controls[E_ButtonAddClerk] = new ControlButtonAddClerk(4 + ControlButtonAddClerk::width / 2 + Question::width + 2, 300);

        controls[E_Question_Mark_ButtonAddManager] = new QAddManager(4 + Question::width / 2, 362);
        controls[E_ButtonAddManager] = new ControlButtonAddManager(4 + ControlButtonAddManager::width / 2 + Question::width + 2, 362);

        controls[E_Question_Mark_ButtonAddAccountant] = new QAddAccountant(4 + Question::width / 2, 424);
        controls[E_ButtonAddAccountant] = new ControlButtonAddAccountant(4 + ControlButtonAddManager::width / 2 + Question::width + 2, 424);

        controls[E_Question_Mark_ButtonAddOffice] = new QAddOffice(4 + Question::width / 2, 486);
        controls[E_ButtonAddOffice] = new ControlButtonAddOffice(4 + ControlButtonAddOffice::width / 2 + Question::width + 2, 486);

        controls[E_Question_Mark_ButtonAddElevator] = new QAddElevator(4 + Question::width / 2, 548);

        controls[E_ButtonAddElevatorCabin] = new ControlButtonAddElevatorCabin(162, 548);
        controls[E_ButtonAddElevatorShaftMiddle] = new ControlButtonAddElevatorShaftMiddle(224, 548);
        controls[E_ButtonAddElevatorShaftTop] = new ControlButtonAddElevatorShaftTop(286, 548);

        controls[E_ButtonAddElevator] = new ControlButtonAddElevator(4 + ControlButtonAddElevator::width / 2 + Question::width + 2, 548);
    }


}


