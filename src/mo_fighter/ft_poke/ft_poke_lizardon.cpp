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

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_116_7384(u8* p) { return *(u8*)(p + 0x4); }
void fn_116_929C() {}
void fn_116_9718() {}
void fn_116_9A98() {}
void fn_116_9DA4() {}
void fn_116_9EC4() {}
int fn_116_A148(u8* p) { return *(int*)(p + 0x28); }
int fn_116_A150() { return 0x0; }
void fn_116_A274() {}
void fn_116_A408() {}
u8 fn_116_A40C(u8* p) { return *(u8*)(p + 0x44); }
void fn_116_A414() {}
void fn_116_A454() {}
void fn_116_A458() {}
void fn_116_A510() {}
void fn_116_A514() {}
void fn_116_A518() {}
void fn_116_A51C() {}
void fn_116_A520() {}
void fn_116_A524() {}
void fn_116_A528() {}
void fn_116_A52C() {}
void fn_116_A530() {}
void fn_116_A534() {}
void fn_116_A538() {}
void fn_116_A53C() {}
void fn_116_A540() {}
void fn_116_A56C() {}
void fn_116_A570() {}
void fn_116_A574() {}
void fn_116_A578() {}
void fn_116_A57C() {}
int fn_116_A580(u8* p) { return *(int*)(p + 0x110); }
int fn_116_A598() { return 0x0; }
void fn_116_A5A0() {}
void fn_116_A5A4() {}
void fn_116_A5A8() {}
int fn_116_A5AC() { return 0x0; }
void fn_116_A5B4() {}
void fn_116_A5B8() {}
void fn_116_A5BC() {}
int fn_116_A5C0() { return 0x850; }
void fn_116_A5C8() {}
void fn_116_A5CC() {}
void fn_116_A5D0() {}
int fn_116_A5D4() { return 0x0; }
void fn_116_A5DC() {}
int fn_116_A5E0() { return 0x0; }
void fn_116_A5E8() {}
void fn_116_A5EC() {}
int fn_116_A760(u8* p) { return *(int*)(p + 0x20); }
int fn_116_A83C(u8* p) { return *(int*)(p + 0x18); }
int fn_116_A8D4(u8* p) { return *(int*)(p + 0x10); }
int fn_116_BC58() { return 0x3; }
void fn_116_CB00() {}
void fn_116_D290() {}
int fn_116_D33C() { return 0x0; }
void fn_116_D378() {}
int fn_116_D424() { return 0x0; }
void fn_116_D460() {}
int fn_116_D50C() { return 0x0; }
void fn_116_D548() {}
int fn_116_D5F4() { return 0x0; }
void fn_116_D630() {}
int fn_116_D6DC() { return 0x0; }
void fn_116_D718() {}
int fn_116_D7C4() { return 0x0; }
void fn_116_D800() {}
int fn_116_D8AC() { return 0x0; }
void fn_116_D8E8() {}
int fn_116_D994() { return 0x0; }

}
