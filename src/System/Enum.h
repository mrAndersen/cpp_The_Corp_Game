#ifndef CORP_GAME_ENUM
#define CORP_GAME_ENUM

enum DrawOrder {
    D_Ground = 20,
    D_Trees = 20,

    D_GroundArtifacts = 21,



    D_Offices = 98,
    D_Characters_Wokring = 100,
    D_Chair = 105,
    D_ElevatorShafts = 110,
    D_ElevatorCabin = 120,
    D_Characters = 200,

    D_Ui = 250
};

enum Gender {
    G_Male = 1,
    G_Female = 2
};

enum Race {
    R_White = 1,
    R_Black = 2,
    R_Asian = 3
};

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
    S_Smoking = 4,
    S_WaitForElevator = 5,
    S_RideInElevator = 6,
    S_Working = 7,
    S_Falling = 8,
    S_GoToOffice = 9,
    S_GoHome = 10,
    S_GoSmoke = 11,
    S_GoToElevator = 12,
    S_GoToCabin = 13,

    S_Button_Normal = 101,
    S_Button_Pressed = 102,
};

enum Entities {
    E_Entity = 0,

    E_StaticGround_1 = 11,
    E_StaticGround_2 = 12,

    E_StaticTree_1 = 13,
    E_StaticGroundArtifact_1 = 14,

    E_Clerk = 21,

    E_ButtonAddClerk = 31,
    E_Question_Mark_ButtonAddClerk = 311,

    E_ButtonAddOffice = 32,
    E_Question_Mark_ButtonAddOffice = 321,

    E_ButtonAddElevatorShaftMiddle = 33,
    E_ButtonAddElevatorShaftTop = 33,
    E_ButtonAddElevatorCabin = 34,

    E_ButtonAddElevator = 35,
    E_Question_Mark_ButtonAddElevator = 351,

    E_OfficeDefault = 41,

    E_ElevatorShaftBottom = 51,
    E_ElevatorShaftMiddle = 52,
    E_ElevatorShaftTop = 53,
    E_ElevatorCabin = 54,

    E_Chair = 91,

    E_Indicator_Money = 101,
};

#endif