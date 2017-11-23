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
    std::string helpTextString = "my-text";

    sf::Text titleText;
    std::string titleTextString = "my-title";

    Entity *popup = nullptr;

    Question(float leftOffset, float topOffset, Entities type);

    void update() override;

    const std::string &getHelpTextString() const;

    void setHelpTextString(const std::string &helpTextString);

    const std::string &getTitleTextString() const;

    void setTitleTextString(const std::string &titleTextString);
};

#endif //THE_CORP_GAME_QUESTION_H