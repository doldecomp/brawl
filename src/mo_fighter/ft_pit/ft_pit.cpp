#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/pit/ft_pit.h>
#include <ft/pit/ft_pit_extend_param_accesser.h>

#define FT_BC ftPitBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPitExtendParamAccesser g_ftPitExtendParamAccesser;

ftClassInfoImpl<Fighter_Pit, ftPit> g_ftClassInfoPit;

ftPit::ftPit(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPitBuildConfig>(entryId,
                                         Fighter_Pit,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPit is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPitInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPitInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_112_774C(u8* p) { return *(u8*)(p + 0x4); }
void fn_112_956C() {}
int fn_112_A2E0() { return 0x0; }
void fn_112_A448() {}
void fn_112_A5C0() {}
u8 fn_112_A5C4(u8* p) { return *(u8*)(p + 0x44); }
void fn_112_A5CC() {}
void fn_112_A60C() {}
void fn_112_A610() {}
void fn_112_A6A0() {}
void fn_112_A6CC() {}
void fn_112_A6D0() {}
void fn_112_A6D4() {}
void fn_112_A6D8() {}
void fn_112_A6DC() {}
void fn_112_A6E0() {}
void fn_112_A6E4() {}
void fn_112_A6E8() {}
void fn_112_A6EC() {}
void fn_112_A6F0() {}
void fn_112_A6F4() {}
void fn_112_A6F8() {}
void fn_112_A6FC() {}
void fn_112_A700() {}
void fn_112_A704() {}
int fn_112_A708() { return 0x0; }
void fn_112_A710() {}
void fn_112_A714() {}
void fn_112_A718() {}
void fn_112_A71C() {}
void fn_112_A748() {}
void fn_112_A74C() {}
void fn_112_A750() {}
void fn_112_A754() {}
void fn_112_A758() {}
int fn_112_A75C(u8* p) { return *(int*)(p + 0x110); }
int fn_112_A774() { return 0x0; }
void fn_112_A77C() {}
void fn_112_A780() {}
void fn_112_A784() {}
void fn_112_A788() {}
int fn_112_A78C() { return 0x0; }
int fn_112_A794() { return 0x0; }
void fn_112_A79C() {}
void fn_112_A7A0() {}
void fn_112_A7A4() {}
void fn_112_A7A8() {}
void fn_112_A7AC() {}
int fn_112_A920(u8* p) { return *(int*)(p + 0x20); }
int fn_112_A9FC(u8* p) { return *(int*)(p + 0x18); }
int fn_112_AA94(u8* p) { return *(int*)(p + 0x10); }
int fn_112_BDA8() { return 0x3; }
void fn_112_CC00() {}
void fn_112_D390() {}
int fn_112_D43C() { return 0x0; }
void fn_112_D478() {}
int fn_112_D524() { return 0x0; }
int fn_112_D5D4() { return 0x0; }
void fn_112_D610() {}
int fn_112_D6BC() { return 0x0; }
void fn_112_D6F8() {}
int fn_112_D7A4() { return 0x0; }
void fn_112_D7E0() {}
int fn_112_D88C() { return 0x0; }
void fn_112_D8C8() {}
int fn_112_D974() { return 0x0; }
void fn_112_D9B0() {}
int fn_112_DA5C() { return 0x0; }

}
