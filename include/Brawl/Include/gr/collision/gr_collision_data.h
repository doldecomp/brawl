#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

class grCollData {
public:
    struct VtxData {
        Vec2f m_pos;
    };

    struct JointData {
        char _spacer[0x4C];
        const char m_name[0x20]; // +0x4C
    };

    struct LineData {
        short m_pointX;
        short m_pointY;
        char _spacer[12];
    };

    u16 m_vtxLen;
    short m_lineLen;
    short m_jointLen;
    short m_unk1;
    VtxData* m_vtxDatas;
    LineData* m_lineDatas;
    JointData* m_jointDatas;
    u8 unk14[0x14];

    const char* getJointNodeName(u32 nodeIndex);
};
static_assert(sizeof(grCollData) == 0x28, "Class is wrong size!");
