#pragma once

#include <so/so_module_accesser.h>
#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_outside_event_presenter.h>
#include <ft/ft_value_accesser.h>
#include <mt/mt_vector.h>
#include <so/stageobject.h>
#include <sr/sr_common.h>
#include <types.h>

class itCustomizerInterface;
class ftOwner;

class Fighter : public StageObject, public soStatusEventObserver, public soSituationEventObserver, public soCollisionAttackEventObserver, public soCollisionHitEventObserver, public soCollisionShieldEventObserver, public soCollisionReflectorEventObserver, public soCollisionAbsorberEventObserver, public soCollisionSearchEventObserver, public soCaptureEventObserver, public soItemManageEventObserver, public soMotionEventObserver, public soDamageEventObserver, public ftEntryEventObserver, public soTurnEventObserver {
public:
    struct Status {
        enum Kind {
            Wait = 0x0,
            Walk = 0x1,
            Walk_Brake = 0x2,
            Dash = 0x3,
            Run = 0x4,
            Run_Brake = 0x5,
            Turn = 0x6,
            Turn_Dash = 0x7,
            Turn_Run = 0x8,
            Turn_Run_Brake = 0x9,
            Jump_Squat = 0xA,
            Jump = 0xB,
            Jump_Aerial = 0xC,
            Fly = 0xD,
            Fall = 0xE,
            Fall_Aerial = 0xF,
            Fall_Special = 0x10,
            Squat = 0x11,
            Squat_Wait = 0x12,
            Squat_F = 0x13,
            Squat_B = 0x14,
            Squat_Rv = 0x15,
            Landing = 0x16,
            Landing_Light = 0x17,
            Landing_Attack_Air = 0x18,
            Landing_Fall_Special = 0x19,
            Guard_On = 0x1A,
            Guard = 0x1B,
            Guard_Off = 0x1C,
            Guard_Damage = 0x1D,
            Escape = 0x1E,
            Escape_F = 0x1F,
            Escape_B = 0x20,
            Escape_Air = 0x21,
            Rebound_Stop = 0x22,
            Rebound = 0x23,
            Attack = 0x24,
            Attack_100 = 0x25,
            Attack_Dash = 0x26,
            Attack_S3 = 0x27,
            Attack_Hi3 = 0x28,
            Attack_Lw3 = 0x29,
            Attack_S4_Start = 0x2A,
            Attack_S4_Hold = 0x2B,
            Attack_S4 = 0x2C,
            Attack_Lw4_Start = 0x2D,
            Attack_Lw4_Hold = 0x2E,
            Attack_Lw4 = 0x2F,
            Attack_Hi4_Start = 0x30,
            Attack_Hi4_Hold = 0x31,
            Attack_Hi4 = 0x32,
            Attack_Air = 0x33,
            Catch = 0x34,
            Catch_Pull = 0x35,
            Catch_Dash = 0x36,
            Catch_Dash_Pull = 0x37,
            Catch_Turn = 0x38,
            Catch_Wait = 0x39,
            Catch_Attack = 0x3A,
            Catch_Cut = 0x3B,
            Throw = 0x3C,
            Capture_Pulled = 0x3D,
            Capture_Wait = 0x3E,
            Capture_Damage = 0x3F,
            Capture_Cut = 0x40,
            Capture_Jump = 0x41,
            Capture_Thrown = 0x42,
            Damage = 0x43,
            Damage_Air = 0x44,
            Damage_Fly = 0x45,
            Damage_Fly_Roll = 0x46,
            Damage_Fly_Reflect_Lr = 0x47,
            Damage_Fly_Reflect_U = 0x48,
            Damage_Fall = 0x49,
            Down = 0x4A,
            Down_Spot = 0x4B,
            Down_Continue = 0x4C,
            Down_Wait = 0x4D,
            Down_Wait_Continue = 0x4E,
            Down_Eat = 0x4F,
            Lay_Down = 0x50,
            Down_Stand = 0x51,
            Down_Stand_Fb = 0x52,
            Down_Stand_Attack = 0x53,
            Down_Damage = 0x54,
            Down_Reflect_Lr = 0x55,
            Shield_Break_Fly = 0x56,
            Shield_Break_Fall = 0x57,
            Shield_Break_Down = 0x58,
            FuraFura_Stand = 0x59,
            FuraFura = 0x5A,
            FuraFura_End = 0x5B,
            Damage_Song_Start = 0x5C,
            Damage_Song = 0x5D,
            Damage_Song_End = 0x5E,
            Bind = 0x5F,
            Passive = 0x60,
            Passive_Fb = 0x61,
            Passive_Wall = 0x62,
            Passive_Wall_Jump = 0x63,
            Passive_Ceil = 0x64,
            Stop_Wall = 0x65,
            Stop_Ceil = 0x66,
            Wall_Jump = 0x67,
            Attach_Wall = 0x68,
            Attach_Wall_Wait = 0x69,
            Detach_Wall = 0x6A,
            Detach_Wall_Fall = 0x6B,
            Detach_Wall_Jump = 0x6C,
            Tread_Jump = 0x6D,
            Tread_Damage = 0x6E,
            Tread_Damage_Rv = 0x6F,
            Tread_Damage_Air = 0x70,
            Tread_Fall = 0x71,
            Pass = 0x72,
            Cliff_Catch_Move = 0x73,
            Cliff_Catch = 0x74,
            Cliff_Wait = 0x75,
            Cliff_Attack = 0x76,
            Cliff_Climb = 0x77,
            Cliff_Escape = 0x78,
            Cliff_Jump1 = 0x79,
            Cliff_Jump2 = 0x7A,
            Cliff_Jump3 = 0x7B,
            Ottoto = 0x7C,
            Ottoto_Wait = 0x7D,
            Miss_Foot = 0x7E,
            Air_Lasso = 0x7F,
            Air_Lasso_Reach = 0x80,
            Air_Lasso_Hang = 0x81,
            Air_Lasso_Rewind = 0x82,
            Air_Lasso_Failure = 0x83,
            Glide_Start = 0x84,
            Glide = 0x85,
            Glide_Landing = 0x86,
            Glide_Attack = 0x87,
            Glide_End = 0x88,
            Slip = 0x89,
            Slip_Down = 0x8A,
            Slip_Turn = 0x8B,
            Slip_Dash = 0x8C,
            Slip_Wait = 0x8D,
            Slip_Stand = 0x8E,
            Slip_Stand_Attack = 0x8F,
            Slip_Stand_F = 0x90,
            Slip_Stand_B = 0x91,
            Ladder_Catch = 0x92,
            Ladder_Catch_End = 0x93,
            Ladder_Wait = 0x94,
            Ladder_End = 0x95,
            Item_Pickup_Light = 0x96,
            Item_Pickup_Heavy = 0x97,
            Item_Lift_Wait = 0x98,
            Item_Lift_Turn = 0x99,
            Item_Lift_Walk = 0x9A,
            Item_Throw = 0x9B,
            Item_Throw_Dash = 0x9C,
            Item_Throw_Heavy = 0x9D,
            Item_Swing = 0x9E,
            Item_Swing_S3 = 0x9F,
            Item_Swing_S4_Start = 0xA0,
            Item_Swing_S4 = 0xA1,
            Item_Swing_S4_Hold = 0xA2,
            Item_Swing_Dash = 0xA3,
            Item_Shoot_Wait = 0xA4,
            Item_Shoot_Walk_F = 0xA5,
            Item_Shoot_Walk_Brake_F = 0xA6,
            Item_Shoot_Walk_B = 0xA7,
            Item_Shoot_Walk_Brake_B = 0xA8,
            Item_Shoot_Dash_F = 0xA9,
            Item_Shoot_Dash_B = 0xAA,
            Item_Shoot_Jump_Squat = 0xAB,
            Item_Shoot_Jump = 0xAC,
            Item_Shoot_Air = 0xAD,
            Item_Shoot_Landing = 0xAE,
            Item_Screw_Jump = 0xAF,
            Item_Screw_Jump_Aerial = 0xB0,
            Item_Screw_Fall = 0xB1,
            Item_Assist_Hoist = 0xB2,
            Swim_Dive = 0xB3,
            Swim_Rise = 0xB4,
            Swim_Up = 0xB5,
            Swim_Wait = 0xB6,
            Swim = 0xB7,
            Swim_End = 0xB8,
            Swim_Turn = 0xB9,
            Swim_Jump = 0xBA,
            Swim_Drown = 0xBB,
            Swim_Drown_Out = 0xBC,
            Dead = 0xBD,
            Rebirth = 0xBE,
            Gimmick_Door = 0xBF,
            Gimmick_Barrel = 0xC0,
            Gimmick_Catapult = 0xC1,
            Gimmick_Truck = 0xC2,
            Gimmick_Spring = 0xC3,
            Gimmick_Spring_Jump = 0xC4,
            Gimmick_Spring_Back = 0xC5,
            Gimmick_Eaten = 0xC6,
            Bury = 0xC7,
            Bury_Wait = 0xC8,
            Bury_Jump = 0xC9,
            Ice = 0xCA,
            Ice_Jump = 0xCB,
            Bitten_Wario_Start = 0xCC,
            Bitten_Wario = 0xCD,
            Bitten_Wario_End = 0xCE,
            Clung_Captain = 0xCF,
            Swallowed = 0xD0,
            Swallowed_Drink = 0xD1,
            Swallowed_Capture = 0xD2,
            Swallowed_Thrown_Star = 0xD3,
            Swallowed_Thrown = 0xD4,
            Swallowed_Canceled = 0xD5,
            Clung_Diddy = 0xD6,
            Clung_Damage_Diddy = 0xD7,
            Clung_Thrown_Diddy = 0xD8,
            Shouldered_Donkey_Start = 0xD9,
            Shouldered_Donkey = 0xDA,
            Shouldered_Donkey_Thrown = 0xDB,
            Warpstar = 0xDC,
            Warpstar_Jump = 0xDD,
            Dragoon_Ride = 0xDE,
            Hammer_Wait = 0xDF,
            Hammer_Walk = 0xE0,
            Hammer_Turn = 0xE1,
            Hammer_Jump_Squat = 0xE2,
            Hammer_Jump = 0xE3,
            Hammer_Fall = 0xE4,
            Hammer_Landing = 0xE5,
            Clung_Ganon = 0xE6,
            Catched_Ganon = 0xE7,
            Catched_Air_Ganon = 0xE8,
            Catched_Air_Fall_Ganon = 0xE9,
            Catched_Air_End_Ganon = 0xEA,
            Capture_Yoshi = 0xEB,
            Yoshi_Egg = 0xEC,
            Link_Final = 0xED,
            Koopa_Dived = 0xEE,
            Metaknight_Final = 0xEF,
            Pit_Fall = 0xF0,
            Throw_Kirby = 0xF1,
            Big = 0xF2,
            Small = 0xF3,
            Heart_Swap = 0xF4,
            Heart_Swap_End = 0xF5,
            Adv_Follow = 0xF6,
            Ike_Final_Damage_Fly = 0xF7,
            Ike_Final_Damage = 0xF8,
            Ike_Final_Damage_Fall = 0xF9,
            Capture_Masterhand = 0xFA,
            Final_Visual_Attack_Other = 0xFB,
            Captain_Final_Start = 0xFC,
            Captain_Final_FuraFura = 0xFD,
            Captain_Final_Clash = 0xFE,
            Captain_Final_End = 0xFF,
            Kirby_Final_Damage_Fly = 0x100,
            Kirby_Final_Damage_Wait = 0x101,
            Capture_Gokulin = 0x102,
            Capture_Cut_Gokulin = 0x103,
            Capture_Taboo = 0x104,
            Capture_Bucyulus = 0x105,
            Capture_Cut_Bucyulus = 0x106,
            Capture_Pulled_Yoshi = 0x107,
            Capture_Wait_Yoshi = 0x108,
            Capture_Damage_Yoshi = 0x109,
            Capture_Cut_Yoshi = 0x10A,
            Standby = 0x10B,
            Appeal  = 0x10C,
            Smash_Appeal = 0x10D,
            Entry = 0x10E,
            Win = 0x10F,
            Lose = 0x110,
            Test_Motion = 0x111
        };

