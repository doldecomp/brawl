#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/so_module_accesser.h>
#include <types.h>

class soParamAccesser : private soNull, public soNullable {
public:
    virtual ~soParamAccesser() { }
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
};

class soParamAccesserNull : public soParamAccesser {
public:
    virtual ~soParamAccesserNull();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0);
};

extern soParamAccesserNull g_soParamAccesserNull;

class soValueAccesser {
public:

    enum ParamFloat {
        Common_Param_Float_Damage_Frame_Mul = 2002,
        Common_Param_Float_Damage_Level_1 = 2003,
        Common_Param_Float_Damage_Level_2 = 2004,
        Common_Param_Float_Damage_Level_3 = 2005,
        Common_Param_Float_Damage_Angle_Ground_Zero_Speed_Mul = 2006,
        Common_Param_Float_Damage_Angle_Ground_Max = 2007,
        Common_Param_Float_Damage_Angle_Ground_Reaction_Min = 2008,
        Common_Param_Float_Damage_Angle_Ground_Reaction_Max = 2009,
        Common_Param_Float_Damage_Speed_Mul = 2010,
        Common_Param_Float_Damage_Speed_Limit = 2011,
        Common_Param_Float_Damage_Sync_Speed_Mul = 2012,
        Common_Param_Float_Damage_Down_On_Ground_Angle = 2013,
        Common_Param_Float_Damage_Down_On_Ground_Speed_Y_Mul = 2014,
        Common_Param_Float_Fly_Top_Angle_Lw = 2015,
        Common_Param_Float_Fly_Top_Angle_Hi = 2016,
        Common_Param_Float_Fly_Roll_Rate = 2017,
        Common_Param_Float_Hit_Stop_Frame_Max = 2018,
        Common_Param_Float_Hit_Stop_Frame_Mul = 2019,
        Common_Param_Float_Hit_Stop_Frame_Add = 2020,
        Common_Param_Float_Damage_Shake_Mul_Value = 2021,
        Common_Param_Float_Damage_Shake_Add_Value = 2022,

        Common_Param_Float_Down_Damage_Reaction = 2025,
        Common_Param_Float_Down_Damage_S_Reaction = 2026,

        Common_Param_Float_Hit_Stop_Elec_Mul = 2028,
        Common_Param_Float_Hit_Stop_Frame_Paralyze_Max = 2029,
        Common_Param_Float_Hit_Stop_Frame_Paralyze_Mul = 2030,
        Common_Param_Float_Hit_Stop_Frame_Paralyze_Add = 2031,
        Common_Param_Float_Slip_Damage_Reaction = 2032,
        Common_Param_Float_Capture_Cut_Attack_Power = 2033,
        Common_Param_Float_Capture_Cut_Damage = 2034,
        Common_Param_Float_Damage_Fly_Quake_M = 2035,
        Common_Param_Float_Damage_Fly_Quake_L = 2036,
        Common_Param_Float_Rebound_Power_Diff = 2037,
        Common_Param_Float_Rebound_Reaction_Mul = 2038,
        Common_Param_Float_Rebound_Reaction_Add = 2039,
        Common_Param_Float_Rebound_Speed_Mul = 2040,
        Common_Param_Float_Rebound_Speed_Add = 2041,
    };

    enum ParamInt {
        Common_Param_Int_Meteor_Vector_Min = 22001,
        Common_Param_Int_Meteor_Vector_Max = 22002,
        Common_Param_Int_Fly_Roll_Damage = 22003,

        Common_Param_Int_Reflect_Count_Max = 22005,
    };

    enum ParamIndefinite {

    };

