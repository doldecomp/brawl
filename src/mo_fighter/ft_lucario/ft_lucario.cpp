#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/lucario/ft_lucario.h>
#include <ft/lucario/ft_lucario_extend_param_accesser.h>

#define FT_BC ftLucarioBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftLucarioExtendParamAccesser g_ftLucarioExtendParamAccesser;

ftClassInfoImpl<Fighter_Lucario, ftLucario> g_ftClassInfoLucario;

ftLucario::ftLucario(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftLucarioBuildConfig>(entryId,
                                         Fighter_Lucario,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftLucario is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftLucarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftLucarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
