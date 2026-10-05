#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// TODO: identify the special moves these ExtendParam classes are for

struct ftMarioExtendParamClass1 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
};

struct ftMarioExtendParamClass2 {
    float unk0;
    float unk4;
    float unk8;
};

struct ftMarioExtendParamClass3 {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
};

struct ftMarioExtendParamClass4 {
    int unk0;
    float unk4;
    int unk8;
    float unkC;
    int unk10;
};

// ftMario and ftMarioD (Dr. Mario) have the same parameter layout; they are separate classes with the same code.
// TODO: Match without the const_cast hack
// TODO: UBFIX endianness
#define FT_MARIO_EXTEND_PARAM_ACCESSER(Name, Kind)                                               class Name : public ftExtendParamAccesserEx<3999, 15, 23999, 3> {                                 static const u32 OffsetExt4 = 0x88;                                                           const ftMarioExtendParamClass1* group1(const u8* base) {                                         return *(ftMarioExtendParamClass1* const*)(base + OffsetExt1);                            }                                                                                             const ftMarioExtendParamClass1* group1Cast(const u8* base) {                                     return *(ftMarioExtendParamClass1**)(base + OffsetExt1);                                  }                                                                                             const ftMarioExtendParamClass2* group2(const u8* base) {                                         return *(ftMarioExtendParamClass2* const*)(base + OffsetExt2);                            }                                                                                             const ftMarioExtendParamClass2* group2Cast(const u8* base) {                                     return *(ftMarioExtendParamClass2**)(base + OffsetExt2);                                  }                                                                                             const ftMarioExtendParamClass3* group3(const u8* base) {                                         return *(ftMarioExtendParamClass3* const*)(base + OffsetExt3);                            }                                                                                             const ftMarioExtendParamClass3* group3Cast(const u8* base) {                                     return *(ftMarioExtendParamClass3**)(base + OffsetExt3);                                  }                                                                                             const ftMarioExtendParamClass4* group4(const u8* base) {                                         return *(ftMarioExtendParamClass4* const*)(base + OffsetExt4);                            }                                                                                             const ftMarioExtendParamClass4* group4Cast(const u8* base) {                                     return *(ftMarioExtendParamClass4**)(base + OffsetExt4);                                  }                                                                                         public:                                                                                           Name() : ftExtendParamAccesserEx(Kind) { }                                                   virtual ~Name() { }                                                                           virtual void setup(const u8* extData) {                                                          for (s32 i = 0; i < NumVariations; i++) {                                                         m_floats[i][0] = &group1Cast(extData)->unk0;                                                  m_floats[i][1] = &group1(extData)->unk4;                                                      m_floats[i][2] = &group1(extData)->unk8;                                                      m_floats[i][3] = &group1(extData)->unkC;                                                      m_floats[i][4] = &group1(extData)->unk10;                                                     m_floats[i][5] = &group2Cast(extData)->unk0;                                                  m_floats[i][6] = &group2(extData)->unk4;                                                      m_floats[i][7] = &group2(extData)->unk8;                                                      m_floats[i][8] = &group3Cast(extData)->unk0;                                                  m_floats[i][9] = &group3(extData)->unk4;                                                      m_floats[i][10] = &group3(extData)->unk8;                                                     m_floats[i][11] = &group3(extData)->unkC;                                                     m_floats[i][12] = &group3(extData)->unk10;                                                    m_floats[i][13] = &group4(extData)->unk4;                                                     m_floats[i][14] = &group4(extData)->unkC;                                                     m_ints[i][0] = &group4Cast(extData)->unk0;                                                    m_ints[i][1] = &group4(extData)->unk8;                                                        m_ints[i][2] = &group4(extData)->unk10;                                                   }                                                                                         }                                                                                         }

FT_MARIO_EXTEND_PARAM_ACCESSER(ftMarioExtendParamAccesser, Fighter_Mario);
FT_MARIO_EXTEND_PARAM_ACCESSER(ftMarioDExtendParamAccesser, Fighter_MarioD);

extern ftMarioExtendParamAccesser g_ftMarioExtendParamAccesser;
extern ftMarioDExtendParamAccesser g_ftMarioDExtendParamAccesser;
