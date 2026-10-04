#pragma once

// soMotionModuleBuilder<soMotionModuleBuildConfig<...>>: ftMarth fn_106_58E8 (ctor, 0x19C bytes) / fn_106_4C1C (dtor).
// Size 0x394, the soMotionModuleImpl is at +0x224. Constructed in the module accesser builder as
//   soMotionModuleBuilder(soModuleAccesser*, fbd.getMotionData())
// STUB: storage only; reconstruct the real members (soTransitionModule + type-list pools, soArrayVector<soPartialAnim,2>,
// soArrayVector<soOtherAnim,1>, soArrayVector<soTransitionTermPack,1>, soArrayVector<u32,5>, soMotionAnimObjCacheModule...).

#include <ft/builder/ft_dol_types.h>
#include <types.h>

template <typename T>
class soMotionModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soMotionModuleBuilder {
    u8 m_data[0x394];
public:
    soMotionModuleBuilder(soModuleAccesser* acc, void* motionData) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB: non-empty so the call is not optimized away
    soMotionModule* getModule() { return (soMotionModule*)(m_data + 0x224); }
};
