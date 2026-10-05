#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ganon/ft_ganon.h>
#include <ft/ganon/ft_ganon_extend_param_accesser.h>

#define FT_BC ftGanonBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftGanonExtendParamAccesser g_ftGanonExtendParamAccesser;

ftClassInfoImpl<Fighter_Ganon, ftGanon> g_ftClassInfoGanon;

ftGanon::ftGanon(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftGanonBuildConfig>(entryId,
                                         Fighter_Ganon,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftGanon is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftGanonInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftGanonInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
