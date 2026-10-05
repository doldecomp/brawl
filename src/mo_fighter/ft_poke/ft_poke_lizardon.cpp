#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/poke/ft_poke_lizardon.h>
#include <ft/poke/ft_poke_lizardon_extend_param_accesser.h>

#define FT_BC ftPokeLizardonBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPokeLizardonExtendParamAccesser g_ftPokeLizardonExtendParamAccesser;

ftClassInfoImpl<Fighter_PokeLizardon, ftPokeLizardon> g_ftClassInfoPokeLizardon;

ftPokeLizardon::ftPokeLizardon(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPokeLizardonBuildConfig>(entryId,
                                         Fighter_PokeLizardon,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPokeLizardon is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPokeLizardonInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPokeLizardonInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
