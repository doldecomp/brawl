#pragma once

// soGeneralWorkBuilder<soGeneralWorkBuildConfig<Ints, Floats, Flags>>: the work arrays followed by the
// soGeneralWorkSimple that points at them. Used standalone (77,32,3 -> 0x1E8 bytes, ftMarth fn_106_6AAC /
// fn_106_314C) and inside the status builder (26,14,7 for Marth).

#include <so/work/so_general_work_simple.h>
#include <types.h>

template <s32 Ints, s32 Floats, s32 Flags>
class soGeneralWorkBuildConfig {
public:
    enum { IntCap = Ints, FloatCap = Floats, FlagCap = Flags };
    typedef soGeneralWorkSimple ModuleType;
};

template <typename BC>
class soGeneralWorkBuilder {
    s32 m_ints[BC::IntCap];
    float m_floats[BC::FloatCap];
    u32 m_flags[BC::FlagCap];
    typename BC::ModuleType m_module;
public:
    soGeneralWorkBuilder() : m_module(m_ints, BC::IntCap, m_floats, BC::FloatCap, m_flags, BC::FlagCap) {
        soGeneralWorkAbstract* work = &m_module;
        work->clearWorkAll();
    }
    typename BC::ModuleType* getModule() { return &m_module; }
};
