#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

struct ecTrace {
    u8 unk0[0x1C];
    ecTrace* m_prev;
    ecTrace* m_next;
    u32 m_id;
    u32 unk28;
    u32 unk2C;
    u8 unk30[0x1C];
    Vec3f unk4C;
    Vec3f unk58;
    Vec3f unk64;
    u8 unk70[0x4];
    float unk74;
    u8 unk78[0xC];
    ~ecTrace();
    bool update_just();
    void update_odd(float p1);
    void renderXlu();

    ecTrace(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7);
    ecTrace(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6);
    void end(u32 p1, u32 p2);
    void pause(bool p1);
};
static_assert(sizeof(ecTrace) == 0x84, "Class is the wrong size!");
