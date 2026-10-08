#pragma once

// soMotionModuleBuilder<soMotionModuleBuildConfig<501, soMotionModuleImpl, 2, 1, TransitionConfig, CacheConfig>> (0x394 bytes):
// ftMarth fn_106_58E8 (ctor) / fn_106_4C1C (dtor). The soMotionModuleImpl is at +0x224. Constructed in the module accesser
// builder as soMotionModuleBuilder(soModuleAccesser*, fbd.getMotionData()).
//   +0x000 soTransitionModuleBuilder (one group of 8 terms)
//   +0x0C4 partial anims (2), +0x160 other anims (1), +0x198 transition term packs (1), +0x1B8 u32 (5)
//   +0x1D8 table of the motion data (501), +0x1E8 soMotionAnimObjCacheModuleBuilder, +0x224 the module

#include <ft/builder/ft_builder_animcmd.h>
#include <ft/builder/ft_builder_status.h>
#include <ft/builder/ft_builder_transition.h>
#include <ft/builder/ft_dol_array_list.h>
#include <ft/builder/ft_dol_types.h>
#include <ft/builder/ft_dol_instances.h>
#include <so/motion/so_motion_module_impl.h>
#include <types.h>

namespace nw4r {
namespace g3d {
class AnmObjChrRes;
}
}

FT_DOL_ARRAY_VECTOR(soTransitionTermGroup, 1);
FT_DOL_ARRAY_VECTOR(soPartialAnim, 2);
FT_DOL_ARRAY_VECTOR(soOtherAnim, 1);
FT_DOL_ARRAY_VECTOR(soTransitionTermPack, 1);
FT_DOL_ARRAY_VECTOR(u32, 5);
typedef soMotionAnimObjCacheUnit<nw4r::g3d::AnmObjChrRes> ftMotionAnimObjCacheUnitChrRes;
FT_DOL_ARRAY_VECTOR(ftMotionAnimObjCacheUnitChrRes, 5);
typedef const soMotionData soMotionDataConst;
FT_DOL_CONTRACTIBLE_TABLE(soMotionDataConst);

FT_DOL_POLY_BEGIN(soMotionAnimObjCacheModuleImpl, 0x8);
    soMotionAnimObjCacheModuleImpl(soArray<ftMotionAnimObjCacheUnitChrRes>* units);
FT_DOL_POLY_END;

// The type list of the transition term groups of the motion module (a single group of 8 terms).
typedef soTypeList<soIntToType<8>, soTypeListNullType> ftMotionTransitionTypeList;

template <u32 Num, typename T>
class soMotionAnimObjCacheModuleBuildConfig {
public:
    typedef T ModuleType;
    enum { CacheNum = Num };
};

template <typename BC>
class soMotionAnimObjCacheModuleBuilder {
    soArrayVector<ftMotionAnimObjCacheUnitChrRes, BC::CacheNum> m_units; // +0
public:
    typename BC::ModuleType m_module;                                    // +0x34
    soMotionAnimObjCacheModuleBuilder() : m_units(0), m_module(&m_units) { }
    ~soMotionAnimObjCacheModuleBuilder() { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <u32 DataNum, typename T, u32 PartialNum, u32 OtherNum, typename TransitionConfig, typename CacheConfig>
class soMotionModuleBuildConfig {
public:
    typedef T ModuleType;
    typedef TransitionConfig TransitionBuildConfig;
    typedef CacheConfig CacheBuildConfig;
    enum { MotionDataNum = DataNum, PartialAnimNum = PartialNum, OtherAnimNum = OtherNum };
};

template <typename V, typename Null>
class soSelectInstanceHolder {
public:
    V m_array;
    soSelectInstanceHolder() : m_array(0) { }
    V* get() { return &m_array; }
    ~soSelectInstanceHolder() { }
};

template <typename BC>
class soMotionModuleBuilder {
    typedef soArrayVector<soPartialAnim, BC::PartialAnimNum> PartialAnimsT;
    typedef soArrayVector<soOtherAnim, BC::OtherAnimNum> OtherAnimsT;
    typedef soArrayVector<soTransitionTermPack, 1> TermPacksT;
    typedef soArrayVector<u32, 5> U32sT;
    soTransitionModuleBuilder<typename BC::TransitionBuildConfig> m_transitionBuilder;                                             // +0
    soArraySelectHolder<1, PartialAnimsT, soSingletonHolder<soArrayNull<soPartialAnim> > > m_partialAnims;                         // +0xC4
    soArraySelectHolder<1, OtherAnimsT, soSingletonHolder<soArrayNull<soOtherAnim> > > m_otherAnims;                               // +0x160
    soSelectInstanceHolder<TermPacksT, soSingletonHolder<soArrayNull<soTransitionTermPack> > > m_termPacks;                        // +0x198
    soArraySelectHolder<1, U32sT, soSingletonHolder<soArrayNull<u32> > > m_u32s;                                                   // +0x1B8
    soArrayContractibleTable<soMotionDataConst> m_motionData;                                                                      // +0x1D8
    soMotionAnimObjCacheModuleBuilder<typename BC::CacheBuildConfig> m_cacheBuilder;                                               // +0x1E8
    typename BC::ModuleType m_module;                                                                                              // +0x224
public:
    soMotionModuleBuilder(soModuleAccesser* acc, void* motionData) :
        m_transitionBuilder(),
        m_partialAnims(BC::PartialAnimNum, 0),
        m_otherAnims(BC::OtherAnimNum, 0),
        m_termPacks(),
        m_u32s(5, 0),
        m_motionData((const soMotionData*)motionData, BC::MotionDataNum),
        m_cacheBuilder(),
        m_module(acc, &m_motionData, m_transitionBuilder.getModule(), m_partialAnims.get(), m_otherAnims.get(),
                 m_termPacks.get(), m_u32s.get(), static_cast<soEventManager&>(acc->getEventManageModule()).getManageId(), true, (soMotionAnimObjCacheModule*)&m_cacheBuilder.m_module) {
        acc->getModelModule().isNull();
    }
    ~soMotionModuleBuilder() { }
    soMotionModule* getModule() { return &m_module; }
};
