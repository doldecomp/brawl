#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/captain/ft_captain.h>
#include <ft/captain/ft_captain_extend_param_accesser.h>

#define FT_BC ftCaptainBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftCaptainExtendParamAccesser g_ftCaptainExtendParamAccesser;

ftClassInfoImpl<Fighter_Captain, ftCaptain> g_ftClassInfoCaptain;

ftCaptain::ftCaptain(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftCaptainBuildConfig>(entryId,
                                         Fighter_Captain,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftCaptain is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftCaptainInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftCaptainInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_100_6C60(u8* p) { return *(u8*)(p + 0x4); }
void fn_100_9670() {}
void fn_100_9674() {}
int fn_100_97E8(u8* p) { return *(int*)(p + 0x20); }
int fn_100_98C4(u8* p) { return *(int*)(p + 0x18); }
void fn_100_A9D8(u8* p, u8 v) { *(u8*)(p + 0x405c) = v; }
void fn_100_B7DC() {}
void fn_100_BF74() {}
void fn_100_C05C() {}
void fn_100_C1F4() {}
void fn_100_C2DC() {}
void fn_100_C3C4() {}
void fn_100_C4AC() {}
void fn_100_C594() {}

}
