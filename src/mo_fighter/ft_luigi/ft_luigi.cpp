#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/luigi/ft_luigi.h>
#include <ft/luigi/ft_luigi_extend_param_accesser.h>

#define FT_BC ftLuigiBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftLuigiExtendParamAccesser g_ftLuigiExtendParamAccesser;

ftClassInfoImpl<Fighter_Luigi, ftLuigi> g_ftClassInfoLuigi;

ftLuigi::ftLuigi(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftLuigiBuildConfig>(entryId,
                                         Fighter_Luigi,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftLuigi is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftLuigiInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftLuigiInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
