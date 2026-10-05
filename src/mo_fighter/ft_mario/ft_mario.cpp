#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/mario/ft_mario.h>
#include <ft/mario/ft_mario_extend_param_accesser.h>

#define FT_BC ftMarioBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftMarioExtendParamAccesser g_ftMarioExtendParamAccesser;
ftMarioDExtendParamAccesser g_ftMarioDExtendParamAccesser;

ftClassInfoImpl<Fighter_Mario, ftMario> g_ftClassInfoMario;
ftClassInfoImpl<Fighter_MarioD, ftMarioD> g_ftClassInfoMarioD;

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
