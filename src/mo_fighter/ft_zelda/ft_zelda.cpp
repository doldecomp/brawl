#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/zelda/ft_zelda.h>
#include <ft/zelda/ft_zelda_extend_param_accesser.h>

#define FT_BC ftZeldaBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftZeldaExtendParamAccesser g_ftZeldaExtendParamAccesser;

ftClassInfoImpl<Fighter_Zelda, ftZelda> g_ftClassInfoZelda;

ftZelda::ftZelda(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftZeldaBuildConfig>(entryId,
                                         Fighter_Zelda,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftZelda is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftZeldaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftZeldaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
