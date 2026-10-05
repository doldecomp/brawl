#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ness/ft_ness.h>
#include <ft/ness/ft_ness_extend_param_accesser.h>

#define FT_NO_REFLECTOR_INSTANTIATION
#define FT_BC ftNessBuildConfig
#include <ft/builder/ft_builder_noinline.h>

#pragma dont_inline on
template soCollisionShieldModuleBuilder<ftNessCollisionReflectorBaseModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
template soCollisionShieldModuleBuilder<ftNessCollisionAbsorberModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
#pragma dont_inline off

ftNessExtendParamAccesser g_ftNessExtendParamAccesser;

ftClassInfoImpl<Fighter_Ness, ftNess> g_ftClassInfoNess;

ftNess::ftNess(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftNessBuildConfig>(entryId,
                                         Fighter_Ness,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftNess is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftNessInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftNessInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
