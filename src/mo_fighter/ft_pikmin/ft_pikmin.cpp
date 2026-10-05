#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/pikmin/ft_pikmin.h>
#include <ft/pikmin/ft_pikmin_extend_param_accesser.h>

#define FT_BC ftPikminBuildConfig
#include <ft/builder/ft_builder_noinline.h>

// MATCH-ONLY: unlike the other fighters, ftPikmin calls the ftFighterBuilder constructor out of line (it has a large
// constructor body of its own that MWCC's inliner no longer fits it into).
#pragma dont_inline on
template ftFighterBuilder<ftPikminBuildConfig>::ftFighterBuilder(s32, ftKind, Heaps::HeapType, Heaps::HeapType, Heaps::HeapType);
#pragma dont_inline off

ftPikminExtendParamAccesser g_ftPikminExtendParamAccesser;

ftClassInfoImpl<Fighter_Pikmin, ftPikmin> g_ftClassInfoPikmin;

ftPikmin::ftPikmin(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPikminBuildConfig>(entryId,
                                         Fighter_Pikmin,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPikmin is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPikminInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPikminInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
