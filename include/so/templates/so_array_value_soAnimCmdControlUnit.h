#pragma once
#include <StaticAssert.h>
#include <types.h>

// Local copy of the two pointer fields established by the SDK shadow header.
class soAnimCmdInterpreter;
class soAnimCmdAddressPackArraySeparate;
class soAnimCmdControlUnit {
public:
    soAnimCmdInterpreter* m_animCmdInterpreter;
    soAnimCmdAddressPackArraySeparate* m_animCmdAddressPackArraySeparate;
};
static_assert(sizeof(soAnimCmdControlUnit) == 8, "Class is wrong size!");
