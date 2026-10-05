#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/kirby/ft_kirby.h>
#include <ft/kirby/ft_kirby_extend_param_accesser.h>

#define FT_BC ftKirbyBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftKirbyExtendParamAccesser g_ftKirbyExtendParamAccesser;

ftClassInfoImpl<Fighter_Kirby, ftKirby> g_ftClassInfoKirby;

ftKirby::ftKirby(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftKirbyBuildConfig>(entryId,
                                         Fighter_Kirby,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftKirby is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftKirbyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftKirbyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_96_28D0(u8* p) { return *(u8*)(p + 0x4); }
void fn_96_AB5C() {}
void fn_96_AF94() {}
int fn_96_BC64(u8* p) { return *(int*)(p + 0x110); }
int fn_96_BC6C(u8* p) { return *(int*)(p + 0x28); }
int fn_96_C17C(u8* p) { return *(int*)(p + 0xc0); }
int fn_96_E240() { return 0; }
void fn_96_EF10() {}
void fn_96_F014() {}
u8 fn_96_F018(u8* p) { return *(u8*)(p + 0x44); }
void fn_96_F020() {}
void fn_96_F060() {}
void fn_96_F064() {}
void fn_96_F0F4() {}
void fn_96_F120() {}
void fn_96_F124() {}
void fn_96_F128() {}
void fn_96_F12C() {}
void fn_96_F130() {}
void fn_96_F134() {}
void fn_96_F138() {}
void fn_96_F13C() {}
void fn_96_F140() {}
void fn_96_F144() {}
void fn_96_F148() {}
void fn_96_F14C() {}
int fn_96_F150() { return 0; }
void fn_96_F158() {}
void fn_96_F15C() {}
void fn_96_F160() {}
void fn_96_F164() {}
void fn_96_F190() {}
void fn_96_F194() {}
void fn_96_F198() {}
void fn_96_F19C() {}
void fn_96_F1A0() {}
int fn_96_F1B4() { return 0; }
void fn_96_F1BC() {}
void fn_96_F1C0() {}
void fn_96_F1C4() {}
int fn_96_F1C8() { return 0; }
int fn_96_F1D0() { return 0; }
void fn_96_F1D8() {}
void fn_96_F1DC() {}
void fn_96_F1E0() {}
void fn_96_F1E4() {}
void fn_96_F204() {}
void fn_96_F208() {}
void fn_96_F20C() {}
void fn_96_F210() {}
u8* fn_96_F2D4(u8* p) { return p + 0x458; }
u8* fn_96_F2DC(u8* p) { return p + 0x3c8; }
u8* fn_96_F2E4(u8* p) { return p + 0x8; }
u8* fn_96_F2EC(u8* p) { return p + 0x84; }
u8* fn_96_F2F4(u8* p) { return p + 0x70; }
u8* fn_96_F2FC(u8* p) { return p + 0x5c; }
u8* fn_96_F304(u8* p) { return p + 0x48; }
u8* fn_96_F30C(u8* p) { return p + 0x34; }
u8* fn_96_F314(u8* p) { return p + 0x20; }
u8* fn_96_F31C(u8* p) { return p + 0x8; }
int fn_96_F384() { return 0; }
int fn_96_F38C() { return 0; }
void fn_96_F394() {}
void fn_96_F398() {}
void fn_96_F39C() {}
void fn_96_F3A0() {}
void fn_96_F3A4() {}
void fn_96_F3A8() {}
int fn_96_F3AC(u8* p) { return *(int*)(p + 0x20); }
int fn_96_F488(u8* p) { return *(int*)(p + 0x18); }
int fn_96_F520(u8* p) { return *(int*)(p + 0x10); }
int fn_96_F5E0() { return 0; }
int fn_96_115E8() { return 12; }
void fn_96_12530() {}
void fn_96_12C28() {}
int fn_96_12C64() { return 8; }
void fn_96_12CAC() {}
int fn_96_12D58() { return 0; }
int fn_96_12E08() { return 0; }
int fn_96_12EB8() { return 0; }
int fn_96_12F68() { return 0; }
void fn_96_12FA4() {}
int fn_96_13050() { return 0; }
void fn_96_1308C() {}
int fn_96_13138() { return 0; }
void fn_96_13174() {}
int fn_96_13220() { return 0; }
void fn_96_1325C() {}
int fn_96_13308() { return 0; }

}
