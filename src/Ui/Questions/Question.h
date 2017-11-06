#ifndef THE_CORP_GAME_QUESTION_H
#define THE_CORP_GAME_QUESTION_H

#include "..\..\Ui\BasicUi.h"
#include "..\..\System\ResourceLoader.h"
#include "..\..\System\EntityContainer.h"
#include "..\..\System\System.h"
#include "..\..\System\ControlPanel.h"

class Question : public BasicUi {
public:
    const static int width = 26;
    const static int height = 62;

    sf::Text helpText;
    std::string helpTextString = "This is your warhorse, main unit - clerk. He works from 9:00 AM to 6:00 PM. Daily salary is 80$";
    sf::Vertex popup[4];

    Question(float leftOffset, float topOffset, Entities type);

    void update() override;
};

#endif //THE_CORP_GAME_QUESTION_H