        struct Transition {
            enum TermId {
                Term_Wait = 10000,
                Term_Wait_From_Run_Brake = 10001,
                Term_Fall = 10002,
                Term_Fall_Aerial = 10003,
                Term_Fall_Special = 10004,
                Term_Damage_Fall = 10005,
                Term_Damage_Fly_Reflect_L = 10006, // TODO: Verify
                Term_Damage_Fly_Reflect_R = 10007, // TODO: Verify
                Term_Damage_Fly_Reflect_U = 10008, // TODO: Verify
                Term_Dash_To_Run = 10009,
                Term_Slip = 10010,
                Term_Run = 10011,
                Term_Down = 10012,
                Term_Down_Wait = 10013,
                Term_Down_Stand = 10014,
                Term_Down_Damage_Fall = 10015,
                Term_Down_Damage_Reflect_L = 10016,
                Term_Down_Damage_Reflect_R = 10017,
                Term_Passive = 10018,
                Term_Passive_Fb = 10019,
                Term_Passive_Wall = 10020,
                Term_Passive_Wall_Jump = 10021,
                Term_Passive_Wall_Jump_Button = 10022,
                Term_Passive_Ceil = 10023,
                Term_Stop_Wall = 10024,
                Term_Stop_Ceil = 10025,
                Term_Landing = 10026,
                Term_Landing_Light = 10027,
                Term_Landing_Attack_Air = 10028,
                Term_Landing_Fall_Special = 10029,
                Term_Cliff_Catch = 10030,
                Term_Glide = 10031,
                Term_Glide_Landing = 10032,
                Term_Squat_Wait = 10033,
                Term_Catch_Wait = 10034,
                Term_Capture_Wait = 10035,
                Term_Capture_Cut = 10036,
                Term_Cont_Escape = 10037,
                Term_Cont_Escape_F = 10038,
                Term_Cont_Escape_B = 10039,
                Term_Cont_Guard_On = 10040,
                Term_Cont_Guard = 10041,
                Term_Cont_Jump_Squat = 10042,
                Term_Cont_Jump_Squat_Button = 10043,
                Term_Cont_Dash = 10044,
                Term_Cont_Run_Brake = 10045,
                Term_Cont_Turn = 10046,
                Term_Cont_Turn_Run = 10047,
                Term_Cont_Turn_Dash = 10048,
                Term_Cont_Turn_Dash_Dash = 10049,
                Term_Cont_Slip_Turn = 10050,
                Term_Cont_Squat = 10051,
                Term_Cont_Squat_Rv = 10052,
                Term_Cont_Squat_Wait = 10053,
                Term_Cont_Squat_F = 10054,
                Term_Cont_Squat_B = 10055,
                Term_Cont_Appeal_Hi = 10056,
                Term_Cont_Appeal_S = 10057,
                Term_Cont_Appeal_Lw = 10058,
                Term_Cont_Walk = 10059,
                Term_Cont_Escape_Air = 10060,
                Term_Cont_Jump_Aerial = 10061,
                Term_Cont_Jump_Aerial_Button = 10062,
                Term_Cont_Tread_Jump = 10063,
                Term_Cont_Tread_Jump_Button = 10064,
                Term_Cont_Tread_Jump_No_Trigger = 10065,
                Term_Cont_Fly = 10066,
                Term_Cont_Fly_Button = 10067,
                Term_Cont_Fly_Next = 10068,
                Term_Cont_Cliff_Attack = 10069,
                Term_Cont_Cliff_Special = 10070,
                Term_Cont_Cliff_Escape = 10071,
                Term_Cont_Cliff_Climb = 10072,
                Term_Cont_Cliff_Fall = 10073,
                Term_Cont_Cliff_Jump = 10074,
                Term_Cont_Cliff_Jump_Button = 10075,
                Term_Cont_Glide_Start = 10076,
                Term_Cont_Glide_End = 10077,
                Term_Cont_Glide_Attack = 10078,
                Term_Cont_Pass = 10079,
                Term_Cont_Air_Lasso = 10080,
                Term_Cont_Attack = 10081,
                Term_Cont_Attack_100 = 10082,
                Term_Cont_Attack_Dash = 10083,
                Term_Cont_Attack_S3 = 10084,
                Term_Cont_Attack_Hi3 = 10085,
                Term_Cont_Attack_Lw3 = 10086,
                Term_Cont_Attack_S4 = 10087,
                Term_Cont_Attack_S4_Start = 10088,
                Term_Cont_Attack_S4_Hold = 10089,
                Term_Cont_Attack_Hi4 = 10090,
                Term_Cont_Attack_Hi4_Start = 10091,
                Term_Cont_Attack_Hi4_Hold = 10092,
                Term_Cont_Attack_Lw4 = 10093,
                Term_Cont_Attack_Lw4_Start = 10094,
                Term_Cont_Attack_Lw4_Hold = 10095,
                Term_Cont_Attack_Air = 10096,
                Term_Cont_Special_N = 10097,
                Term_Cont_Special_S = 10098,
                Term_Cont_Special_Hi = 10099,
                Term_Cont_Special_Lw = 10100,
                Term_Cont_Throw_Fb = 10101,
                Term_Cont_Throw_Hi = 10102,
                Term_Cont_Throw_Lw = 10103,
                Term_Cont_Catch = 10104,
                Term_Cont_Catch_Dash = 10105,
                Term_Cont_Catch_Turn = 10106,
                Term_Cont_Capture_Jump_Button = 10107,
                Term_Cont_Capture_Jump = 10108,
                Term_Cont_Item_Pickup_Light = 10109,
                Term_Cont_Item_Pickup_Heavy = 10110,
                Term_Cont_Item_Throw = 10111,
                Term_Cont_Item_Throw_Guard = 10112,
                Term_Cont_Item_Throw_Force = 10113,
                Term_Cont_Item_Throw_Force_Dash = 10114,
                Term_Cont_Item_Throw_Dash = 10115,
                Term_Cont_Item_Throw_Dash_Clacker = 10116,
                Term_Cont_Item_Swing_Bat_4 = 10117,
                Term_Cont_Item_Swing_4 = 10118,
                Term_Cont_Item_Swing_4_Hold = 10119,
                Term_Cont_Item_Swing_3 = 10120,
                Term_Cont_Item_Swing = 10121,
                Term_Cont_Item_Swing_Dash = 10122,
                Term_Cont_Item_Shoot = 10123,
                Term_Cont_Item_Shoot_S3 = 10124,
                Term_Cont_Item_Shoot_S4 = 10125,
                Term_Cont_Item_Shoot_Wait = 10126,
                Term_Cont_Item_Shoot_Walk_F = 10127,
                Term_Cont_Item_Shoot_Walk_F_Brake = 10128,
                Term_Cont_Item_Shoot_Walk_B = 10129,
                Term_Cont_Item_Shoot_Walk_B_Brake = 10130,
                Term_Cont_Item_Shoot_Dash_F = 10131,
                Term_Cont_Item_Shoot_Dash_B = 10132,
                Term_Cont_Item_Shoot_Air = 10133,
                Term_Cont_Item_Shoot_Air_Pass = 10134,
                Term_Cont_Item_Shoot_Jump_Button = 10135,
                Term_Cont_Item_Shoot_Jump = 10136,
                Term_Cont_Item_Shoot_Turn_Dash = 10137,
                Term_Cont_Item_Shoot_Landing = 10138,
                Term_Item_Gekikara_Wait = 10139,
                Term_Item_Gekikara_Run = 10140,
                Term_Cont_Item_Gekikara_Run_Brake = 10141,
                Term_Throw_Kirby_Ground = 10142,
                Term_Final = 10143,
                Term_Throw_Enemy = 10144,
                Term_Smash_Appeal = 10145, // TODO: Verify
            };

