#pragma once
#include <StaticAssert.h>
#include <ac/ac_anim_cmd_impl.h>

// Motion transition identifier and its animation-command arguments.
// The argument-list type is verified by the Sonic dash constructor and RTTI.
struct soTransitionTermPack {
    u32 unk0;
    acCmdArgList unk4;
};
static_assert(sizeof(soTransitionTermPack) == 20, "Class is wrong size!");
