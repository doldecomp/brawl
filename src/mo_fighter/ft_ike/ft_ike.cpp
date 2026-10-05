#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ike/ft_ike.h>
#include <ft/ike/ft_ike_extend_param_accesser.h>

#define FT_BC ftIkeBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftIkeExtendParamAccesser g_ftIkeExtendParamAccesser;

ftClassInfoImpl<Fighter_Ike, ftIke> g_ftClassInfoIke;

ftIke::ftIke(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftIkeBuildConfig>(entryId,
                                         Fighter_Ike,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftIke is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftIkeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftIkeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
