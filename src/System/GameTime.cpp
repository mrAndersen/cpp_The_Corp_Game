#include "../../includes/Utls/GameTime.h"
#include "../../includes/System/System.h"

GameTime operator+(const GameTime &a, const GameTime &b) {
    auto c_hour = a.hour + b.hour;
    auto c_minute = a.minute + b.minute;

    if (c_minute >= 60) {
        c_minute = c_minute - 60;
        c_hour++;
    }

    if (c_hour >= 24) {
        c_hour = c_hour - 24;
    }

    return {c_hour, c_minute};
}

std::string GameTime::get() {
    return (hour < 10 ? ("0" + std::to_string(hour)) : std::to_string(hour)) +
           ":" +
           (minute < 10 ? ("0" + std::to_string(minute)) : std::to_string(minute));
}

GameTime::GameTime(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
}

GameTime operator+(const GameTime &a, int minutes) {
    GameTime b(0, minutes);

    return a + b;
}

bool GameTime::isWorkTime() {
    return hour >= System::startWorkHour && hour < System::endWorkHour;
}

bool GameTime::isEarningHour() {
    return hour >= System::startWorkHour + 1 && hour <= System::endWorkHour && minute == 0;
}

bool GameTime::isDayEndHour() {
    return hour == System::endWorkHour && minute == 0;
}

bool GameTime::isDayStartHour() {
    return hour == System::startWorkHour && minute == 0;
}

GameTime::GameTime() {
    this->hour = 12;
    this->minute = 0;
}

int GameTime::diffMinutes(const GameTime &target) {
    int m = this->hour * 60 + this->minute;
    int m2 = target.hour * 60 + target.minute;

    return abs(m - m2);
}

int GameTime::getHour() const {
    return hour;
}

int GameTime::getMinute() const {
    return minute;
}
