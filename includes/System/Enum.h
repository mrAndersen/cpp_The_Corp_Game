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
    E_Entity = 0,
    //Ground
    E_StaticGround = 11,

    //Clerks
    E_MovableClerk = 21,

    //Controls
    E_ButtonAddClerk = 31,
    E_ButtonAddOffice = 32,

    //Office
    E_OfficeClerk = 41,
};

#endif