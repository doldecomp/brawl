#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

class ftExtendParamAccesser : public soParamAccesser {
    ftKind m_kind;
public:
    ftExtendParamAccesser(ftKind kind);
    static ftExtendParamAccesser* getAccesser(ftKind kind);
    static bool isExistAccesser(ftKind kind);

    virtual ~ftExtendParamAccesser();
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) = 0;
    virtual void* getParamIndefinite(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) { return nullptr; }
    virtual void setup(const u8* extData) = 0;
};
static_assert(sizeof(ftExtendParamAccesser) == 0x10, "Class is the wrong size!");

// TODO: T1 and T3 always equal 3999 and 24999 and have unknown purpose
template<u32 T1, u32 NumFloats, u32 T3, u32 NumInts>
class ftExtendParamAccesserEx : public ftExtendParamAccesser {
protected:
    static const s32 NumVariations = 2;
    static const s32 OffsetFloat = 4000;
    static const s32 OffsetInt = 24000;

    // Byte offsets to pointers to ExtendParam structures
    static const u32 OffsetExt1 = 0x7C;
    static const u32 OffsetExt2 = 0x80;
    static const u32 OffsetExt3 = 0x84;

    const float* m_floats[NumVariations][NumFloats+1];
    const int* m_ints[NumVariations][NumInts+1];
public:
    ftExtendParamAccesserEx(ftKind kind)
        : ftExtendParamAccesser(kind) { }
    virtual ~ftExtendParamAccesserEx() { }
    virtual float getParamFloat(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) {
        return m_floats[soValueAccesser::getValueVariation()][p2 - OffsetFloat][p3];
    }
    virtual s32 getParamInt(soModuleAccesser* moduleAccesser, s32 p2, s32 p3 = 0) {
        return m_ints[soValueAccesser::getValueVariation()][p2 - OffsetInt][p3];
    }
    virtual void setup(const u8* extData) { }
};
