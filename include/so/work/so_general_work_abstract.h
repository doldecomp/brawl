#pragma once
// NOTE: shadows the BrawlHeaders copy to add the non-null constructor used by the builders.

#include <StaticAssert.h>
#include <types.h>
#include <so/so_null.h>

class soGeneralWorkAbstract : private soNull, public soNullable {
public:
    soGeneralWorkAbstract();
    // MATCH-ONLY: ctor of the fighter builders' work areas (not null); inlined into soGeneralWorkSimple's ctor.
    soGeneralWorkAbstract(bool isNull) : soNullable(isNull) { }
#ifdef FT_MODULE_BUILDER
    ~soGeneralWorkAbstract(); // MATCH-ONLY: out of line in the fighter RELs (defined in ft_builder_noinline.h)
#else
    ~soGeneralWorkAbstract() { }
#endif
    virtual s32 getIntWork(u32 index) const { return 0; }
    virtual void setIntWork(s32 value, u32 index) { }
    virtual void addIntWork(s32 value, u32 index) { }
    virtual void subIntWork(s32 value, u32 index) { }
    virtual void mulIntWork(s32 value, u32 index) { }
    virtual void divIntWork(s32 value, u32 index) { }
    virtual void incIntWork(u32 index) { }
    virtual void decIntWork(u32 index) { }
    virtual u32 getIntWorkSize() { return 0; }
    virtual float getFloatWork(u32 index) const { return 0.0f; }
    virtual void setFloatWork(float value, u32 index) { }
    virtual void addFloatWork(float value, u32 index) { }
    virtual void subFloatWork(float value, u32 index) { }
    virtual void mulFloatWork(float value, u32 index) { }
    virtual void divFloatWork(float value, u32 index) { }
    virtual u32 getFloatWorkSize() { return 0; }
    virtual void onFlag(u32 flag, u32 index) { }
    virtual void offFlag(u32 flag, u32 index) { }
    virtual void clearFlag(u32 index) { }
    virtual bool isFlag(u32 flag, u32 index) const { return false; }
    virtual u32 turnOffFlag(u32 flag, u32 index) { return 0; }
    virtual u32 getFlagWorkSize() { return 0; }
    virtual void clearWorkAll() { }
};
static_assert(sizeof(soGeneralWorkAbstract) == 12, "Class is wrong size!");

extern soGeneralWorkAbstract g_soGeneralWorkAbstract;