            enum TermGroupId {
                // 0x0
                Group_Chk_Ground_Special = 0x1,
                Group_Chk_Ground_Item = 0x2,
                Group_Chk_Ground_Catch = 0x3,
                Group_Chk_Ground_Attack = 0x4,
                Group_Chk_Ground_Escape = 0x5,
                Group_Chk_Ground_Guard = 0x6,
                Group_Chk_Ground_Jump = 0x7,
                Group_Chk_Ground = 0x8,
                Group_Chk_Air_Landing = 0x9,
                Group_Chk_Air_Cliff = 0xA,
                Group_Chk_Air_Special = 0xB,
                Group_Chk_Air_Item_Throw = 0xC,
                Group_Chk_Air_Lasso = 0xD,
                Group_Chk_Air_Escape = 0xE,
                Group_Chk_Air_Attack = 0xF,
                Group_Chk_Air_Tread_Jump = 0x10,
                Group_Chk_Air_Wall_Jump = 0x11,
                Group_Chk_Air_Jump_Aerial = 0x12,
                // 0x13
            };
        };

        struct Work {
            enum Int {

            };

            enum Float {
                Float_Reserve_Hold_Rate = 0x21000000,
                Float_Rebound_Frame = 0x21000001,
                Float_Rebound_Lr = 0x21000002,
            };

            enum Flag {
                Flag_Reserve_Dive = 0x22000002,
                Flag_Reserve_Check_Dead_Area_Force = 0x22000004,
                Flag_Reserve_Jump_Mini = 0x22000006,
                Flag_Reserve_Jump_From_Tread = 0x22000007,
                Flag_Reserve_Jump_From_Ladder = 0x22000008,

                Flag_Reserve_Jump_From_Shoot = 0x2200000A,
                Flag_Reserve_Jump_From_Water = 0x2200000B,
                Flag_Reserve_Jump_From_Spring = 0x2200000C,
                Flag_Reserve_Disable_Outside_Energy = 0x2200000D,
            };
        };

        struct Attack_Air {
            struct Work {
                enum Int {
                    Int_Motion_Kind = 0x20000000,
                };
                enum Float {

                };
                enum Flag {

                };
            };
        };

        struct Tread {
            struct Work {
                enum Int {

                };
                enum Float {
                    Float_Jump_Speed_Mul = 0x21000004,
                };
                enum Flag {

                };
            };
        };

        struct Item_Throw {
            struct Work {
                enum Int {

                };
                enum Float {
                    Float_Lr = 0x21000004,
                };
                enum Flag {

                };
            };
        };

        struct Ladder {
            struct Work {
                enum Int {

                };
                enum Float {
                    Float_Ladder_Upper_X = 0x21000004,
                    Float_Ladder_Upper_Y = 0x21000005,
                    Float_Ladder_End_X = 0x21000005,
                    Float_Ladder_End_Y = 0x21000006,
                    Float_Ladder_End_Start_X = 0x21000007,
                    Float_Ladder_End_Start_Y = 0x21000008,
                };
                enum Flag {
                    Flag_Fall = 0x22000010,
                };
            };
        };

        struct Swim {
            struct Work {
                enum Int {
                    Int_Water_Task_Id = 0x20000002,
                    Int_Eff_Counter = 0x20000003,
                    Int_No_Water_Frame = 0x20000004,
                };
                enum Float {

                };
                enum Flag {
                    Flag_Damage = 0x22000010
                };
            };
        };

        struct Dead {
            struct Work {
                enum Int {
                };
                enum Float {
                };
                enum Flag {
                };
            };
        };

        struct Gimmick_Door {
            enum Step {
                Step_Turn = 0x0,
                Step_Walk_To_Center = 0x1,
                Step_Walk_Through = 0x2,
                Step_Wait = 0x3,
            };
            struct Work {
                enum Int {
                    Int_Step = 0x20000000,
                };
                enum Float {
                    Float_Center_X = 0x21000004,
                    Float_Center_Y = 0x21000005,
                };
                enum Flag {
                    Flag_No_Into = 0x22000010,
                };
            };
        };

