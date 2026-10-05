#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// TODO: identify the special moves the ExtendParam groups are for
// TODO: Match without the const_cast hack (the Cast accessors load the group pointer again)
// TODO: UBFIX endianness

class ftLucarioExtendParamAccesser : public ftExtendParamAccesserEx<3999, 52, 23999, 6> {
    const u8* group1(const u8* base) { return *(const u8* const*)(base + 0x7C); }
    const u8* group1Cast(const u8* base) { return *(const u8**)(base + 0x7C); }
    const u8* group2(const u8* base) { return *(const u8* const*)(base + 0x80); }
    const u8* group2Cast(const u8* base) { return *(const u8**)(base + 0x80); }
    const u8* group3(const u8* base) { return *(const u8* const*)(base + 0x84); }
    const u8* group3Cast(const u8* base) { return *(const u8**)(base + 0x84); }
    const u8* group4(const u8* base) { return *(const u8* const*)(base + 0x88); }
    const u8* group4Cast(const u8* base) { return *(const u8**)(base + 0x88); }
    const u8* group5(const u8* base) { return *(const u8* const*)(base + 0x8C); }
    const u8* group5Cast(const u8* base) { return *(const u8**)(base + 0x8C); }
    const u8* group6(const u8* base) { return *(const u8* const*)(base + 0x90); }
    const u8* group6Cast(const u8* base) { return *(const u8**)(base + 0x90); }
    const u8* group7(const u8* base) { return *(const u8* const*)(base + 0x94); }
    const u8* group7Cast(const u8* base) { return *(const u8**)(base + 0x94); }
    const u8* group8(const u8* base) { return *(const u8* const*)(base + 0x98); }
    const u8* group8Cast(const u8* base) { return *(const u8**)(base + 0x98); }

public:
    ftLucarioExtendParamAccesser() : ftExtendParamAccesserEx(Fighter_Lucario) { }
    virtual ~ftLucarioExtendParamAccesser() { }

    virtual void setup(const u8* extData) {
        for (s32 i = 0; i < NumVariations; i++) {
            m_floats[i][0] = (const float*)(group1(extData) + 0x4);
            m_floats[i][1] = (const float*)(group1(extData) + 0x8);
            m_floats[i][2] = (const float*)(group1(extData) + 0xC);
            m_floats[i][3] = (const float*)(group1(extData) + 0x14);
            m_floats[i][4] = (const float*)(group1(extData) + 0x18);
            m_floats[i][5] = (const float*)(group1(extData) + 0x1C);
            m_floats[i][6] = (const float*)(group2Cast(extData) + 0x0);
            m_floats[i][7] = (const float*)(group2(extData) + 0x4);
            m_floats[i][8] = (const float*)(group2(extData) + 0x8);
            m_floats[i][9] = (const float*)(group2(extData) + 0xC);
            m_floats[i][10] = (const float*)(group3Cast(extData) + 0x0);
            m_floats[i][11] = (const float*)(group3(extData) + 0x4);
            m_floats[i][12] = (const float*)(group3(extData) + 0x8);
            m_floats[i][13] = (const float*)(group3(extData) + 0xC);
            m_floats[i][14] = (const float*)(group3(extData) + 0x10);
            m_floats[i][15] = (const float*)(group3(extData) + 0x14);
            m_floats[i][16] = (const float*)(group3(extData) + 0x18);
            m_floats[i][17] = (const float*)(group3(extData) + 0x1C);
            m_floats[i][18] = (const float*)(group4Cast(extData) + 0x0);
            m_floats[i][19] = (const float*)(group4(extData) + 0x4);
            m_floats[i][20] = (const float*)(group4(extData) + 0x8);
            m_floats[i][21] = (const float*)(group4(extData) + 0xC);
            m_floats[i][22] = (const float*)(group4(extData) + 0x10);
            m_floats[i][23] = (const float*)(group4(extData) + 0x14);
            m_floats[i][24] = (const float*)(group5Cast(extData) + 0x0);
            m_floats[i][25] = (const float*)(group5(extData) + 0x4);
            m_floats[i][26] = (const float*)(group5(extData) + 0x8);
            m_floats[i][27] = (const float*)(group5(extData) + 0xC);
            m_floats[i][28] = (const float*)(group5(extData) + 0x10);
            m_floats[i][29] = (const float*)(group5(extData) + 0x14);
            m_floats[i][30] = (const float*)(group5(extData) + 0x18);
            m_floats[i][31] = (const float*)(group5(extData) + 0x1C);
            m_floats[i][32] = (const float*)(group5(extData) + 0x24);
            m_floats[i][33] = (const float*)(group5(extData) + 0x28);
            m_floats[i][34] = (const float*)(group5(extData) + 0x2C);
            m_floats[i][35] = (const float*)(group5(extData) + 0x30);
            m_floats[i][36] = (const float*)(group5(extData) + 0x38);
            m_floats[i][37] = (const float*)(group6Cast(extData) + 0x0);
            m_floats[i][38] = (const float*)(group6(extData) + 0x4);
            m_floats[i][39] = (const float*)(group6(extData) + 0x8);
            m_floats[i][40] = (const float*)(group6(extData) + 0x10);
            m_floats[i][41] = (const float*)(group6(extData) + 0x14);
            m_floats[i][42] = (const float*)(group7Cast(extData) + 0x0);
            m_floats[i][43] = (const float*)(group7(extData) + 0x4);
            m_floats[i][44] = (const float*)(group7(extData) + 0x8);
            m_floats[i][45] = (const float*)(group8Cast(extData) + 0x0);
            m_floats[i][46] = (const float*)(group8(extData) + 0x4);
            m_floats[i][47] = (const float*)(group8(extData) + 0x8);
            m_floats[i][48] = (const float*)(group8(extData) + 0xC);
            m_floats[i][49] = (const float*)(group8(extData) + 0x10);
            m_floats[i][50] = (const float*)(group8(extData) + 0x14);
            m_floats[i][51] = (const float*)(group8(extData) + 0x18);
            m_ints[i][0] = (const int*)(group1Cast(extData) + 0x0);
            m_ints[i][1] = (const int*)(group1(extData) + 0x10);
            m_ints[i][2] = (const int*)(group5(extData) + 0x20);
            m_ints[i][3] = (const int*)(group5(extData) + 0x34);
            m_ints[i][4] = (const int*)(group6(extData) + 0xC);
            m_ints[i][5] = (const int*)(group6(extData) + 0x18);
        }
    }
};

extern ftLucarioExtendParamAccesser g_ftLucarioExtendParamAccesser;
