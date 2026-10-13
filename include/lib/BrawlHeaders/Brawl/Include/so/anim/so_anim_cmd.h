#pragma once

#include <StaticAssert.h>
#include <types.h>

class soAnimCmdArgument;
class soAnimCmd;

// Variable Data Type
#define ANIM_CMD_INT 0
#define ANIM_CMD_FLOAT 1
#define ANIM_CMD_BOOL 2 

// Variable Memory Type
#define ANIM_CMD_VAR_TYPE_IC 0
#define ANIM_CMD_VAR_TYPE_LA 1
#define ANIM_CMD_VAR_TYPE_RA 2

enum soAnimCmdArgumentType {
    AnimCmd_Arg_Type_Int = 0,
    AnimCmd_Arg_Type_Scalar = 1,
    AnimCmd_Arg_Type_Ptr = 2,
    AnimCmd_Arg_Type_Bool = 3,
    AnimCmd_Arg_Type_File = 4,
    AnimCmd_Arg_Type_Variable = 5,
    AnimCmd_Arg_Type_Requirement = 6
};

class soAnimCmdArgument {
public:
    soAnimCmdArgumentType m_varType;
    u32 m_rawValue;
};
static_assert(sizeof(soAnimCmdArgument) == 0x8, "Class is the wrong size!");

class soAnimCmd {
public:
    char m_module;
    char m_code;
    char m_argCount;
    char m_option;
    soAnimCmdArgument *m_args; // ptr to array
};
static_assert(sizeof(soAnimCmd) == 0x8, "Class is the wrong size!");

struct soAnimCmdAddressPack {
    u32 unk0;
    u32 unk4;
    u32 unk8;

    soAnimCmdAddressPack& operator=(const soAnimCmdAddressPack& orig) {
        if (this != &orig) {
            u32 addr3 = orig.unk8;
            u32 addr2 = orig.unk4;
            u32 addr1 = orig.unk0;
            unk0 = addr1;
            unk4 = addr2;
            unk8 = addr3;
        }
        return *this;
    }
};
static_assert(sizeof(soAnimCmdAddressPack) == 0xc, "Class is the wrong size!");
