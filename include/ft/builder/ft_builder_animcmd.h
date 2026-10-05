#pragma once

// soAnimCmdModuleBuilder<soAnimCmdModuleBuildConfig<11, soAnimCmdModuleImpl>> (0xF4 bytes): ctor / dtor in the REL.
//   soAnimCmdModuleBuilder(s16 unitId); the soAnimCmdModuleImpl is at +0, its soInstanceManagerFullPropertyVector at +0x24.
// ftAnimCmdModuleSubBuilder<ftAnimCmdModuleSubBuildConfig<289, 501>> (0x15EC bytes in the module accesser builder after the
// 0x10-byte soArrayContractibleTable<const soStatusData>): the soAnimCmdControlUnitBuilder<...> members, built in
// the ftMarth constructor (anim cmd interpreters, soAnimCmdAddressPackArraySeparate, disguise lists).
// STUB (sub builder): storage only.

#include <ft/builder/ft_dol_types.h>
#include <so/anim/so_anim_cmd_module_impl.h>
#include <so/so_instance_manager.h>
#include <types.h>

#include <ft/builder/ft_dol_instances.h>

FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11);

// MATCH-ONLY: the constructor of this instance manager (and its vtable) are in sora_melee; only the destructor is
// emitted in the REL. Explicit specialization with the members declared but not defined.
template <>
class soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 11> : public soInstanceManagerFullProperty<soAnimCmdControlUnit> {
    soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11> m_arrayVector; // 0x10
    bool m_unk1;
public:
    soInstanceManagerFullPropertyVector(bool p1);
    ~soInstanceManagerFullPropertyVector() { }
    virtual soAnimCmdControlUnit& at(s32 id);
    virtual soAnimCmdControlUnit& atIndex(s32 idx);
    virtual s32 getId(s32 idx);
    virtual u32 size() const;
    virtual bool isContain(s32 id) const;
    virtual void erase(s32 id);
    virtual void clear();
    virtual void set(const soAnimCmdControlUnit& elm, s32 id);
    virtual s32 add(soAnimCmdControlUnit& elm, s32 id, soAttributeFlag attr, s16 p4);
    virtual u32 capacity();
    virtual soAnimCmdControlUnit& atIndexFast(s32 idx);
    virtual soInstanceUnitFullProperty<soAnimCmdControlUnit>& atUnitIndexFast(s32 idx);
    virtual s32 getIndex(s32 id) const;
    virtual void getAttributeArray(soAttributeFlag targetAttr, soArray<soAnimCmdControlUnit*>& arr);
    virtual soAttributeFlag getAttribute(s32 id) const;
    virtual void getPriorityArray(soArray<soAnimCmdControlUnit*>& arr);
};
static_assert(sizeof(soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 11>) == 0xD0, "Class is wrong size!");

template <u32 N, typename T>
class soAnimCmdModuleBuildConfig {
public:
    typedef T ModuleType;
    enum { ControlUnitNum = N };
};

template <typename BC>
class soAnimCmdModuleBuilder {
    typename BC::ModuleType m_module; // +0
    soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, BC::ControlUnitNum> m_controlUnits; // +0x24
public:
    ~soAnimCmdModuleBuilder() { }
    soAnimCmdModuleBuilder(s16 unitId) : m_module(unitId, &m_controlUnits), m_controlUnits(false) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <u32 P1, u32 P2>
class ftAnimCmdModuleSubBuildConfig {
    // TODO
};

template <typename BC>
class ftAnimCmdModuleSubBuilder {
    u8 m_data[0x15EC];
public:
    ~ftAnimCmdModuleSubBuilder() { m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; } // STUB: non-trivial so the dtor call exists
    ftAnimCmdModuleSubBuilder() { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
};
