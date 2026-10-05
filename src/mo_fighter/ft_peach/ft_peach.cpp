#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/peach/ft_peach.h>
#include <ft/peach/ft_peach_extend_param_accesser.h>

#define FT_BC ftPeachBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPeachExtendParamAccesser g_ftPeachExtendParamAccesser;

ftClassInfoImpl<Fighter_Peach, ftPeach> g_ftClassInfoPeach;

ftPeach::ftPeach(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPeachBuildConfig>(entryId,
                                         Fighter_Peach,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPeach is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPeachInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPeachInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
