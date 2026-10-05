#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/link/ft_link.h>
#include <ft/link/ft_link_extend_param_accesser.h>

#define FT_BC ftLinkBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftLinkExtendParamAccesser g_ftLinkExtendParamAccesser;

ftClassInfoImpl<Fighter_Link, ftLink> g_ftClassInfoLink;

ftLink::ftLink(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftLinkBuildConfig>(entryId,
                                         Fighter_Link,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftLink is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftLinkInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftLinkInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
