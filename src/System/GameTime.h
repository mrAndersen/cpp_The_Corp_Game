#ifndef THE_CORP_GAME_GAMETIME_H
#define THE_CORP_GAME_GAMETIME_H

#include <string>

class GameTime {
protected:

    int hour = 12;
    int minute = 0;

public:
    std::string get();

    int getHour() const;

    int getMinute() const;

    bool isWorkTime();

    bool isRestTime();

    bool isEarningHour();

    bool isDayEndHour();

    bool isDayStartHour();

    bool isHourStart();

    int diffMinutes(const GameTime &target);

    friend GameTime operator+(const GameTime &a, const GameTime &b);

    friend GameTime operator+(const GameTime &a, int minutes);

    friend bool operator==(const GameTime &a, const GameTime &b);

    GameTime(int hour, int minute);

    GameTime();
};

#endif //THE_CORP_GAME_GAMETIME_H