        struct Gimmick_Spring {
            struct Work {
                enum Int {

                };
                enum Float {
                    Float_Shoot_Speed_Y = 0x21000004,
                    Float_Shoot_Angle = 0x21000005,
                };
                enum Flag {

                };
            };
        };

        struct Gimmick_Barrel {
            enum Step {
                Step_In = 0x0,
                Step_Shoot_Wait = 0x1,
                Step_Shoot = 0x2,
            };
            struct Work {
                enum Int {
                    Int_Step = 0x20000000,
                    Int_Break_Hitstop_Frame = 0x20000002,
                };
                enum Float {
                    Float_Fall_Speed = 0x21000004,
                    Float_Shoot_Offset_X = 0x21000005,
                    Float_Shoot_Offset_Y = 0x21000006,
                };
                enum Flag {
                    Flag_End_Speed = 0x22000010,
                };
            };
        };

        struct Gimmick_Truck {
            struct Work {
                enum Int {

                };
                enum Float {
                    Float_Speed_X = 0x21000004,
                    Float_Speed_Y = 0x21000005,
                };
                enum Flag {
                    Flag_Run = 0x22000010,
                };
            };
        };
    };

    struct Motion {
        enum Kind {
            Wait_1 = 0x0,
            Wait_2 = 0x1,
            Wait_3 = 0x2,
            Tex_Anim = 0x3,

            Wait_Item = 0x5,
            Item_Hand_Pickup = 0x6,
            Item_Hand_Have = 0x7,
            Item_Hand_Grip = 0x8,
            Item_Hand_Smash = 0x9,
            Walk_Slow = 0xA,
            Walk_Middle = 0xB,
            Walk_Fast = 0xC,
            Walk_Brake = 0xD,
            Dash = 0xE,
            Run = 0xF,
            Run_Brake = 0x10,
            Turn = 0x11,
            Turn_Run = 0x12,
            Turn_Run_Brake = 0x13,
            Jump_Squat = 0x14,
            Jump_F = 0x15,
            Jump_F_ = 0x16,
            Jump_B = 0x17,
            Jump_B_ = 0x18,
            Jump_Aerial_F = 0x19,
            Jump_Aerial_B = 0x1A,
            Special_N_Cancel = 0x1B,
            Special_Air_N_Cancel = 0x1C,
            Appeal_Brawl_Lw_R = 0x1D,
            Appeal_Brawl_Lw_L = 0x1E,
            Appeal_Brawl_S = 0x1F,
            Fall = 0x20,
            Fall_F = 0x21,
            Fall_B = 0x22,
            Fall_Aerial = 0x23,
            Fall_Aerial_F = 0x24,
            Fall_Aerial_B = 0x25,
            Fall_Special = 0x26,
            Fall_Special_F = 0x27,
            Fall_Special_B = 0x28,
            Damage_Fall = 0x29,
            Squat = 0x2A,
            Squat_Wait = 0x2B,
            Squat_Wait_2 = 0x2C,
            Squat_Wait_Item = 0x2D,
            Squat_F = 0x2E,
            Squat_B = 0x2F,
            Squat_Rv = 0x30,
            Landing_Light = 0x31,
            Landing_Heavy = 0x32,
            Landing_Fall_Special = 0x33,
            Step_Jump = 0x34,
            Step_Pose = 0x35,
            Step_Back = 0x36,
            Step_Air_Pose = 0x37,
            Step_Fall = 0x38,
            Glide_Start = 0x39,
            Glide_Direction = 0x3A,
            Glide_Wing = 0x3B,
            Glide_Attack = 0x3C,
            Glide_End = 0x3D,
            Glide_Landing = 0x3E,
            Guard_On = 0x3F,
            Guard = 0x40,
            Guard_Off = 0x41,
            Guard_Damage = 0x42,
            Escape_N = 0x43,
            Escape_F = 0x44,
            Escape_B = 0x45,
            Escape_Air = 0x46,
            Rebound = 0x47,
            Attack_11 = 0x48,
            Attack_12 = 0x49,
            Attack_13 = 0x4A,
            Attack_100_Start = 0x4B,
            Attack_100 = 0x4C,
            Attack_End = 0x4D,
            Attack_Dash = 0x4E,
            Attack_S3_Hi = 0x4F,
            Attack_S3_S = 0x50,
            Attack_Dash_Air = 0x51,

            Attack_S3_Lw = 0x53,
            Attack_Hi_3 = 0x54,
            Attack_Lw_3 = 0x55,
            Attack_S4_Start = 0x56,
            Attack_S4_Hi = 0x57,
            Attack_S4_S = 0x58,

