#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

#pragma once

// TODO: identify the special moves these ExtendParam classes are for

struct ftPurinExtendParamClass1 {
    int unk0;
    int unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    float unk38;
    int unk3C;
    float unk40;
    float unk44;
    float unk48;
    float unk4C;
    float unk50;
    float unk54;
    float unk58;
    float unk5C;
    float unk60;
    float unk64;
    int unk68;
    float unk6C;
    float unk70;
    float unk74;
    float unk78;
    float unk7C;
    float unk80;
    float unk84;
    float unk88;
    float unk8C;
    float unk90;
    float unk94;
    float unk98;
    float unk9C;
    float unkA0;
    float unkA4;
};

struct ftPurinExtendParamClass2 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
};

struct ftPurinExtendParamClass3 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
};

// TODO: Match without the const_cast hack
// TODO: UBFIX endianness

class ftPurinExtendParamAccesser : public ftExtendParamAccesserEx<3999, 49, 24999, 4> {
    const ftPurinExtendParamClass1* group1(const u8* base) {
        return *(ftPurinExtendParamClass1* const*)(base + OffsetExt1);
    }

    const ftPurinExtendParamClass1* group1Cast(const u8* base) {
        return *(ftPurinExtendParamClass1**)(base + OffsetExt1);
    }

    const ftPurinExtendParamClass2* group2(const u8* base) {
        return *(ftPurinExtendParamClass2* const*)(base + OffsetExt2);
    }

    const ftPurinExtendParamClass2* group2Cast(const u8* base) {
        return *(ftPurinExtendParamClass2**)(base + OffsetExt2);
    }

    const ftPurinExtendParamClass3* group3(const u8* base) {
        return *(ftPurinExtendParamClass3* const*)(base + OffsetExt3);
    }

    const ftPurinExtendParamClass3* group3Cast(const u8* base) {
        return *(ftPurinExtendParamClass3**)(base + OffsetExt3);
    }

public:
    ftPurinExtendParamAccesser() : ftExtendParamAccesserEx(Fighter_Jigglypuff) { }
    virtual ~ftPurinExtendParamAccesser() { }

    virtual void setup(const u8* extData) {
        for (s32 i = 0; i < NumVariations; i++) {
            m_floats[i][0] = &group1(extData)->unk8;
            m_floats[i][1] = &group1(extData)->unkC;
            m_floats[i][2] = &group1(extData)->unk10;
            m_floats[i][3] = &group1(extData)->unk14;
            m_floats[i][4] = &group1(extData)->unk18;
            m_floats[i][5] = &group1(extData)->unk1C;
            m_floats[i][6] = &group1(extData)->unk20;
            m_floats[i][7] = &group1(extData)->unk24;
            m_floats[i][8] = &group1(extData)->unk28;
            m_floats[i][9] = &group1(extData)->unk2C;
            m_floats[i][10] = &group1(extData)->unk30;
            m_floats[i][11] = &group1(extData)->unk34;
            m_floats[i][12] = &group1(extData)->unk38;
            m_floats[i][13] = &group1(extData)->unk40;
            m_floats[i][14] = &group1(extData)->unk44;
            m_floats[i][15] = &group1(extData)->unk48;
            m_floats[i][16] = &group1(extData)->unk4C;
            m_floats[i][17] = &group1(extData)->unk50;
            m_floats[i][18] = &group1(extData)->unk54;
            m_floats[i][19] = &group1(extData)->unk58;
            m_floats[i][20] = &group1(extData)->unk5C;
            m_floats[i][21] = &group1(extData)->unk60;
            m_floats[i][22] = &group1(extData)->unk64;
            m_floats[i][23] = &group1(extData)->unk6C;
            m_floats[i][24] = &group1(extData)->unk70;
            m_floats[i][25] = &group1(extData)->unk74;
            m_floats[i][26] = &group1(extData)->unk78;
            m_floats[i][27] = &group1(extData)->unk7C;
            m_floats[i][28] = &group1(extData)->unk80;
            m_floats[i][29] = &group1(extData)->unk84;
            m_floats[i][30] = &group1(extData)->unk88;
            m_floats[i][31] = &group1(extData)->unk8C;
            m_floats[i][32] = &group1(extData)->unk90;
            m_floats[i][33] = &group1(extData)->unk94;
            m_floats[i][34] = &group1(extData)->unk98;
            m_floats[i][35] = &group1(extData)->unk9C;
            m_floats[i][36] = &group1(extData)->unkA0;
            m_floats[i][37] = &group1(extData)->unkA4;

            m_floats[i][38] = &group2Cast(extData)->unk0;
            m_floats[i][39] = &group2(extData)->unk4;
            m_floats[i][40] = &group2(extData)->unk8;
            m_floats[i][41] = &group2(extData)->unkC;
            m_floats[i][42] = &group2(extData)->unk10;
            m_floats[i][43] = &group2(extData)->unk14;
            m_floats[i][44] = &group2(extData)->unk18;

            m_floats[i][45] = &group3Cast(extData)->unk0;
            m_floats[i][46] = &group3(extData)->unk4;
            m_floats[i][47] = &group3(extData)->unk8;
            m_floats[i][48] = &group3(extData)->unkC;

            m_ints[i][0] = &group1Cast(extData)->unk0;
            m_ints[i][1] = &group1(extData)->unk4;
            m_ints[i][2] = &group1(extData)->unk3C;
            m_ints[i][3] = &group1(extData)->unk68;
        }
    }
};
static_assert(sizeof(ftPurinExtendParamAccesser) == 0x1C8, "Class is the wrong size!");

extern ftPurinExtendParamAccesser g_ftPurinExtendParamAccesser;
