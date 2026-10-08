#pragma once

#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// One accesser per Zako fighter; they only differ in the fighter kind.
class ftZakoExtendParamAccesserBase : public ftExtendParamAccesserEx<3999, 1, 23999, 0> {
protected:
    const u8* group1(const u8* base) { return *(const u8* const*)(base + 0x7C); }
    const u8* group1Cast(const u8* base) { return *(const u8**)(base + 0x7C); }

public:
    ftZakoExtendParamAccesserBase(ftKind kind) : ftExtendParamAccesserEx(kind) { }
};

#define FT_ZAKO_EXTEND_PARAM_ACCESSER(NAME, KIND)                                   \
    class ftZako##NAME##ExtendParamAccesser : public ftZakoExtendParamAccesserBase { \
    public:                                                                         \
        ftZako##NAME##ExtendParamAccesser() : ftZakoExtendParamAccesserBase(KIND) { } \
        virtual ~ftZako##NAME##ExtendParamAccesser() { }                            \
        virtual void setup(const u8* extData) {                                     \
            for (s32 i = 0; i < NumVariations; i++) {                               \
                m_floats[i][0] = (const float*)(group1Cast(extData) + 0x0);         \
            }                                                                       \
        }                                                                           \
    };

FT_ZAKO_EXTEND_PARAM_ACCESSER(Boy, Fighter_Zako_Boy)
FT_ZAKO_EXTEND_PARAM_ACCESSER(Girl, Fighter_Zako_Girl)
FT_ZAKO_EXTEND_PARAM_ACCESSER(Child, Fighter_Zako_Child)
FT_ZAKO_EXTEND_PARAM_ACCESSER(Ball, Fighter_Zako_Ball)
