#pragma once

// soAnimCmdModuleBuilder<soAnimCmdModuleBuildConfig<11, soAnimCmdModuleImpl>> (0xF4 bytes): fn_106_61E0 (ctor) / fn_106_4088 (dtor).
//   soAnimCmdModuleBuilder(s16 unitId); the soAnimCmdModuleImpl is at +0.
// ftAnimCmdModuleSubBuilder<ftAnimCmdModuleSubBuildConfig<289, 501>> (0x15EC bytes in the module accesser builder after the
// 0x10-byte soArrayContractibleTable<const soStatusData>): the soAnimCmdControlUnitBuilder<...> members, built in
// the ftMarth constructor (anim cmd interpreters, soAnimCmdAddressPackArraySeparate, disguise lists).
// STUB: storage only.

#include <ft/builder/ft_dol_types.h>
#include <types.h>

template <typename T>
class soAnimCmdModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soAnimCmdModuleBuilder {
    u8 m_data[0xF4];
public:
    ~soAnimCmdModuleBuilder() { m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; } // STUB: non-trivial so the dtor call exists
    soAnimCmdModuleBuilder(s16 unitId) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    soAnimCmdModule* getModule() { return (soAnimCmdModule*)m_data; }
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
