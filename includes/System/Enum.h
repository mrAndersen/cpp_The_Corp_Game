#ifndef CORP_GAME_ENUM
#define CORP_GAME_ENUM

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

enum Entities {
    //Ground
            StaticGround = 11,

    //Clerks
            MovableClerk = 21,
};

#endif