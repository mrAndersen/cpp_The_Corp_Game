#ifndef CORP_GAME_ENUM
#define CORP_GAME_ENUM

enum Scenes {
    SC_Loading = 0,
    SC_Main_Menu = 1,
    SC_Game = 2
};

enum DrawOrder {

    D_BG_Mountain_1 = 14,
    D_BG_Mountain_2 = 15,

    D_BG_Field_1 = 17,
    D_BG_Field_2 = 18,

    D_BG_Trees = 19,

    D_Ground = 20,
    D_Trees = 20,

    D_GroundArtifacts = 21,

    D_Offices = 98,
    D_Offices_Spawning = 99,

    D_Characters_Working = 100,
    D_Chair = 105,
    D_ElevatorShafts = 110,
    D_ElevatorCabin = 120,
    D_Characters = 200,

    D_Text_Entities = 150,

    D_Ui = 250,
    D_Ui_Over = 251,

    D_Popup = 251,
    D_Popup_Button = 252
};

enum DestinationType {
    DST_Unknown = 0,
    DST_Elevator_Waiting = 1,
    DST_Elevator_Exiting = 4,
    DST_Elevator_Inside_Cabin = 2,
    DST_Workplace = 3,
    DST_SmokeArea = 5,
    DST_Home = 6,
    DST_Buff_Position = 7,
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
    None = 0,
    Right = 1,
    Left = 2,
    Up = 3,
    Down = 4,

    UpRight,
    UpLeft,
    DownRight,
    DownLeft
};

enum States {
    S_None = 0,
    S_Play = 1,
    S_Run = 2,
    S_Walk = 3,
    S_Smoking = 4,
    S_Working = 7,

    S_Button_Normal = 101,
    S_Button_Pressed = 102,
};

enum Entities {
    E_Entity = 0,

    E_StaticGround_1 = 11,
    E_StaticGround_2 = 12,
    E_StaticGround_3 = 18,
    E_StaticTree_1 = 13,
    E_StaticTree_2 = 14,
    E_StaticGroundArtifact_1 = 15,
    E_StaticTree_3 = 16,
    E_StaticTree_4 = 17,



    E_Clerk = 21,
    E_Manager = 22,
    E_Accountant = 23,

    E_ButtonAddClerk = 31,
    E_Question_Mark_ButtonAddClerk = 311,

    E_ButtonAddOffice = 32,
    E_Question_Mark_ButtonAddOffice = 321,

    E_ButtonAddAccountant = 33,
    E_Question_Mark_ButtonAddAccountant = 331,

    E_ButtonAddElevator = 35,
    E_ButtonAddElevatorShaftMiddle = 351,
    E_ButtonAddElevatorShaftTop = 352,
    E_ButtonAddElevatorCabin = 353,
    E_Question_Mark_ButtonAddElevator = 354,

    E_ButtonAddManager = 36,
    E_Question_Mark_ButtonAddManager = 361,


    E_OfficeDefault = 41,

    E_ElevatorShaftBottom = 51,
    E_ElevatorShaftMiddle = 52,
    E_ElevatorShaftTop = 53,
    E_ElevatorCabin = 54,

    E_Chair = 91,

    E_Indicator_Money = 101,
    E_MainPanelOverlay = 102,
    E_ButtonPause = 103,
    E_Button1x = 104,
    E_Button5x = 105,
    E_Button10x = 106,
    E_Popup = 107,
    E_Popup_Button = 108,
    E_Cog = 109,

    E_Cloud1 = 1001,
    E_Cloud2 = 1002,
    E_Cloud3 = 1003,
    E_Cloud4 = 1004,

    E_Stats_Daily_Income = 20001,
    E_Stats_Daily_Loss = 20002
};

#endif