#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/mario/ft_mario.h>

#define FT_BC ftMarioBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftMario::ftMario(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftMarioBuildConfig>(entryId,
                                         Fighter_Mario,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftMario is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftMarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftMarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
