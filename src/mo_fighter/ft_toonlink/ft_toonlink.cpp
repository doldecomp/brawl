#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/toonlink/ft_toonlink.h>
#include <ft/toonlink/ft_toonlink_extend_param_accesser.h>

#define FT_BC ftToonLinkBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftToonLinkExtendParamAccesser g_ftToonLinkExtendParamAccesser;

ftClassInfoImpl<Fighter_ToonLink, ftToonLink> g_ftClassInfoToonLink;

ftToonLink::ftToonLink(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftToonLinkBuildConfig>(entryId,
                                         Fighter_ToonLink,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftToonLink is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftToonLinkInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftToonLinkInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
