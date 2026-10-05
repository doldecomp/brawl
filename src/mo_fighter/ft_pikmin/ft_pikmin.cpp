#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/pikmin/ft_pikmin.h>
#include <ft/pikmin/ft_pikmin_extend_param_accesser.h>

#define FT_BC ftPikminBuildConfig
#include <ft/builder/ft_builder_noinline.h>

// MATCH-ONLY: unlike the other fighters, ftPikmin calls the ftFighterBuilder constructor out of line (it has a large
// constructor body of its own that MWCC's inliner no longer fits it into).
#pragma dont_inline on
template ftFighterBuilder<ftPikminBuildConfig>::ftFighterBuilder(s32, ftKind, Heaps::HeapType, Heaps::HeapType, Heaps::HeapType);
#pragma dont_inline off

ftPikminExtendParamAccesser g_ftPikminExtendParamAccesser;

ftClassInfoImpl<Fighter_Pikmin, ftPikmin> g_ftClassInfoPikmin;

ftPikmin::ftPikmin(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPikminBuildConfig>(entryId,
                                         Fighter_Pikmin,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPikmin is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPikminInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPikminInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

int fn_113_686C(u8* p) { return *(int*)(p + 0x60); }
int fn_113_7FA8() { return 0x0; }
int fn_113_7FBC() { return 0x0; }
int fn_113_8094() { return 0x0; }
int fn_113_809C() { return 0x0; }
int fn_113_80A4() { return 0x0; }
int fn_113_80AC() { return 0x0; }
int fn_113_80D8() { return 0x0; }
int fn_113_80E0() { return 0x0; }
u8 fn_113_80F4(u8* p) { return *(u8*)(p + 0x4); }
void fn_113_9F54() {}
int fn_113_C534() { return 0x0; }
void fn_113_C5F4() {}
void fn_113_C810() {}
u8 fn_113_C814(u8* p) { return *(u8*)(p + 0x44); }
void fn_113_C81C() {}
void fn_113_C85C() {}
void fn_113_C860() {}
void fn_113_C8F0() {}
void fn_113_C91C() {}
void fn_113_C920() {}
void fn_113_C924() {}
void fn_113_C928() {}
void fn_113_C92C() {}
void fn_113_C930() {}
void fn_113_C934() {}
void fn_113_C938() {}
void fn_113_C93C() {}
void fn_113_C940() {}
void fn_113_C944() {}
void fn_113_C948() {}
void fn_113_C94C() {}
void fn_113_C950() {}
void fn_113_C954() {}
int fn_113_C958() { return 0x0; }
void fn_113_C960() {}
void fn_113_C964() {}
void fn_113_C968() {}
void fn_113_C96C() {}
void fn_113_C998() {}
void fn_113_C99C() {}
void fn_113_C9A0() {}
void fn_113_C9A4() {}
void fn_113_C9A8() {}
int fn_113_C9AC(u8* p) { return *(int*)(p + 0x110); }
int fn_113_C9C4() { return 0x0; }
void fn_113_C9CC() {}
void fn_113_C9D0() {}
void fn_113_C9D4() {}
void fn_113_C9D8() {}
int fn_113_C9DC() { return 0x0; }
int fn_113_C9E4() { return 0x0; }
void fn_113_C9EC() {}
void fn_113_C9F0() {}
void fn_113_C9F4() {}
void fn_113_C9F8() {}
void fn_113_C9FC() {}
int fn_113_CB70() { return 0x1; }
void fn_113_CB78() {}
int fn_113_CB7C() { return 0x0; }
void fn_113_CB84() {}
int fn_113_CB88() { return 0x0; }
void fn_113_CB90() {}
void fn_113_CB94() {}
void fn_113_CB98() {}
void fn_113_CB9C() {}
void fn_113_CBA0() {}
void fn_113_CBA4() {}
void fn_113_CBA8() {}
void fn_113_CBAC() {}
int fn_113_CBB0(u8* p) { return *(int*)(p + 0x20); }
int fn_113_CC8C(u8* p) { return *(int*)(p + 0x18); }
int fn_113_CD24(u8* p) { return *(int*)(p + 0x10); }
int fn_113_E000() { return 0x3; }
void fn_113_EEFC() {}
void fn_113_F678() {}
int fn_113_F724() { return 0x0; }
void fn_113_F760() {}
int fn_113_F80C() { return 0x0; }
void fn_113_F848() {}
int fn_113_F8F4() { return 0x0; }
void fn_113_F930() {}
int fn_113_F9DC() { return 0x0; }
void fn_113_FA18() {}
int fn_113_FAC4() { return 0x0; }
void fn_113_FB00() {}
int fn_113_FBAC() { return 0x0; }
void fn_113_FBE8() {}
int fn_113_FC94() { return 0x0; }
void fn_113_FCD0() {}
int fn_113_FD7C() { return 0x0; }

}
