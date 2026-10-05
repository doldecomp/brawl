#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/samus/ft_samus.h>
#include <ft/samus/ft_samus_extend_param_accesser.h>

#define FT_BC ftSamusBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftSamusExtendParamAccesser g_ftSamusExtendParamAccesser;

ftClassInfoImpl<Fighter_Samus, ftSamus> g_ftClassInfoSamus;

ftSamus::ftSamus(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftSamusBuildConfig>(entryId,
                                         Fighter_Samus,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftSamus is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftSamusInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftSamusInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_94_6CF8(u8* p) { return *(u8*)(p + 0x4); }
int fn_94_A630(u8* p) { return *(int*)(p + 0x28); }
u8 fn_94_A8D0(u8* p) { return *(u8*)(p + 0x44); }
void fn_94_A9E0() {}
void fn_94_A9E4() {}
void fn_94_A9E8() {}
void fn_94_A9EC() {}
void fn_94_A9F0() {}
void fn_94_A9F4() {}
void fn_94_A9F8() {}
void fn_94_A9FC() {}
void fn_94_AA00() {}
void fn_94_AA04() {}
void fn_94_AA08() {}
void fn_94_AA0C() {}
void fn_94_AA10() {}
void fn_94_AA1C() {}
void fn_94_AA20() {}
void fn_94_AA24() {}
void fn_94_AA28() {}
void fn_94_AA54() {}
void fn_94_AA58() {}
void fn_94_AA5C() {}
void fn_94_AA60() {}
void fn_94_AA64() {}
int fn_94_AA68(u8* p) { return *(int*)(p + 0x110); }
void fn_94_AA88() {}
void fn_94_AA8C() {}
void fn_94_AA90() {}
void fn_94_AA9C() {}
void fn_94_AAA0() {}
void fn_94_AAA4() {}
void fn_94_AAA8() {}
void fn_94_AAAC() {}
int fn_94_AAB0() { return 32683; }
void fn_94_AAB8() {}
u8* fn_94_ADEC(u8* p) { return p + 0x458; }
u8* fn_94_ADF4(u8* p) { return p + 0x3c8; }
u8* fn_94_ADFC(u8* p) { return p + 0x8; }
int fn_94_AE9C(u8* p) { return *(int*)(p + 0x20); }
int fn_94_AF78(u8* p) { return *(int*)(p + 0x18); }
void fn_94_DC2C() {}
void fn_94_E338() {}
int fn_94_E374() { return 8; }
void fn_94_E3BC() {}
void fn_94_E4A4() {}
void fn_94_E58C() {}
void fn_94_E674() {}
void fn_94_E75C() {}
void fn_94_E844() {}
void fn_94_E92C() {}
void fn_94_EA14() {}

}
