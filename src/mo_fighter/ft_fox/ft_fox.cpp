#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/fox/ft_fox.h>
#include <ft/fox/ft_fox_extend_param_accesser.h>

#define FT_BC ftFoxBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftFoxExtendParamAccesser g_ftFoxExtendParamAccesser;

ftClassInfoImpl<Fighter_Fox, ftFox> g_ftClassInfoFox;

ftFox::ftFox(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftFoxBuildConfig>(entryId,
                                         Fighter_Fox,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftFox is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftFoxInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftFoxInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
