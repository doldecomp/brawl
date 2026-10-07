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


// MATCH-ONLY: Default value records clear the two element fields before the ID.
// Keep the element type an aggregate so its verified bulk copy is unchanged.
template<class T> class soInstanceUnit;
template<>
class soInstanceUnit<soAnimCmdControlUnit> {
public:
    soAnimCmdControlUnit m_element;
    int m_id;

    soInstanceUnit() {
        m_element.m_animCmdInterpreter = nullptr;
        m_element.m_animCmdAddressPackArraySeparate = nullptr;
        m_id = -1;
    }
    soInstanceUnit(soAnimCmdControlUnit& elm, s32 id) :
        m_element(elm), m_id(id) { }
};
static_assert(sizeof(soInstanceUnit<soAnimCmdControlUnit>) == 12, "Instance unit is wrong size!");
