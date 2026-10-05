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
int fn_96_BC6C(u8* p) { return *(int*)(p + 0x28); }
int fn_96_C17C(u8* p) { return *(int*)(p + 0xc0); }
int fn_96_F3AC(u8* p) { return *(int*)(p + 0x20); }
int fn_96_F488(u8* p) { return *(int*)(p + 0x18); }
int fn_96_115E8() { return 12; }
void fn_96_12530() {}
void fn_96_12C28() {}
void fn_96_12CAC() {}
void fn_96_12FA4() {}
void fn_96_1308C() {}
void fn_96_13174() {}
void fn_96_1325C() {}

}
