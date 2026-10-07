#pragma once
// NOTE: shadows the BrawlHeaders copy to add the constructor used by soGeneralWorkBuilder.

#include <StaticAssert.h>
#include <so/work/so_general_work_abstract.h>
#include <types.h>

class soGeneralWorkSimple : public soGeneralWorkAbstract {
    void clearInts() {
#ifdef FT_MARTH_RUNTIME_HELPERS
        u32 intWorkSize = m_intWorkSize;
        // MATCH-ONLY: retain the original second size load before taking the minimum.
        u32 currentSize = *(volatile u32*)&m_intWorkSize;
        if (intWorkSize >= currentSize) intWorkSize = currentSize;
#else
        s32 intWorkSize = m_intWorkSize;
        intWorkSize = (intWorkSize != m_intWorkSize) ? m_intWorkSize : intWorkSize;
#endif
        for (s32 i = 0; i < (s32)intWorkSize; i++) {
            m_intWorks[i] = 0;
        }
    }

    void clearFloats() {
#ifdef FT_MARTH_RUNTIME_HELPERS
        u32 floatWorkSize = m_floatWorkSize;
        // MATCH-ONLY: retain the original second size load before taking the minimum.
        u32 currentSize = *(volatile u32*)&m_floatWorkSize;
        if (floatWorkSize >= currentSize) floatWorkSize = currentSize;
#else
        s32 floatWorkSize = m_floatWorkSize;
        floatWorkSize = (floatWorkSize != m_floatWorkSize) ? m_floatWorkSize : floatWorkSize;
#endif
        for (s32 i = 0; i < (s32)floatWorkSize; i++) {
            m_floatWorks[i] = 0;
        }
    }

    void clearFlags() {
#ifdef FT_MARTH_RUNTIME_HELPERS
        u32 flagWorkSize = m_flagWorkSize;
        // MATCH-ONLY: retain the original second size load before taking the minimum.
        u32 currentSize = *(volatile u32*)&m_flagWorkSize;
        if (flagWorkSize >= currentSize) flagWorkSize = currentSize;
#else
        s32 flagWorkSize = m_flagWorkSize;
        flagWorkSize = (flagWorkSize != m_flagWorkSize) ? m_flagWorkSize : flagWorkSize;
#endif
        for (s32 i = 0; i < (s32)flagWorkSize; i++) {
            m_flagWorks[i] = 0;
        }
    }
public:
    s32* m_intWorks;
    u32 m_intWorkSize;
    float* m_floatWorks;
    u32 m_floatWorkSize;
    u32* m_flagWorks;
    u32 m_flagWorkSize;

    soGeneralWorkSimple() { }
    soGeneralWorkSimple(s32* ints, u32 numInts, float* floats, u32 numFloats, u32* flags, u32 numFlags);

    virtual s32 getIntWork(u32 index) const {
        return m_intWorks[index];
    }

    virtual void setIntWork(s32 value, u32 index) {
        m_intWorks[index] = value;
    }

    virtual void addIntWork(s32 value, u32 index) {
        m_intWorks[index] += value;
    }

    virtual void subIntWork(s32 value, u32 index) {
        m_intWorks[index] -= value;
    }

    virtual void mulIntWork(s32 value, u32 index) {
        m_intWorks[index] *= value;
    }

    virtual void divIntWork(s32 value, u32 index) {
        if (0 != value) {
            m_intWorks[index] /= value;
        }
    }

    virtual void incIntWork(u32 index) {
        m_intWorks[index]++;
    }

    virtual void decIntWork(u32 index) {
        m_intWorks[index]--;
    }

    virtual u32 getIntWorkSize() {
        return m_intWorkSize;
    }

    virtual float getFloatWork(u32 index) const {
        return m_floatWorks[index];
    }

    virtual void setFloatWork(float value, u32 index) {
        m_floatWorks[index] = value;
    }

    virtual void addFloatWork(float value, u32 index) {
        m_floatWorks[index] += value;
    }

    virtual void subFloatWork(float value, u32 index) {
        m_floatWorks[index] -= value;
    }

    virtual void mulFloatWork(float value, u32 index) {
        m_floatWorks[index] *= value;
    }

    virtual void divFloatWork(float value, u32 index) {
        if (0.0f != value) {
            m_floatWorks[index] /= value;
        }
    }

    virtual u32 getFloatWorkSize() {
        return m_floatWorkSize;
    }

    virtual void onFlag(u32 flag, u32 index) {
        m_flagWorks[index] |= flag;
    }

    virtual void offFlag(u32 flag, u32 index) {
        m_flagWorks[index] &= ~flag;
    }

    virtual void clearFlag(u32 index) {
        m_flagWorks[index] = 0;
    }

    virtual bool isFlag(u32 flag, u32 index) const {
        return m_flagWorks[index] & flag;
    }

    virtual u32 turnOffFlag(u32 flag, u32 index) {
        u32 result;
        if ((result = isFlag(flag, index)) == 1) {
            offFlag(flag, index);
        }
        return result;
    }

    virtual u32 getFlagWorkSize() {
        return m_flagWorkSize;
    }

    virtual void clearWorkAll() {
        clearInts();
        clearFloats();
        clearFlags();
    }
};
static_assert(sizeof(soGeneralWorkSimple) == 0x24, "Class is wrong size!");


extern soGeneralWorkSimple g_soGeneralWorkSimple;
