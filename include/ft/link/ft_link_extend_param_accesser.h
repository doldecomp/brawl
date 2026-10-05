#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// TODO: identify the special moves the ExtendParam groups are for
// TODO: Match without the const_cast hack (the Cast accessors load the group pointer again)
// TODO: UBFIX endianness

class ftLinkExtendParamAccesser : public ftExtendParamAccesserEx<3999, 20, 23999, 5> {
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

public:
    ftLinkExtendParamAccesser() : ftExtendParamAccesserEx(Fighter_Link) { }
    virtual ~ftLinkExtendParamAccesser() { }

    virtual void setup(const u8* extData) {
        for (s32 i = 0; i < NumVariations; i++) {
            m_floats[i][0] = (const float*)(group1Cast(extData) + 0x0);
            m_floats[i][1] = (const float*)(group1(extData) + 0x4);
            m_floats[i][2] = (const float*)(group1(extData) + 0x8);
            m_floats[i][3] = (const float*)(group1(extData) + 0xC);
            m_floats[i][4] = (const float*)(group2(extData) + 0x4);
            m_floats[i][5] = (const float*)(group3Cast(extData) + 0x0);
            m_floats[i][6] = (const float*)(group3(extData) + 0x4);
            m_floats[i][7] = (const float*)(group3(extData) + 0x8);
            m_floats[i][8] = (const float*)(group3(extData) + 0xC);
            m_floats[i][9] = (const float*)(group3(extData) + 0x10);
            m_floats[i][10] = (const float*)(group4Cast(extData) + 0x0);
            m_floats[i][11] = (const float*)(group4(extData) + 0x4);
            m_floats[i][12] = (const float*)(group5Cast(extData) + 0x0);
            m_floats[i][13] = (const float*)(group5(extData) + 0x4);
            m_floats[i][14] = (const float*)(group5(extData) + 0xC);
            m_floats[i][15] = (const float*)(group5(extData) + 0x14);
            m_floats[i][16] = (const float*)(group6Cast(extData) + 0x0);
            m_floats[i][17] = (const float*)(group7Cast(extData) + 0x0);
            m_floats[i][18] = (const float*)(group7(extData) + 0x4);
            m_floats[i][19] = (const float*)(group7(extData) + 0x8);
            m_ints[i][0] = (const int*)(group2Cast(extData) + 0x0);
            m_ints[i][1] = (const int*)(group3(extData) + 0x14);
            m_ints[i][2] = (const int*)(group5(extData) + 0x8);
            m_ints[i][3] = (const int*)(group5(extData) + 0x10);
            m_ints[i][4] = (const int*)(group6(extData) + 0x4);
        }
    }
};

extern ftLinkExtendParamAccesser g_ftLinkExtendParamAccesser;
