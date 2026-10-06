#pragma once
#include <StaticAssert.h>
#include <types.h>

// Local copy declaration for templates; preserves the SDK field names and size.
class soTransitionTerm {
public:
    u8 m_flags;
    // MATCH-ONLY: the unsigned target field is copied through its signed view.
    union { u16 m_targetKind; s16 unk2; };
    s16 m_generalTermIndex;
    u16 unk6; // HYPOTHESIS: trailing padding, excluded from assignment.
    soTransitionTerm& operator=(const soTransitionTerm& other);
};
static_assert(sizeof(soTransitionTerm) == 8, "Class is wrong size!");