            Attack_S4_Lw = 0x5A,
            Attack_S4_Hold = 0x5B,
            Attack_Hi_4_Start = 0x5C,
            Attack_Hi_4 = 0x5D,
            Attack_Hi_4_Hold = 0x5E,
            Attack_Lw_4_Start = 0x5F,
            Attack_Lw_4 = 0x60,
            Attack_Lw_4_Hold = 0x61,
            Attack_Air_N = 0x62,
            Attack_Air_F = 0x63,
            Attack_Air_B = 0x64,
            Attack_Air_Hi = 0x65,
            Attack_Air_Lw = 0x66,
            Landing_Air_N = 0x67,
            Landing_Air_F = 0x68,
            Landing_Air_B = 0x69,
            Landing_Air_Hi = 0x6A,
            Landing_Air_Lw = 0x6B,
            Catch = 0x6C,
            Catch_Dash = 0x6D,
            Catch_Turn = 0x6E,
            Catch_Wait = 0x6F,
            Catch_Attack = 0x70,
            Catch_Cut = 0x71,
            Throw_B = 0x72,
            Throw_F = 0x73,
            Throw_Hi = 0x74,
            Throw_Lw = 0x75,
            Thrown_B = 0x76,
            Thrown_F = 0x77,
            Thrown_Hi = 0x78,
            Thrown_Lw = 0x79,
            Thrown_Dx_B = 0x7A,
            Thrown_Dx_F = 0x7B,
            Thrown_Dx_Hi = 0x7C,
            Thrown_Dx_Lw = 0x7D,
            Capture_Pulled_Hi = 0x7E,
            Capture_Wait_Hi = 0x7F,
            Capture_Damage_Hi = 0x80,
            Capture_Pulled_Lw = 0x81,
            Capture_Wait_Lw = 0x82,
            Capture_Damage_Lw = 0x83,
            Capture_Pulled_Snake = 0x84,
            Capture_Wait_Snake = 0x85,
            Capture_Damage_Snake = 0x86,
            Capture_Pulled_Snake_ = 0x87,
            Capture_Wait_Snake_ = 0x88,
            Capture_Damage_Snake_ = 0x89,
            Capture_Pulled_Dx_Snake = 0x8A,
            Capture_Wait_Dx_Snake = 0x8B,
            Capture_Damage_Dx_Snake = 0x8C,
            Capture_Pulled_Dx_Snake_ = 0x8D,
            Capture_Wait_Dx_Snake_ = 0x8E,
            Capture_Damage_Dx_Snake_ = 0x8F,
            Capture_Pulled_Big_Snake = 0x90,
            Capture_Wait_Big_Snake = 0x91,
            Capture_Damage_Big_Snake = 0x92,
            Capture_Pulled_Big_Snake_ = 0x93,
            Capture_Wait_Big_Snake_ = 0x94,
            Capture_Damage_Big_Snake_ = 0x95,
            Capture_Cut = 0x96,
            Capture_Jump = 0x97,
            Damage_Hi_1 = 0x98,
            Damage_Hi_2 = 0x99,
            Damage_Hi_3 = 0x9A,
            Damage_N_1 = 0x9B,
            Damage_N_2 = 0x9C,
            Damage_N_3 = 0x9D,
            Damage_Lw_1 = 0x9E,
            Damage_Lw_2 = 0x9F,
            Damage_Lw_3 = 0xA0,
            Damage_Air_1 = 0xA1,
            Damage_Air_2 = 0xA2,
            Damage_Air_3 = 0xA3,
            Damage_Fly_Hi = 0xA4,
            Damage_Fly_N = 0xA5,
            Damage_Fly_Lw = 0xA6,
            Damage_Fly_Top = 0xA7,
            Damage_Fly_Roll = 0xA8,
            Damage_Elec = 0xA9,
            Down_Bound_U = 0xAA,
            Down_Wait_U = 0xAB,
            Down_Damage_U = 0xAC,
            Down_Damage_U_3 = 0xAD,
            Down_Eat_U = 0xAE,
            Down_Stand_U = 0xAF,
            Down_Attack_U = 0xB0,
            Down_Forward_U = 0xB1,
            Down_Back_U = 0xB2,
            Down_Bound_D = 0xB3,
            Down_Wait_D = 0xB4,
            Down_Damage_D = 0xB5,
            Down_Damage_D_3 = 0xB6,
            Down_Eat_D = 0xB7,
            Down_Stand_D = 0xB8,
            Down_Attack_D = 0xB9,
            Down_Forward_D = 0xBA,
            Down_Back_D = 0xBB,
            Down_Spot_U = 0xBC,
            Down_Spot_D = 0xBD,
            Passive = 0xBE,
            Passive_Stand_F = 0xBF,
            Passive_Stand_B = 0xC0,
            Passive_Wall = 0xC1,
            Passive_Wall_Jump = 0xC2,
            Passive_Ceil = 0xC3,
            Passive_Wall_Attach = 0xC4,
            FuraFura = 0xC5,
            FuraFura_Start_U = 0xC6,
            FuraFura_Start_D = 0xC7,
            FuraFura_End = 0xC8,
            Fura_Sleep_Start = 0xC9,
            Fura_Sleep_Loop = 0xCA,
            Fura_Sleep_End = 0xCB,
            Swallowed = 0xCC,
            Pass = 0xCD,
            Ottotto = 0xCE,
            Ottotto_Wait = 0xCF,
            Wall_Damage = 0xD0,
            Stop_Ceil = 0xD1,
            Stop_Wall = 0xD2,
            Stop_Ceil_ = 0xD3,
            Miss_Foot = 0xD4,
            Cliff_Catch = 0xD5,
            Cliff_Wait = 0xD6,
            Cliff_Attack_Quick = 0xD7,
            Cliff_Climb_Quick = 0xD8,
            Cliff_Escape_Quick = 0xD9,
            Cliff_Jump_Quick_1 = 0xDA,
            Cliff_Jump_Quick_2 = 0xDB,
            Cliff_Attack_Slow = 0xDC,
            Cliff_Climb_Slow = 0xDD,
            Cliff_Escape_Slow = 0xDE,
            Cliff_Jump_Slow_1 = 0xDF,
            Cliff_Jump_Slow_2 = 0xE0,
            Slip_Down = 0xE1,
            Slip = 0xE2,
            Slip_Turn = 0xE3,
            Slip_Dash = 0xE4,
            Slip_Wait = 0xE5,
            Slip_Stand = 0xE6,
            Slip_Attack = 0xE7,
            Slip_Escape_F = 0xE8,
            Slip_Escape_B = 0xE9,
            Air_Catch = 0xEA,
            Air_Catch_Pose = 0xEB,
            Air_Catch_Hit = 0xEC,
            Air_Catch_ = 0xED,
            Swim_Rise = 0xEE,
            Swim_Up = 0xEF,
            Swim_Up_Damage = 0xF0,
            Swim = 0xF1,
            Swim_F = 0xF2,
            Swim_End = 0xF3,
            Swim_Turn = 0xF4,
            Swim_Drown = 0xF5,
            Swim_Drown_Out = 0xF6,
            Light_Get = 0xF7,
            Light_Walk_Get = 0xF8,
            Light_Eat = 0xF9,
            Walk_Eat = 0xFA,
            Heavy_Get = 0xFB,
            Heavy_Walk_1 = 0xFC,
            Heavy_Walk_2 = 0xFD,
            Light_Throw_Drop = 0xFE,
            Light_Throw_F = 0xFF,
            Light_Throw_B = 0x100,
            Light_Throw_Hi = 0x101,
            Light_Throw_Lw = 0x102,
            Light_Throw_F_ = 0x103,
            Light_Throw_B_ = 0x104,
            Light_Throw_Hi_ = 0x105,
            Light_Throw_Lw_ = 0x106,
            Light_Throw_Dash = 0x107,
            Light_Throw_Air_F = 0x108,
            Light_Throw_Air_B = 0x109,
            Light_Throw_Air_Hi = 0x10A,
            Light_Throw_Air_Lw = 0x10B,
            Light_Throw_Air_F_ = 0x10C,
            Light_Throw_Air_B_ = 0x10D,
            Light_Throw_Air_Hi_ = 0x10E,
            Light_Throw_Air_Lw_ = 0x10F,
            Heavy_Throw_F = 0x110,
            Heavy_Throw_B = 0x111,
            Heavy_Throw_Hi = 0x112,
            Heavy_Throw_Lw = 0x113,
            Heavy_Throw_F_ = 0x114,
            Heavy_Throw_B_ = 0x115,
            Heavy_Throw_Hi_ = 0x116,
            Heavy_Throw_Lw_ = 0x117,
            Smash_Throw_F = 0x118,
            Smash_Throw_B = 0x119,
            Smash_Throw_Hi = 0x11A,
            Smash_Throw_Lw = 0x11B,
            Smash_Throw_Dash = 0x11C,
            Smash_Throw_Air_F = 0x11D,
            Smash_Throw_Air_B = 0x11E,
            Smash_Throw_Air_Hi = 0x11F,
            Smash_Throw_Air_Lw = 0x120,
            Swing_1_Sword = 0x121,
            Swing_3_Sword = 0x122,
            Swing_4_Start_Sword = 0x123,
            Swing_4_Sword = 0x124,
            Swing_4_2_Sword = 0x125,
            Swing_4_Hold_Sword = 0x126,
            Swing_Dash_Sword = 0x127,
            Swing_1_Bat = 0x128,
            Swing_3_Bat = 0x129,
            Swing_4_Bat = 0x12A,
            Swing_Dash_Bat = 0x12B,
            Swing_1_Harisen = 0x12C,
            Swing_3_Harisen = 0x12D,
            Swing_4_Start_Harisen = 0x12E,
            Swing_4_Harisen = 0x12F,
            Swing_4_2_Harisen = 0x130,
            Swing_4_Hold_Harisen = 0x131,
            Swing_Dash_Harisen = 0x132,
            Swing_1_StarRod = 0x133,
            Swing_3_StarRod = 0x134,
            Swing_4_Start_StarRod = 0x135,
            Swing_4_StarRod = 0x136,
            Swing_4_2_StarRod = 0x137,
            Swing_4_Hold_StarRod = 0x138,
            Swing_Dash_StarRod = 0x139,
            Swing_1_LipStick = 0x13A,
            Swing_3_LipStick = 0x13B,
            Swing_4_Start_LipStick = 0x13C,
            Swing_4_LipStick = 0x13D,
            Swing_4_2_LipStick = 0x13E,
            Swing_4_Hold_LipStick = 0x13F,
            Swing_Dash_LipStick = 0x140,
            Item_Hammer_Wait = 0x141,
            Item_Hammer_Move = 0x142,
            Item_Hammer_Air = 0x143,
            Item_Hammer_Wait_ = 0x144,
            Item_Hammer_Move_ = 0x145,
            Item_Hammer_Air_ = 0x146,
            Item_Warpstar_Ride = 0x147,
            Item_Screw = 0x148,
            Item_Screw_Aerial = 0x149,
            Item_Screw_Fall = 0x14A,
            Guard_On_ = 0x14B,
            Item_Dragoon_Get  = 0x14C,
            Item_Dragoon_Ride = 0x14D,
            Item_Big = 0x14E,
            Item_Small = 0x14F,
            Item_Legs_Wait = 0x150,
            Item_Legs_Slow_F = 0x151,
            Item_Legs_Middle_F = 0x152,
            Item_Legs_Fast_F = 0x153,
            Item_Legs_Brake_F = 0x154,
            Item_Legs_Dash_F = 0x155,
            Item_Legs_Slow_B = 0x156,
            Item_Legs_Middle_B = 0x157,
            Item_Legs_Fast_B = 0x158,
            Item_Legs_Brake_B = 0x159,
            Item_Legs_Dash_B = 0x15A,
            Item_Legs_Jump_Squat = 0x15B,
            Item_Legs_Landing = 0x15C,
            Item_Shoot_Gun = 0x15D,
            Item_Shoot_Air_Gun = 0x15E,
            Item_Shoot_Gun_Empty = 0x15F,
            Item_Shoot_Air_Gun_Empty = 0x160,
            Item_Shoot_Flower = 0x161,
            Item_Shoot_Air_Flower = 0x162,
            Item_Scope_Start = 0x163,
            Item_Scope_Rapid = 0x164,
            Item_Scope_Fire = 0x165,
            Item_Scope_End = 0x166,
            Item_Scope_Air_Start = 0x167,
            Item_Scope_Air_Rapid = 0x168,
            Item_Scope_Air_Fire = 0x169,
            Item_Scope_Air_End = 0x16A,
            Item_Scope_Start_Empty = 0x16B,
            Item_Scope_Rapid_Empty = 0x16C,
            Item_Scope_Fire_Empty = 0x16D,
            Item_Scope_End_Empty = 0x16E,
            Item_Scope_Air_Start_Empty = 0x16F,
            Item_Scope_Air_Rapid_Empty = 0x170,
            Item_Scope_Air_Fire_Empty = 0x171,
            Item_Scope_Air_End_Empty = 0x172,
            Item_Launcher = 0x173,
            Item_Launcher_Fire = 0x174,
            Item_Launcher_Air_Fire = 0x175,
            Item_Launcher_Empty = 0x176,
            Item_Launcher_Fire_Empty = 0x177,
            Item_Launcher_Air_Fire_Empty = 0x178,
            Item_Launcher_Fall = 0x179,
            Item_Launcher_Air = 0x17A,
            Item_Assist = 0x17B,
            Gekikara_Wait = 0x17C,
            Barrel = 0x17D,
            Catapult = 0x17E,
            Ladder_Wait = 0x17F,
            Ladder_Up = 0x180,
            Ladder_Down = 0x181,
            Ladder_Catch_R = 0x182,
            Ladder_Catch_L = 0x183,
            Ladder_Catch_Air_R = 0x184,
            Ladder_Catch_Air_L = 0x185,
            Ladder_Catch_End_R = 0x186,
            Ladder_Catch_End_L = 0x187,
            Rope_Catch = 0x188,
            Rope_Fishing = 0x189,
            Special_N_Bitten_Start = 0x18A,
            Special_N_Bitten = 0x18B,
            Special_N_Bitten_End = 0x18C,
            Special_Air_N_Bitten_Start = 0x18D,
            Special_Air_N_Bitten = 0x18E,
            Special_Air_N_Bitten_End = 0x18F,
            Special_N_Dx_Bitten_Start = 0x190,
            Special_N_Dx_Bitten = 0x191,
            Special_N_Dx_Bitten_End = 0x192,
            Special_Air_N_Dx_Bitten_Start = 0x193,
            Special_Air_N_Dx_Bitten = 0x194,
            Special_Air_N_Dx_Bitten_End = 0x195,
            Special_N_Big_Bitten_Start = 0x196,
            Special_N_Big_Bitten = 0x197,
            Special_N_Big_Bitten_End = 0x198,
            Special_Air_N_Big_Bitten_Start = 0x199,
            Special_AIr_N_Big_Bitten = 0x19A,
            Special_Air_N_Big_Bitten_End = 0x19B,
            Special_Hi_Capture = 0x19C,
            Special_Hi_Dx_Capture = 0x19D,
            Special_S_Stick_Capture = 0x19E,
            Special_S_Stick_Attack_Capture = 0x19F,
            Special_S_Stick_Jump_Capture = 0x1A0,
            Special_S_Dx_Stick_Capture = 0x1A1,
            Special_S_Dx_Stick_Attack_Capture = 0x1A2,
            Special_S_Dx_Stick_Jump_Capture = 0x1A3,
            Thrown_Zitabata = 0x1A4,
            Thrown_Dx_Zitabata = 0x1A5,
            Thrown_Girl_Zitabata = 0x1A6,
            Thrown_F_F = 0x1A7,
            Thrown_F_B = 0x1A8,
            Thrown_F_Hi = 0x1A9,
            Thrown_F_Lw = 0x1AA,
            Thrown_Dx_F_F = 0x1AB,
            Thrown_Dx_F_B = 0x1AC,
            Thrown_Dx_F_Hi = 0x1AD,
            Thrown_Dx_F_Lw = 0x1AE,
            Ganon_Special_Hi_Capture = 0x1AF,
            Ganon_Special_Hi_Dx_Capture = 0x1B0,
            Special_S_Capture = 0x1B1,
            Special_Air_S_Catch_Capture = 0x1B2,
            Special_Air_S_Fall_Capture = 0x1B3,
            Special_Air_S_Capture = 0x1B4,
            Special_S_Dx_Capture = 0x1B5,
            Special_Air_S_Dx_Catch_Capture = 0x1B6,
            Special_Air_S_Dx_Fall_Capture = 0x1B7,
            Special_Air_S_Dx_Capture = 0x1B8,
            Special_N_Egg = 0x1B9,
            Special_S_Zitabata = 0x1BA,
            Special_S_Dx_Zitabata = 0x1BB,
            Appeal_Hi_R = 0x1BC,
            Appeal_Hi_L = 0x1BD,
            Appeal_S_R = 0x1BE,
            Appeal_S_L = 0x1BF,
            Appeal_Lw_R = 0x1C0,
            Appeal_Lw_L = 0x1C1,
            Entry_R = 0x1C2,
            Entry_L = 0x1C3,
            Win_1 = 0x1C4,
            Win_1_Wait = 0x1C5,
            Win_2 = 0x1C6,
            Win_2_Wait = 0x1C7,
            Win_3 = 0x1C8,
            Win_3_Wait = 0x1C9,
            Lose = 0x1CA,
            Damage_Face = 0x1CB,
            Dark = 0x1CC,
            Spycloak = 0x1CD,
        };
    };

