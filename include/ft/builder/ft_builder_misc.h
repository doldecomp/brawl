#pragma once

// Builders of the remaining small modules: team, area, color blend, jostle, abnormal, slow, glow, combo.
// All of them are constructed in the module accesser builder; see ft_module_accesser_builder.h.

#include <ft/builder/ft_dol_types.h>
#include <so/slow/so_slow_module_impl.h>
#include <so/color/so_color_blend_module_impl.h>
#include <types.h>

////////////////////////////////////////
// soTeamModuleBuilder (0x74 bytes): fn_106_53D8 (ctor) / fn_106_49CC (dtor).
//   soTeamModuleBuilder(fbd.getTeam() (unused), soModuleAccesser*); the team is the entry id of the owner fighter.
////////////////////////////////////////

#include <ft/fighter.h>

template <typename T>
class soTeamModuleBuildConfig {
public:
    typedef T ModuleType;
};

extern char g_soTeamModuleNullArg[];

template <typename BC>
class soTeamModuleBuilder {
    u32 m_unk0;
    ftTeam m_team;                 // +0x4
    ftTeamIndirect m_teamIndirect; // +0x18
    soTeamModuleImpl m_module;     // +0x30
public:
    static int getEntryId(soModuleAccesser* acc) { return dynamic_cast<Fighter&>(*acc->m_stageObject).m_entryId; }
    soTeamModuleBuilder(s32 team, soModuleAccesser* acc) :
        m_team(getEntryId(acc)),
        m_teamIndirect(getEntryId(acc)),
        m_module(&m_team, &m_team, &m_teamIndirect, acc, g_soTeamModuleNullArg) { }
    void* getModule() { return &m_module; }
};

////////////////////////////////////////
// soAreaModuleBuilder (0x374 bytes): fn_106_6BD8 (ctor) / fn_106_2F08 (dtor). The area module is at +0x10.
//   soAreaModuleBuilder(soModuleAccesser*, fbd.getAreaCategory(), &g_soEventObserverRegistrationDescNull)
////////////////////////////////////////

#include <so/area/so_area_module_impl.h>
#include <ft/builder/ft_dol_holders.h>

template <typename T>
class soAreaModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soAreaModuleBuilder : public soArraySelectHolder<1, soArrayVector<soAreaWind, 1>, soArrayNull<soAreaWind> > {
    typename BC::ModuleType m_module;                 // +0x10
    soAreaEnviromentElementCheckerImpl m_checker;     // +0x78
    soArrayVector<soAreaContactLog, 16> m_contactLogs; // +0x94
    soArrayVector<soAreaInstance, 9> m_instances;     // +0x220
    u32 m_pad;
public:
    soAreaModuleBuilder(soModuleAccesser* acc, u8 areaCategory, soEventObserverRegistrationDesc* regDesc) :
        soArraySelectHolder<1, soArrayVector<soAreaWind, 1>, soArrayNull<soAreaWind> >(1, 0),
        m_module(acc, areaCategory, &m_instances, &m_contactLogs, &m_checker, this->get(), regDesc, 8),
        m_checker(), m_contactLogs(0), m_instances(0) { }
    void* getModule() { return &m_module; }
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
