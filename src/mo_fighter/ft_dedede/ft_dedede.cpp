#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/dedede/ft_dedede.h>
#include <ft/dedede/ft_dedede_extend_param_accesser.h>

#define FT_BC ftDededeBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftDededeExtendParamAccesser g_ftDededeExtendParamAccesser;

ftClassInfoImpl<Fighter_Dedede, ftDedede> g_ftClassInfoDedede;

ftDedede::ftDedede(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftDededeBuildConfig>(entryId,
                                         Fighter_Dedede,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftDedede is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftDededeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftDededeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_117_67D4(u8* p) { return *(u8*)(p + 0x4); }
void fn_117_8A60() {}
int fn_117_99D8(u8* p) { return *(int*)(p + 0xb8); }
int fn_117_9F40() { return 0x0; }
void fn_117_A13C() {}
void fn_117_A2B4() {}
u8 fn_117_A2B8(u8* p) { return *(u8*)(p + 0x44); }
void fn_117_A2C0() {}
void fn_117_A300() {}
void fn_117_A304() {}
void fn_117_A394() {}
void fn_117_A3C0() {}
void fn_117_A3C4() {}
void fn_117_A3C8() {}
void fn_117_A3CC() {}
void fn_117_A3D0() {}
void fn_117_A3D4() {}
void fn_117_A3D8() {}
void fn_117_A3DC() {}
void fn_117_A3E0() {}
void fn_117_A3E4() {}
void fn_117_A3E8() {}
void fn_117_A3EC() {}
void fn_117_A3F0() {}
void fn_117_A3F4() {}
void fn_117_A3F8() {}
int fn_117_A3FC() { return 0x0; }
void fn_117_A404() {}
void fn_117_A408() {}
void fn_117_A40C() {}
void fn_117_A410() {}
void fn_117_A43C() {}
void fn_117_A440() {}
void fn_117_A444() {}
void fn_117_A448() {}
void fn_117_A44C() {}
int fn_117_A450(u8* p) { return *(int*)(p + 0x110); }
int fn_117_A468() { return 0x0; }
void fn_117_A470() {}
void fn_117_A474() {}
void fn_117_A478() {}
void fn_117_A47C() {}
int fn_117_A480() { return 0x0; }
int fn_117_A488() { return 0x0; }
void fn_117_A490() {}
void fn_117_A494() {}
void fn_117_A498() {}
void fn_117_A49C() {}
void fn_117_A4A0() {}
int fn_117_A654(u8* p) { return *(int*)(p + 0x20); }
int fn_117_A730(u8* p) { return *(int*)(p + 0x18); }
int fn_117_A7C8(u8* p) { return *(int*)(p + 0x10); }
int fn_117_A888() { return 0x0; }
int fn_117_C104() { return 0x5; }
void fn_117_D0F8() {}
void fn_117_D804() {}
int fn_117_D840() { return 0x8; }
void fn_117_D888() {}
int fn_117_D934() { return 0x0; }
void fn_117_D970() {}
int fn_117_DA1C() { return 0x0; }
void fn_117_DA58() {}
int fn_117_DB04() { return 0x0; }
void fn_117_DB40() {}
int fn_117_DBEC() { return 0x0; }
void fn_117_DC28() {}
int fn_117_DCD4() { return 0x0; }
void fn_117_DD10() {}
int fn_117_DDBC() { return 0x0; }
void fn_117_DDF8() {}
int fn_117_DEA4() { return 0x0; }
void fn_117_DEE0() {}
int fn_117_DF8C() { return 0x0; }

}