    struct Link : StageObject::Link {
        enum No {

        };

        enum EventKind {
            Event_Metaknight_Final = 1101,
        };
    };

    struct Area {
        enum Kind {
            Body = 0x0,

            Tread_Jump_Check = 0x2,

            Item_Pickup = 0x6,
            Item_Pickup_Air = 0x7,
            Wind = 0x8
        };
    };

    struct Model {
        enum NodeId {
            Node_Metroid = 201,

            Node_Correct_Throw = 300,
            Node_Correct_Hip = 301,
            Node_Correct_XRot = 302,
            Node_Correct_YRot = 303,
            Node_Correct_Trans = 304,
        };
    };

    struct Kinetic {
        struct Energy {
            enum Id {
                Id_Motion = 0x0,
                Id_Gravity = 0x1,
                Id_Control = 0x2,
                Id_Stop = 0x3,
                Id_Damage = 0x4,
                Id_Env_Wind = 0x5,
                Id_Ground_Movement = 0x6,
                Id_Jostle = 0x7,
            };
        };
    };

    struct Instance {
        struct Work {
            enum Int {
                Int_Entry_Id = 0x10000000,
                Int_Jump_Count = 0x10000001,
                Int_Cliff_No_Catch_Frame = 0x10000002,
                Int_Wall_Jump_Count = 0x10000003,
                Int_Wall_Jump_Past_Frame = 0x10000004,
                Int_Tread_Jump_Count = 0x10000005,
                Int_No_Tread_Frame = 0x10000006,
                Int_Tread_Target_Id = 0x10000007,
                Int_Tread_Target_Category = 0x10000008,
                Int_No_Slip_Frame = 0x10000009,
                Int_No_Damage_Slip_Frame = 0x1000000A,
                Int_No_Attach_Wall_Frame = 0x1000000B,
                Int_Attach_Wall_Count = 0x1000000C,
                Int_Speed_Y_Stable_Frame = 0x1000000D,
                Int_No_Barrel_Frame = 0x1000000E,
                Int_No_Catapult_Frame = 0x1000000F,
                Int_No_Ground_Damage_Frame = 0x10000010,
                Int_No_Ladder_Frame = 0x10000011,
                Int_No_Spring_Frame = 0x10000012,
                Int_Water_Jump_Count = 0x10000013,
                Int_Water_Into_Frame = 0x10000014,
                Int_Gimmick_Id = 0x10000015,
                Int_Gimmick_Event_Manage_Id = 0x10000016,
                Int_Gimmick_Kind = 0x10000017,
                Int_Flower_Counter = 0x10000018,
                Int_Gekikara_Counter = 0x10000019,
                Int_Gekikara_Shoot_Counter = 0x1000001A,
                Int_Hammer_Counter = 0x1000001B,
                Int_Hammer_Throw_Counter = 0x1000001C,
                Int_Hammer_SE_Handle = 0x1000001D,
                Int_SuperStar_Counter = 0x1000001E,
                Int_SuperStar_SE_Handle = 0x1000001F,
                Int_Cursor_Frame = 0x10000020,
                Int_Kinoko_Frame = 0x10000021,
                Int_Thunder_Frame = 0x10000022,
                Int_Scaling_Status = 0x10000023,
                Int_Scaling_Kind = 0x10000024,
                Int_Metal_Frame = 0x10000025,
                Int_No_Heal_Frame = 0x10000026,
                Int_No_Water_InOut_Frame = 0x10000027,
                Int_Dead_Reason = 0x10000028,
                Int_Dead_Mode = 0x10000029,
                Int_Dead_Rebirth_Wait_Frame = 0x1000002A,
                Int_Auto_Heal_Count = 0x1000002B, // TODO: Verify
                Int_Succeed_Hit_Count = 0x1000002C,
                Int_Loupe_Frame = 0x1000002D,
                Int_Curry_SE_Handle = 0x1000002E,
                Int_Heart_Swap_Target_Entry_Id = 0x1000002F,
                Int_Heart_Swap_Item_Id = 0x10000030,
                Int_No_Final_Frame = 0x10000031, // TODO: Verify
                Int_Heal_Eff_Id = 0x10000032,
                Int_Catch_Motion_Offset = 0x10000033, // TODO: Verify
                Int_Thrown_Motion_Offset = 0x10000034, // TODO: Verify
                Int_Attack_Serial_Id = 0x10000035,
                Int_Color = 0x10000036,
                Int_Status_Start_Turn_Frame = 0x10000037,
                Int_Damage_Reaction_Frame = 0x10000038,
                Int_Meteor_Counter_Frame = 0x10000039,
                Int_Badge_Stop_Frame = 0x1000003A, // TODO: Verify
                Int_Screw_Jump_Count = 0x1000003B,
                Int_No_Pickup_Item_Frame = 0x1000003C, // TODO: Verify
                Int_Fly_Reflect_Count = 0x1000003D,
                Int_Air_Lasso_Count = 0x1000003E,
                Int_Damage_Entry_Id = 0x1000003F,
            };
            enum Float {
                Float_Landing_Frame = 0x11000000,
                Float_Fall_X_Accel_Mul = 0x11000001,
                Float_Wall_Jump_Dir = 0x11000002,
                Float_Guard_Shield = 0x11000003,
                Float_Guard_Shield_Min = 0x11000004, // TODO: Verify
                Float_Guard_Shield_Max = 0x11000005, // TODO: Verify
                Float_Flower_Total_Damage = 0x11000006,
                Float_Gekikara_Angle = 0x11000007,
                Float_Gekikara_Angle_Speed = 0x11000008,
                Float_Scaling_Start_Scale = 0x11000009,
                Float_Scaling_End_Scale = 0x1100000A,
                Float_Scaling_Init_Scale = 0x1100000B,
                Float_Metal_Power = 0x1100000C,
                Float_Succeed_Hit_Damage = 0x1100000D,
                Float_Reaction_Cheer = 0x1100000E,
                Float_Damage_Speed_Reserved_X = 0x1100000F,   // TODO: Verify (set in ftKineticTransactor::changeKinetic)
                Float_Damage_Speed_Reserved_Y = 0x11000010,   // TODO: Verify
                Float_Init_Pitch = 0x11000011,
                Float_Cursor_Offset_Y = 0x11000012,
            };
            enum Flag {
                Flag_Dead_End = 0x12000000,
                Flag_No_Dead = 0x12000001,
                Flag_Catch_Cliff = 0x12000002,
                Flag_Disable_Landing_Cancel = 0x12000003, // TODO: Verify
                Flag_No_Pickup_Item = 0x12000004,
                Flag_Tread_No_Trigger = 0x12000005,
                Flag_Final = 0x12000006,
                Flag_Final_Status = 0x12000007,
                Flag_Final_Available = 0x12000008,
                Flag_Flower = 0x12000009,
                Flag_Gekikara = 0x1200000A,
                Flag_Hammer = 0x1200000B,
                Flag_Hammer_No_Attack = 0x1200000C,
                Flag_Hammer_No_Drift = 0x1200000D,
                Flag_Star = 0x1200000E,
                Flag_Screw = 0x1200000F,
                Flag_Pikmin_Final_No_Reaction = 0x12000010, // TODO: Verify
                Flag_Paralyze_Damage = 0x12000011,
                Flag_Metal = 0x12000012,
                Flag_Rabbit_Cap = 0x12000013,
                Flag_Kinoko = 0x12000014,
                Flag_Thunder = 0x12000015,
                Flag_No_Glide = 0x12000016, // TODO: Verify
                Flag_Dead_Area_Out = 0x12000017,
                Flag_KnockOut = 0x12000018,
                Flag_Loupe = 0x12000019,
                Flag_Loupe_Damage = 0x1200001A,
                Flag_Cursor = 0x1200001B,
                Flag_Name_Cursor = 0x1200001C,
                Flag_Rebirth_No_Move = 0x1200001D,
                Flag_Final_Discretion = 0x1200001E,
                Flag_Kirby_Copy_Dedede = 0x1200001F,
                Flag_Speed_Damage = 0x12000020,
                Flag_Disable_Scaling = 0x12000021,
                Flag_Disable_Cliff_Catch = 0x12000022,
                Flag_Rebirth_Adventure = 0x12000023,
                Flag_Disable_Ottotto = 0x12000024,
                Flag_Disable_Slip = 0x12000025,
                Flag_Slow = 0x12000026,
                Flag_Slow_Cause_Timer = 0x12000027,
                Flag_Whole_Slow = 0x12000028,
                Flag_No_Dead_Up = 0x12000029,
                Flag_Item_Throw_4 = 0x1200002A,
                Flag_Assist = 0x1200002B,
                Flag_Check_Catch = 0x1200002C,
                Flag_Cracker_Launcher = 0x1200002D,
                Flag_Sub_Fighter = 0x1200002E,
                Flag_No_Swim = 0x1200002F,
                Flag_Disable_Curry_Shot = 0x12000030,
                Flag_Disable_Interrupt_Swim = 0x12000031,
                Flag_Disable_Interrupt_Scaling = 0x12000032,
                Flag_Voice_Mute = 0x12000033,
                Flag_Enable_Warp_On_Damage = 0x12000034,
                Flag_Hit_Reflector = 0x12000035,
                Flag_Inhaled = 0x12000036,
                Flag_Paralyze_Stop = 0x12000037,
                Flag_Calc_Cursor_Pos_Force = 0x12000038,
                Flag_No_Speed_Operation_Chk = 0x12000039, // TODO: Verify
                Flag_Force_Loupe = 0x1200003A, // TODO: Verify
                Flag_Capture_Yoshi = 0x1200003B,
                Flag_Cursor_On_Posture = 0x1200003C,
            };
        };
    };

