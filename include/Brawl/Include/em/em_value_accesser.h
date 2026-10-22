#include <StaticAssert.h>
#include <types.h>
#include <so/so_value_accesser.h>
#include <it/em_archive.h>

class emValueAccesser : public soValueAccesser {
public:
    enum ParamFloat {

    };

    enum ParamInt {


    };

    enum ParamIndefinite {


    };

    enum VariableFloat {
        Var_Float_Sum_Speed = 1000,
        Var_Float_Kinetic_Angle_From_Speed = 1001,

        Var_Float_HP_Rest_Rate = 1026,
        Var_Float_Kinetic_Speed_Angle_With_Touch_Ground = 1027,
        Var_Float_Goal_Pos_X = 1028,
        Var_Float_Goal_Pos_Y = 1029,

        Var_Float_HP_Diff_From_Prev_HP = 1048,
        Var_Float_Kinetic_Reflect_Num_Add_Value = 1049,

        Var_Float_Center_Pos_X = 1051,
        Var_Float_Center_Pos_Y = 1052,
        Var_Float_Parent_Enemy_Strength = 1053,
    };

    enum VariableInt {
        Var_Int_Frame_Counter_1 = 21000,
        Var_Int_Frame_Counter_2 = 21001,
        Var_Int_Frame_Counter_3 = 21002,

        Var_Int_Enemy_Kind = 21007,
        Var_Int_Frame_Counter_4 = 21008,
        Var_Int_Connected_Trigger_Id = 21009,
        Var_Int_Level = 21010,
        Var_Int_Communication_Item_Port_Data = 21011,
        Var_Int_Parent_Enemy_Status_Kind = 21012,
        Var_Int_Communication_Item_Situation_Kind = 21013,
    };

    enum VariableIndefinite {
        Var_Indefinite_Motion_Path = 41000,
    };

    virtual soParamAccesser* getExtendParamAccesser();
    virtual ~emValueAccesser();
    virtual float getConstantFloatCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual int getConstantIntCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual void* getConstantIndefiniteCore(soModuleAccesser* moduleAccesser, u32, u32);

    virtual float getVariableFloatCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual int getVariableIntCore(soModuleAccesser* moduleAccesser, u32, u32);
    virtual void* getVariableIndefiniteCore(soModuleAccesser* moduleAccesser, u32, u32);

};
