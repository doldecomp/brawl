#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/pit/ft_pit.h>
#include <ft/pit/ft_pit_extend_param_accesser.h>

#define FT_BC ftPitBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPitExtendParamAccesser g_ftPitExtendParamAccesser;

ftClassInfoImpl<Fighter_Pit, ftPit> g_ftClassInfoPit;

ftPit::ftPit(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPitBuildConfig>(entryId,
                                         Fighter_Pit,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPit is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPitInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPitInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