    struct Scaling {
        enum Status {
            Status_None = 0x0,
            Status_End_Small = 0x1,
            Status_End_Big = 0x2,
            Status_Big = 0x3,
            Status_To_Big = 0x4,
            Status_Small = 0x5,
            Status_To_Small = 0x6,
        };

        enum Kind {
            Kind_None = -0x1,
            Kind_Status = 0x0,
            Kind_Kinoko = 0x1,
            Kind_Thunder = 0x2,
        };

        enum Type {
            Type_None = -0x1,
            Type_Big = 0x0,
            Type_Small = 0x1,
        };
    };

    struct Dead {
        enum Reason {
            Reason_Invalid = -0x1,
            Reason_Outside_Up = 0x0,
            Reason_Outside_Down = 0x1,
            Reason_Outside_Left = 0x2,
            Reason_Outside_Right = 0x3,
            Reason_Ground_Crush = 0x4,
            Reason_KnockOut = 0x5,
            Reason_Knockout_Explode = 0x6,
            Reason_Instant_Death = 0x6,
            Reason_KnockOut_SelfDestruct = 0x7,
        };

        enum Mode {
            Mode_Normal = 0x0,
            Mode_DeadUp_Star = 0x1,
            Mode_DeadUp_Fall = 0x2
        };
    };

