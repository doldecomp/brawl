#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/diddy/ft_diddy.h>
#include <ft/diddy/ft_diddy_extend_param_accesser.h>

#define FT_BC ftDiddyBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftDiddyExtendParamAccesser g_ftDiddyExtendParamAccesser;

ftClassInfoImpl<Fighter_Diddy, ftDiddy> g_ftClassInfoDiddy;

ftDiddy::ftDiddy(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftDiddyBuildConfig>(entryId,
                                         Fighter_Diddy,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftDiddy is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftDiddyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftDiddyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_115_672C(u8* p) { return *(u8*)(p + 0x4); }
void fn_115_8734() {}
void fn_115_9A18() {}
void fn_115_9A1C() {}
int fn_115_9B48() { return 0x0; }
void fn_115_9D5C() {}
void fn_115_9ED4() {}
u8 fn_115_9ED8(u8* p) { return *(u8*)(p + 0x44); }
void fn_115_9EE0() {}
void fn_115_9F20() {}
void fn_115_9F24() {}
void fn_115_9FDC() {}
void fn_115_9FE0() {}
void fn_115_9FE4() {}
void fn_115_9FE8() {}
void fn_115_9FEC() {}
void fn_115_9FF0() {}
void fn_115_9FF4() {}
void fn_115_9FF8() {}
void fn_115_9FFC() {}
void fn_115_A000() {}
void fn_115_A004() {}
void fn_115_A008() {}
void fn_115_A00C() {}
void fn_115_A010() {}
void fn_115_A014() {}
int fn_115_A018() { return 0x0; }
void fn_115_A020() {}
void fn_115_A024() {}
void fn_115_A028() {}
void fn_115_A02C() {}
void fn_115_A058() {}
void fn_115_A05C() {}
void fn_115_A060() {}
void fn_115_A064() {}
void fn_115_A068() {}
int fn_115_A06C(u8* p) { return *(int*)(p + 0x110); }
int fn_115_A084() { return 0x0; }
void fn_115_A08C() {}
void fn_115_A090() {}
void fn_115_A094() {}
void fn_115_A098() {}
int fn_115_A09C() { return 0x0; }
int fn_115_A0A4() { return 0x0; }
void fn_115_A0AC() {}
void fn_115_A0B0() {}
void fn_115_A0B4() {}
void fn_115_A0B8() {}
void fn_115_A0BC() {}
int fn_115_A270(u8* p) { return *(int*)(p + 0x20); }
int fn_115_A34C(u8* p) { return *(int*)(p + 0x18); }
int fn_115_A3E4(u8* p) { return *(int*)(p + 0x10); }
int fn_115_A4A4() { return 0x0; }
int fn_115_B97C() { return 0x4; }
void fn_115_C880() {}
void fn_115_CF8C() {}
int fn_115_CFC8() { return 0x8; }
void fn_115_D010() {}
int fn_115_D0BC() { return 0x0; }
void fn_115_D0F8() {}
int fn_115_D1A4() { return 0x0; }
void fn_115_D1E0() {}
int fn_115_D28C() { return 0x0; }
void fn_115_D2C8() {}
int fn_115_D374() { return 0x0; }
void fn_115_D3B0() {}
int fn_115_D45C() { return 0x0; }
void fn_115_D498() {}
int fn_115_D544() { return 0x0; }
void fn_115_D580() {}
int fn_115_D62C() { return 0x0; }
void fn_115_D668() {}
int fn_115_D714() { return 0x0; }

}
