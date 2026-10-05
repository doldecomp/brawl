#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/koopa/ft_koopa.h>
#include <ft/koopa/ft_koopa_extend_param_accesser.h>

#define FT_BC ftKoopaBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftKoopaExtendParamAccesser g_ftKoopaExtendParamAccesser;

ftClassInfoImpl<Fighter_Koopa, ftKoopa> g_ftClassInfoKoopa;

ftKoopa::ftKoopa(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftKoopaBuildConfig>(entryId,
                                         Fighter_Koopa,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftKoopa is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftKoopaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftKoopaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
