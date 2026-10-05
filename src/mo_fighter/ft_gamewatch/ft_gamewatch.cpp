#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/gamewatch/ft_gamewatch.h>
#include <ft/gamewatch/ft_gamewatch_extend_param_accesser.h>

#define FT_BC ftGameWatchBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftGameWatchExtendParamAccesser g_ftGameWatchExtendParamAccesser;

ftClassInfoImpl<Fighter_GameWatch, ftGameWatch> g_ftClassInfoGameWatch;

ftGameWatch::ftGameWatch(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftGameWatchBuildConfig>(entryId,
                                         Fighter_GameWatch,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftGameWatch is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftGameWatchInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftGameWatchInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_107_8720(u8* p) { return *(u8*)(p + 0x4); }
void fn_107_A810() {}
void fn_107_B648() {}
int fn_107_BEAC() { return 0x0; }
void fn_107_BFB8() {}
void fn_107_C140() {}
u8 fn_107_C144(u8* p) { return *(u8*)(p + 0x44); }
void fn_107_C14C() {}
void fn_107_C18C() {}
void fn_107_C190() {}
void fn_107_C220() {}
void fn_107_C24C() {}
void fn_107_C250() {}
void fn_107_C254() {}
void fn_107_C258() {}
void fn_107_C25C() {}
void fn_107_C260() {}
void fn_107_C264() {}
void fn_107_C268() {}
void fn_107_C26C() {}
void fn_107_C270() {}
void fn_107_C274() {}
void fn_107_C278() {}
void fn_107_C27C() {}
void fn_107_C280() {}
void fn_107_C284() {}
int fn_107_C288() { return 0x0; }
void fn_107_C290() {}
void fn_107_C294() {}
void fn_107_C298() {}
void fn_107_C29C() {}
void fn_107_C2C8() {}
void fn_107_C2CC() {}
void fn_107_C2D0() {}
void fn_107_C2D4() {}
void fn_107_C2D8() {}
int fn_107_C2DC(u8* p) { return *(int*)(p + 0x110); }
int fn_107_C2F4() { return 0x0; }
void fn_107_C2FC() {}
void fn_107_C300() {}
int fn_107_C304() { return 0x0; }
int fn_107_C30C() { return 0x0; }
void fn_107_C314() {}
void fn_107_C318() {}
void fn_107_C31C() {}
void fn_107_C320() {}
void fn_107_C324() {}
void fn_107_C328() {}
int fn_107_C49C(u8* p) { return *(int*)(p + 0x20); }
int fn_107_C578(u8* p) { return *(int*)(p + 0x18); }
int fn_107_C610(u8* p) { return *(int*)(p + 0x10); }
int fn_107_C6D0() { return 0x0; }
int fn_107_DFFC() { return 0x7; }
void fn_107_EEC8() {}
void fn_107_F5D4() {}
int fn_107_F610() { return 0x8; }
void fn_107_F658() {}
int fn_107_F704() { return 0x0; }
void fn_107_F740() {}
int fn_107_F7EC() { return 0x0; }
void fn_107_F828() {}
int fn_107_F8D4() { return 0x0; }
void fn_107_F910() {}
int fn_107_F9BC() { return 0x0; }
void fn_107_F9F8() {}
int fn_107_FAA4() { return 0x0; }
void fn_107_FAE0() {}
int fn_107_FB8C() { return 0x0; }
void fn_107_FBC8() {}
int fn_107_FC74() { return 0x0; }
void fn_107_FCB0() {}
int fn_107_FD5C() { return 0x0; }

}