    enum VariableFloat {
        Var_Float_Motion_Frame = 0,
        Var_Float_Motion_End_Frame = 1,
        Var_Float_Damage = 2,
        Var_Float_Posture_Pos_X = 3,
        Var_Float_Posture_Pos_Y = 4,
        Var_Float_Posture_Rot_X = 5,
        Var_Float_Posture_Rot_Y = 6,
        Var_Float_Posture_Rot_Z = 7,
        Var_Float_Posture_Lr = 8,
        Var_Float_Posture_Lr_Rv = 9,
        Var_Float_Motion_Other_1_Frame = 10,
        Var_Float_Motion_Other_2_Frame = 11,
        Var_Float_Motion_Other_3_Frame = 12,
        Var_Float_Motion_Other_4_Frame = 13,
        Var_Float_Motion_Other_5_Frame = 14,
        Var_Float_Motion_Other_1_End_Frame = 15,
        Var_Float_Motion_Other_2_End_Frame = 16,
        Var_Float_Motion_Other_3_End_Frame = 17,
        Var_Float_Motion_Other_4_End_Frame = 18,
        Var_Float_Motion_Other_5_End_Frame = 19,
        Var_Float_Posture_Scale = 20,
        Var_Float_Posture_Pos_Z = 21,
        Var_Float_Kinetic_Sum_Speed_X = 22,
        Var_Float_Kinetic_Sum_Speed_Y = 23,
        Var_Float_Motion_Rate = 24,
        Var_Float_Controller_Stick_X = 25,
        Var_Float_Controller_Stick_X_Rv = 26,
        Var_Float_Kinetic_Sum_Speed_X_Abs = 27,
        Var_Float_Kinetic_Sum_Speed_X_Lr = 28,
        Var_Float_Kinetic_Sum_Speed_X_Lr_Rv = 29,
        Var_Float_Camera_Range_Up = 30,
        Var_Float_Camera_Range_Down = 31,
        Var_Float_Camera_Range_Right = 32,
        Var_Float_Camera_Range_Left = 33,
        Var_Float_Dead_Range_Up = 34,
        Var_Float_Dead_Range_Down = 35,
        Var_Float_Dead_Range_Right = 36,
        Var_Float_Dead_Range_Left = 37,
        Var_Float_Damage_Reaction = 38,
        Var_Float_Ground_Down_Friction = 39,
        Var_Float_Ground_Down_Movement_Speed = 40
    };

    enum VariableInt {
        Var_Int_Motion_Kind = 20000,
        Var_Int_Status_Kind = 20001,
        Var_Int_Status_Ground_Correct_Kind = 20002,
        Var_Int_Status_Prev_Kind = 20003,
        Var_Int_Status_Last_Transition_Group_Id = 20004,
        Var_Int_Status_Last_Transition_Unit_Id = 20005,
        Var_Int_Pickable_Item_Size = 20006,
        Var_Int_Pickable_Item_Kind = 20007,
        Var_Int_Have_Item_Size = 20008,
        Var_Int_Have_Item_Kind = 20009,
        Var_Int_Motion_Partial_1_Kind = 20010,
        Var_Int_Motion_Partial_2_Kind = 20011,
        Var_Int_Motion_Other_1_Kind = 20012,
        Var_Int_Motion_Other_2_Kind = 20013,
        Var_Int_Motion_Other_3_Kind = 20014,
        Var_Int_Motion_Other_4_Kind = 20015,
        Var_Int_Motion_Other_5_Kind = 20016,
        Var_Int_Controller_Flick_X = 20017,
        Var_Int_Shoot_Item_Bullet = 20018,
        Var_Int_Have_Item_Hold_Kind = 20019,
        Var_Int_Camera_Quake_Kind = 20020,
        Var_Int_Team_No = 20021,
        Var_Int_Task_Id = 20022,
        Var_Int_Ground_Correct_Kind = 20023,
        Var_Int_Kinetic_Type = 20024,
        Var_Int_Situation_Kind = 20025,
        Var_Int_Stage_Default_Light_Set_Index = 20026,
    };

    virtual soParamAccesser* getExtendParamAccesser();
    virtual ~soValueAccesser();
    virtual float getVariableFloatCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual int getVariableIntCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual void* getVariableIndefiniteCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual float getConstantFloatCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual int getConstantIntCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual void* getConstantIndefiniteCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual bool isControllerValueCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual bool isEnableSpeedOperationCore(soModuleAccesser* moduleAccesser);

    static float getVariableFloat(soModuleAccesser* moduleAccesser, u32, u32);
    static int getVariableInt(soModuleAccesser* moduleAccesser, u32, u32);
    static void* getVariableIndefinite(soModuleAccesser* moduleAccesser, u32, u32);

    static float getConstantFloat(soModuleAccesser* moduleAccesser, u32, u32);
    static int getConstantInt(soModuleAccesser* moduleAccesser, u32, u32);
    static void* getConstantIndefinite(soModuleAccesser* moduleAccesser, u32, u32);

    static float getValueFloat(soModuleAccesser* moduleAccesser, u32, u32);
    static int getValueInt(soModuleAccesser* moduleAccesser, u32, u32);

    static int getValueVariation();
};
