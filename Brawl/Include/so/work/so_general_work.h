#pragma once

#include <StaticAssert.h>
#include <so/so_array.h>
#include <so/so_general_flag.h>
#include <so/work/so_general_work_abstract.h>
#include <types.h>

class soGeneralWork : public soGeneralWorkAbstract {
    soArray<s32>* m_ints;
    soArray<float>* m_floats;
    soArray<soGeneralFlag<s32> >* m_flags;
public:
    soGeneralWork(
        soArray<s32>* p1,
        soArray<float>* p2,
        soArray<soGeneralFlag<s32> >* p3
    ) : m_ints(p1), m_floats(p2), m_flags(p3) { }
    ~soGeneralWork() { }
    virtual s32 getIntWork(u32 index) const;
    virtual void setIntWork(s32 value, u32 index);
    virtual void addIntWork(s32 value, u32 index);
    virtual void subIntWork(s32 value, u32 index);
    virtual void mulIntWork(s32 value, u32 index);
    virtual void divIntWork(s32 value, u32 index);
    virtual void incIntWork(u32 index);
    virtual void decIntWork(u32 index);
    virtual u32 getIntWorkSize();
    virtual float getFloatWork(u32 index) const;
    virtual void setFloatWork(float value, u32 index);
    virtual void addFloatWork(float value, u32 index);
    virtual void subFloatWork(float value, u32 index);
    virtual void mulFloatWork(float value, u32 index);
    virtual void divFloatWork(float value, u32 index);
    virtual u32 getFloatWorkSize();
    virtual void onFlag(u32 flag, u32 index);
    virtual void offFlag(u32 flag, u32 index);
    virtual void clearFlag(u32 index);
    virtual bool isFlag(u32 flag, u32 index) const;
    virtual u32 turnOffFlag(u32 flag, u32 index);
    virtual u32 getFlagWorkSize();
    virtual void clearWorkAll();
};
static_assert(sizeof(soGeneralWork) == 0x18, "Class is wrong size!");

extern soGeneralWork g_soGeneralWork;
