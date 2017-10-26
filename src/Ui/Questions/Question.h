#ifndef THE_CORP_GAME_QUESTION_H
#define THE_CORP_GAME_QUESTION_H

#include <System/ResourceLoader.h>
#include <System/EntityContainer.h>
#include <System/ViewHandler.h>
#include <Basic/Entity.h>
#include "Ui/BasicUi.h"

class Question : public BasicUi {
public:
    const static int width = 26;
    const static int height = 62;

    Question(float leftOffset, float topOffset, Entities type);

    void update() override;
};

#endif //THE_CORP_GAME_QUESTION_H