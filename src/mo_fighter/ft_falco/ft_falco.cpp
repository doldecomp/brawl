#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/falco/ft_falco.h>
#include <ft/falco/ft_falco_extend_param_accesser.h>

#define FT_BC ftFalcoBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftFalcoExtendParamAccesser g_ftFalcoExtendParamAccesser;

ftClassInfoImpl<Fighter_Falco, ftFalco> g_ftClassInfoFalco;

ftFalco::ftFalco(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftFalcoBuildConfig>(entryId,
                                         Fighter_Falco,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftFalco is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftFalcoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftFalcoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