    int m_entryId;
    char _272[44];
    ftOutsideEventPresenter m_outsideEventPresenter;
    char _332[72];

    Fighter(s32 entryId, ftKind kind, Heaps::HeapType instHeap, soModuleAccesser* acc);

    virtual void processUpdate();
    virtual void processFixPosition();
    virtual void processHit();
    virtual void processFixCamera();
    virtual void processEnd();
    virtual ~Fighter();

    virtual Input* getInput();
    virtual soKind soGetKind();
    virtual int soGetSubKind();
    virtual bool checkTransitionStatus(u32);
    virtual bool isTreadPassive();
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual void updateRoughPos();

    // TODO: Verify parameters
    virtual void postCreate();
    virtual Fighter* getPartner();
    virtual void attachInstance();
    virtual void detachInstance();
    virtual void standbyAdvFollow();
#ifdef MATCHING
    virtual void onStartFinal();
#else
    virtual void onStartFinal(int variantID = -1, itCustomizerInterface** customizer = NULL); // Note: Optional parameters for modding purposes to use custom customizers
#endif
    virtual void onEndFinal();
    virtual void toDead(Dead::Reason deadReason);
    virtual int checkDead();
    virtual void onDeadEnd();
    virtual void toKnockOut();
    virtual void activate();
    virtual void onActivate();
    virtual void onDeactivate();
    virtual void onStart(int);
    virtual void postStart(int);
    virtual void setCursor(bool);
    virtual void setNameCursor(bool);
    virtual void setLoupe(bool);
    virtual void setLoupeDamage(bool);
    virtual u32 getChangeSucceedOption();
    virtual void changeSucceedCore(void*, int);
    virtual void setupChangeSucceedWork(void*);
    virtual bool setupChangeSucceedEffect();
    virtual void change(void*, int);
    virtual void touchItem(soLinkTouchItemEventArgs*);
    virtual bool setMetal(bool setStatus, float health, int unk3);
    virtual void onSetMetal(bool);
    virtual void onHitReflector(soModuleAccesser* moduleAccesser, bool);
    virtual void dropItemCheck(soDamage *, bool);
    virtual bool isHeartSwapEnableCondition();
    virtual void analyzeSeal(void*);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionAttackFighter(void* unk, soModuleAccesser* moduleAccesser);
    virtual ftOwner* getOwner();
    virtual ftKind getFtKind();
    virtual bool isInclude(float* rect, Vec3f* out);
    virtual void eatItem(soLinkTouchItemEventArgs *);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual void notifyEventCollisionShield(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionShieldSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionShieldCheck();
    virtual void notifyEventCollisionReflector(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionReflectorSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionReflectorCheck();
    virtual void notifyEventCollisionAbsorber(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual bool notifyEventCollisionAbsorberCheck();
    virtual bool notifyEventCaptureStatus(soModuleAccesser* moduleAccesser, int taskId, int, int);
    virtual void notifyEventCollisionSearch(soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionSearchCheck();
    virtual void notifyEventChangeCollisionHit(int index, soModuleAccesser* moduleAccesser);
    virtual void notifyEventOnDamage(soDamage* damage, bool, soModuleAccesser* moduleAccesser);
    virtual void notifyEventAddDamage(soDamage* damage, soModuleAccesser* moduleAccesser);
    virtual void setTeam(int, int);
    virtual void setVisibility(int);
    virtual void notifyEventTurn(float, float, soModuleAccesser* moduleAccesser);
    virtual bool notifyHaveItemPreCheck(BaseItem* item, bool*);
    virtual void notifyHaveItem(itParam::SizeKind, BaseItem* item, u32 nodeIndex, u32 index, bool);
    virtual void notifyAttachItem(BaseItem* item, u32 nodeIndex, u32 attachNodeIndex, bool, bool);
    virtual void notifyUseItem(BaseItem* item, u32 nodeIndex, int*);
    virtual void notifyThrowItem(BaseItem* item, u32 nodeIndex, int*);
    virtual void notifyDropItem(BaseItem*);
    virtual void notifyShootBulletItem(BaseItem* item);
    virtual void notifyEjectItem(BaseItem* item, u32 index, bool);
    virtual void notifyEjectAttachItem(BaseItem* item, u32 index, bool);
    virtual void notifyVisibilityItem(BaseItem* item, int, bool, u8);
    virtual void notifyEventSetDamage(float);
    virtual void notifyEventChangeAdvUnit();
    virtual void notifyEventBeat();
    virtual void playEatSE();
    virtual void onInhaled();
    virtual bool isInhaled();
    virtual void offInhaled();
    virtual void notifyEventPikminFinalAttack(float, int);
    virtual void trainerStart(float, Vec3f*, Vec3f*, int, bool);
    virtual void trainerRestart(float*, bool, bool);
    virtual void disappear(bool);
    virtual bool isEnableCancel();
    virtual void* getCancelModule();
    virtual void* getStatusGimmickUniqProcessPool();
    virtual void* getVirtualNodeMatrixPool();

    void start(Vec3f* pos, float lr, float damage, int, bool);
    void setCurry(bool setStatus, int unk2);
    void setHammer(bool setStatus, int unk2);
    void setSuperStar(bool setStatus, int duration, bool);
    void setFlower(bool setStatus, float rate, float size, int unk4, bool unk5);
    void setSlow(bool setStatus, int slowStrength, int duration, bool useTimerEffect);
    void setHeartSwap(int givingPlayerEntryID, int givingPlayerEntryId, bool setStatus);
    void startScaling(Scaling::Kind, Scaling::Type);
    void warp(Vec3f* pos, float lr, u32 showEffect);
    void setupEquipment();
};
static_assert(sizeof(Fighter) == 404, "Class is wrong size!");

struct ftLinkDeadEventArgs : public soLinkEventArgs {
    Fighter::Dead::Reason m_deadReason;

    inline ftLinkDeadEventArgs(Fighter::Dead::Reason deadReason) : soLinkEventArgs(StageObject::Link::Event_Dead), m_deadReason(deadReason) {}
};
static_assert(sizeof(ftLinkDeadEventArgs) == 0xc, "Class is wrong size!");
