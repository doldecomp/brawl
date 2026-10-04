#pragma once

// soStatusModuleBuilder<soStatusModuleBuildConfig<289, soGeneralWorkBuildConfig<26,14,7>, ...>> (0xEB8 bytes):
// ftMarth fn_106_6224 (ctor) / fn_106_3394 (dtor); the soStatusModuleImpl is at +0xE08.
//   soStatusModuleBuilder(soModuleAccesser*, fbd.getStatusData(), fbd.getPreCheckAnimCmdData())
// soGeneralWorkBuilder<soGeneralWorkBuildConfig<77,32,3>> (0x1E8 bytes): fn_106_6AAC (ctor) / fn_106_314C (dtor), default constructed.
// STUB: storage only.

#include <ft/builder/ft_dol_types.h>
#include <types.h>

template <typename T>
class soStatusModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soStatusModuleBuilder {
    u8 m_data[0xEB8];
public:
    soStatusModuleBuilder(soModuleAccesser* acc, void* statusData, void* preCheckData) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    soStatusModule* getModule() { return (soStatusModule*)(m_data + 0xE08); }
};

template <typename T>
class soGeneralWorkBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soGeneralWorkBuilder {
    u8 m_data[0x1E8];
public:
    soGeneralWorkBuilder() { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
};
