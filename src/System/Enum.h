#ifndef ENUM_H
#define ENUM_H

enum Direction {
    None,
    Right,
    Left,
    Up,
    Down,

    UpRight,
    UpLeft,
    DownRight,
    DownLeft
};

enum Objects {
    //Clerks
    CharacterClerk = 21,
    CharacterSeniorClerk = 22,
    CharacterLeadClerk = 23,
    CharacterVicePresident = 24,
    CharacterPresident = 25
};

#endif