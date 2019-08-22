#ifndef THE_CORP_GAME_QUESTION_H
#define THE_CORP_GAME_QUESTION_H

#include "../../Ui/BasicUi.h"
#include "../../System/ResourceLoader.h"
#include "../../System/EntityContainer.h"
#include "../../System/System.h"
#include "../../System/ControlPanel.h"

class Question : public BasicUi {
public:
    const static int width = 26;
    const static int height = 62;

    sf::Text helpText;
    std::string helpTextString = "my-text";

    sf::Text titleText;
    std::string titleTextString = "my-title";

    Popup *popup = nullptr;

    Question(float leftOffset, float topOffset, Entities type);

    void update() override;
};

#endif //THE_CORP_GAME_QUESTION_H