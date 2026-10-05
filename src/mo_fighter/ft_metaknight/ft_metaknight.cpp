#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/metaknight/ft_metaknight.h>
#include <ft/metaknight/ft_metaknight_extend_param_accesser.h>

#define FT_BC ftMetaknightBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftMetaknightExtendParamAccesser g_ftMetaknightExtendParamAccesser;

ftClassInfoImpl<Fighter_MetaKnight, ftMetaknight> g_ftClassInfoMetaknight;

ftMetaknight::ftMetaknight(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftMetaknightBuildConfig>(entryId,
                                         Fighter_MetaKnight,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftMetaknight is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftMetaknightInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftMetaknightInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_111_5F38(u8* p) { return *(u8*)(p + 0x4); }
u8 fn_111_8474(u8* p) { return *(u8*)(p + 0x44); }
void fn_111_8580() {}
void fn_111_8584() {}
void fn_111_8588() {}
void fn_111_858C() {}
void fn_111_8590() {}
void fn_111_8594() {}
void fn_111_8598() {}
void fn_111_859C() {}
void fn_111_85A0() {}
void fn_111_85A4() {}
void fn_111_85A8() {}
void fn_111_85AC() {}
void fn_111_85B0() {}
void fn_111_85BC() {}
void fn_111_85C0() {}
void fn_111_85C4() {}
void fn_111_85C8() {}
void fn_111_85F4() {}
void fn_111_85F8() {}
void fn_111_85FC() {}
void fn_111_8600() {}
void fn_111_8604() {}
int fn_111_8608(u8* p) { return *(int*)(p + 0x110); }
void fn_111_8628() {}
void fn_111_862C() {}
void fn_111_8630() {}
void fn_111_8644() {}
void fn_111_8648() {}
void fn_111_864C() {}
void fn_111_8650() {}
void fn_111_8654() {}
void fn_111_8658() {}
u8* fn_111_871C(u8* p) { return p + 0x458; }
u8* fn_111_8724(u8* p) { return p + 0x3c8; }
u8* fn_111_872C(u8* p) { return p + 0x8; }
int fn_111_87CC(u8* p) { return *(int*)(p + 0x20); }
int fn_111_88A8(u8* p) { return *(int*)(p + 0x18); }
void fn_111_9800(u8* p, u8 v) { *(u8*)(p + 0x20bc) = v; }
void fn_111_A5EC() {}
void fn_111_AE98() {}

}
