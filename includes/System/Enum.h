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

enum States {
    S_None = 0,
    S_Stand = 1,
    S_Run = 2,
    S_Walk = 3,
    S_Smoke = 4,
    S_WaitForElevator = 5,
    S_RideInElevator = 6,
    S_Working = 7,
    S_Falling = 8,
    S_GoToOffice = 9,
    S_GoHome = 10,
    S_GoSmoke = 11,
    S_GoToElevator = 12
};

enum Entities {
    E_Entity = 0,
    //Ground
    E_StaticGround = 11,

    //Characters
    E_Clerk = 21,

    //Controls
    E_ButtonAddClerk = 31,
    E_ButtonAddOffice = 32,

    //Office
    E_OfficeClerk = 41,
};

#endif