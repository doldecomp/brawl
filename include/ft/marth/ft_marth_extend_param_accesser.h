#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// TODO: identify the special moves these ExtendParam classes are for

struct ftMarthExtendParamClass1 {
    int unk0;
    int unk4;
    int unk8;
    float unkC;
    float unk10;
};

struct ftMarthExtendParamClass2 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
};

struct ftMarthExtendParamClass3 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    float unk20;
};

struct ftMarthExtendParamClass4 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    int unk18;
    float unk1C;
    float unk20;
    float unk24;
};

struct ftMarthExtendParamClass5 {
    int unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
};

struct ftMarthExtendParamClass5Int {
    int v[5];
};

struct ftMarthExtendParamClass6 {
    float unk0;
    float unk4;
    float unk8;
};

// TODO: Match without the const_cast hack
// TODO: UBFIX endianness

class ftMarthExtendParamAccesser : public ftExtendParamAccesserEx<3999, 31, 23999, 8> {
    static const u32 OffsetExt4 = 0x88;
    static const u32 OffsetExt5 = 0x8C;
    static const u32 OffsetExt6 = 0x90;

    const ftMarthExtendParamClass1* group1(const u8* base) {
        return *(ftMarthExtendParamClass1* const*)(base + OffsetExt1);
    }
    const ftMarthExtendParamClass1* group1Cast(const u8* base) {
        return *(ftMarthExtendParamClass1**)(base + OffsetExt1);
    }
    const ftMarthExtendParamClass2* group2(const u8* base) {
        return *(ftMarthExtendParamClass2* const*)(base + OffsetExt2);
    }
    const ftMarthExtendParamClass2* group2Cast(const u8* base) {
        return *(ftMarthExtendParamClass2**)(base + OffsetExt2);
    }
    const ftMarthExtendParamClass3* group3(const u8* base) {
        return *(ftMarthExtendParamClass3* const*)(base + OffsetExt3);
    }
    const ftMarthExtendParamClass3* group3Cast(const u8* base) {
        return *(ftMarthExtendParamClass3**)(base + OffsetExt3);
    }
    const ftMarthExtendParamClass4* group4(const u8* base) {
        return *(ftMarthExtendParamClass4* const*)(base + OffsetExt4);
    }
    const ftMarthExtendParamClass4* group4Cast(const u8* base) {
        return *(ftMarthExtendParamClass4**)(base + OffsetExt4);
    }
    const ftMarthExtendParamClass5* group5(const u8* base) {
        return *(ftMarthExtendParamClass5* const*)(base + OffsetExt5);
    }
    const ftMarthExtendParamClass5* group5Cast(const u8* base) {
        return *(ftMarthExtendParamClass5**)(base + OffsetExt5);
    }
    const ftMarthExtendParamClass5Int* group5Int(const u8* base) {
        return *(ftMarthExtendParamClass5Int* const*)(base + OffsetExt5);
    }
    const ftMarthExtendParamClass6* group6(const u8* base) {
        return *(ftMarthExtendParamClass6* const*)(base + OffsetExt6);
    }
    const ftMarthExtendParamClass6* group6Cast(const u8* base) {
        return *(ftMarthExtendParamClass6**)(base + OffsetExt6);
    }

public:
    ftMarthExtendParamAccesser() : ftExtendParamAccesserEx(Fighter_Marth) { }
    virtual ~ftMarthExtendParamAccesser() { }

    virtual void setup(const u8* extData) {
        for (s32 i = 0; i < NumVariations; i++) {
            m_floats[i][0] = &group1(extData)->unkC;
            m_floats[i][1] = &group1(extData)->unk10;

            m_floats[i][2] = &group2Cast(extData)->unk0;
            m_floats[i][3] = &group2(extData)->unk4;
            m_floats[i][4] = &group2(extData)->unk8;
            m_floats[i][5] = &group2(extData)->unkC;
            m_floats[i][6] = &group2(extData)->unk10;

            m_floats[i][7] = &group3Cast(extData)->unk0;
            m_floats[i][8] = &group3(extData)->unk4;
            m_floats[i][9] = &group3(extData)->unk8;
            m_floats[i][10] = &group3(extData)->unkC;
            m_floats[i][11] = &group3(extData)->unk10;
            m_floats[i][12] = &group3(extData)->unk14;
            m_floats[i][13] = &group3(extData)->unk18;
            m_floats[i][14] = &group3(extData)->unk1C;
            m_floats[i][15] = &group3(extData)->unk20;

            m_floats[i][16] = &group4Cast(extData)->unk0;
            m_floats[i][17] = &group4(extData)->unk4;
            m_floats[i][18] = &group4(extData)->unk8;
            m_floats[i][19] = &group4(extData)->unkC;
            m_floats[i][20] = &group4(extData)->unk10;
            m_floats[i][21] = &group4(extData)->unk14;
            m_floats[i][22] = &group4(extData)->unk1C;
            m_floats[i][23] = &group4(extData)->unk20;
            m_floats[i][24] = &group4(extData)->unk24;

            m_floats[i][25] = &group5(extData)->unk4;
            m_floats[i][26] = &group5(extData)->unk8;
            m_floats[i][27] = &group5(extData)->unkC;
            m_floats[i][28] = &group5(extData)->unk10;

            m_floats[i][29] = &group6Cast(extData)->unk0;
            m_floats[i][30] = &group6(extData)->unk8;

            m_ints[i][0] = &group1Cast(extData)->unk0;
            m_ints[i][1] = &group1(extData)->unk4;
            m_ints[i][2] = &group1(extData)->unk8;
            m_ints[i][3] = &group4(extData)->unk18;
            m_ints[i][4] = &group5Cast(extData)->unk0;
            m_ints[i][5] = (const int*)((const u8*)group5(extData) + 4);
            m_ints[i][6] = (const int*)((const u8*)group5(extData) + 0xC);
            m_ints[i][7] = (const int*)((const u8*)group5(extData) + 0x10);
        }
    }
};

extern ftMarthExtendParamAccesser g_ftMarthExtendParamAccesser;
