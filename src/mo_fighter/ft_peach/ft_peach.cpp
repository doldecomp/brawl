#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/peach/ft_peach.h>
#include <ft/peach/ft_peach_extend_param_accesser.h>

#define FT_BC ftPeachBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPeachExtendParamAccesser g_ftPeachExtendParamAccesser;

ftClassInfoImpl<Fighter_Peach, ftPeach> g_ftClassInfoPeach;

ftPeach::ftPeach(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPeachBuildConfig>(entryId,
                                         Fighter_Peach,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPeach is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPeachInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPeachInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_103_72A4(u8* p) { return *(u8*)(p + 0x4); }
void fn_103_9058() {}
void fn_103_9A40() {}
int fn_103_9A44() { return 0x0; }
void fn_103_9BC4() {}
void fn_103_9D4C() {}
u8 fn_103_9D50(u8* p) { return *(u8*)(p + 0x44); }
void fn_103_9D58() {}
void fn_103_9D98() {}
void fn_103_9D9C() {}
void fn_103_9E2C() {}
void fn_103_9E58() {}
void fn_103_9E5C() {}
void fn_103_9E60() {}
void fn_103_9E64() {}
void fn_103_9E68() {}
void fn_103_9E6C() {}
void fn_103_9E70() {}
void fn_103_9E74() {}
void fn_103_9E78() {}
void fn_103_9E7C() {}
void fn_103_9E80() {}
void fn_103_9E84() {}
void fn_103_9E88() {}
void fn_103_9E8C() {}
void fn_103_9E90() {}
int fn_103_9E94() { return 0x0; }
void fn_103_9E9C() {}
void fn_103_9EA0() {}
void fn_103_9EA4() {}
void fn_103_9EA8() {}
void fn_103_9ED4() {}
void fn_103_9ED8() {}
void fn_103_9EDC() {}
void fn_103_9EE0() {}
void fn_103_9EE4() {}
int fn_103_9EE8(u8* p) { return *(int*)(p + 0x110); }
int fn_103_9F00() { return 0x0; }
void fn_103_9F08() {}
void fn_103_9F0C() {}
void fn_103_9F10() {}
void fn_103_9F14() {}
int fn_103_9F18() { return 0x0; }
int fn_103_9F20() { return 0x0; }
void fn_103_9F28() {}
void fn_103_9F2C() {}
void fn_103_9F30() {}
void fn_103_9F34() {}
int fn_103_A0A8(u8* p) { return *(int*)(p + 0x20); }
int fn_103_A184(u8* p) { return *(int*)(p + 0x18); }
int fn_103_A21C(u8* p) { return *(int*)(p + 0x10); }
int fn_103_B328() { return 0x3; }
void fn_103_C138() {}
int fn_103_C93C() { return 0x0; }
void fn_103_C978() {}
int fn_103_CA24() { return 0x0; }
int fn_103_CAD4() { return 0x0; }
int fn_103_CB84() { return 0x0; }
void fn_103_CBC0() {}
int fn_103_CC6C() { return 0x0; }
void fn_103_CCA8() {}
int fn_103_CD54() { return 0x0; }
void fn_103_CD90() {}
int fn_103_CE3C() { return 0x0; }
void fn_103_CE78() {}
int fn_103_CF24() { return 0x0; }

}
