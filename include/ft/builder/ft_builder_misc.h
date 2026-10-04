#pragma once

// Builders of the remaining small modules: team, area, color blend, jostle, abnormal, slow, glow, combo.
// All of them are constructed in the module accesser builder; see ft_module_accesser_builder.h.

#include <ft/builder/ft_dol_types.h>
#include <so/slow/so_slow_module_impl.h>
#include <so/color/so_color_blend_module_impl.h>
#include <types.h>

////////////////////////////////////////
// soTeamModuleBuilder (0x74 bytes): fn_106_53D8 (ctor) / fn_106_49CC (dtor). The team module is at +0x30.
//   soTeamModuleBuilder(fbd.getTeam(), soModuleAccesser*)
// STUB: storage only (ftTeam at +4, ftTeamIndirect at +0x18, soTeamModuleImpl at +0x30).
////////////////////////////////////////

template <typename T>
class soTeamModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soTeamModuleBuilder {
    u8 m_data[0x74];
public:
    soTeamModuleBuilder(s32 team, soModuleAccesser* acc) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    void* getModule() { return m_data + 0x30; }
};

////////////////////////////////////////
// soAreaModuleBuilder (0x374 bytes): fn_106_6BD8 (ctor) / fn_106_2F08 (dtor). The soAreaModuleImpl is at +0x10.
//   soAreaModuleBuilder(soModuleAccesser*, fbd.getAreaCategory(), &g_soEventObserverRegistrationDescNull)
// STUB: storage only.
////////////////////////////////////////

template <typename T>
class soAreaModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soAreaModuleBuilder {
    u8 m_data[0x374];
public:
    soAreaModuleBuilder(soModuleAccesser* acc, u8 areaCategory, soEventObserverRegistrationDesc* regDesc) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    void* getModule() { return m_data + 0x10; }
};

////////////////////////////////////////
// Builders that hold a single module
////////////////////////////////////////

template <typename T>
class soComboModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soComboModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soComboModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <s32 A, s32 B, typename T>
class soJostleModuleBuildConfig {
public:
    enum { Arg0 = A, Arg1 = B };
    typedef T ModuleType;
};

template <typename BC>
class soJostleModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soJostleModuleBuilder(soModuleAccesser* acc, void* jostleData) : m_module(acc, BC::Arg0, BC::Arg1, jostleData) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soAbnormalModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soAbnormalModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soAbnormalModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soSlowModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soSlowModuleBuilder {
    typename BC::ModuleType m_module;
    u8 unk38[4]; // HYPOTHESIS: the builder is 0x3C bytes while soSlowModuleImpl is 0x38
public:
    soSlowModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soGlowModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soGlowModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soGlowModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <s32 A, s32 B, typename T>
class soColorBlendModuleBuildConfig {
public:
    enum { Arg0 = A, Arg1 = B };
    typedef T ModuleType;
};

template <typename BC>
class soColorBlendModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soColorBlendModuleBuilder(soModuleAccesser* acc) : m_module(acc, BC::Arg0, BC::Arg1) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};
