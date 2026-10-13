#pragma once

#include <StaticAssert.h>
#include <types.h>

struct grFixedPath {
    struct UnkClass {
        u8 unk0[0xC];
    };
    static_assert(sizeof(UnkClass) == 0xC, "Class is the wrong size!");

    u16 m_offsetToNextEntry;
    UnkClass* m_data;
    u8 unk8[0x38];
};
static_assert(sizeof(grFixedPath) == 0x40, "Class is the wrong size!");

class grFixedPathCollection {
    u32 m_count;
    grFixedPath* m_paths;
    u8 unk8[0x18];
    grFixedPath m_pathData[]; // UBFIX: C99 flexible array member
public:
    void relocation();
};
// TODO size assertion
