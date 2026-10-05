#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ike/ft_ike.h>
#include <ft/ike/ft_ike_extend_param_accesser.h>

#define FT_BC ftIkeBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftIkeExtendParamAccesser g_ftIkeExtendParamAccesser;

ftClassInfoImpl<Fighter_Ike, ftIke> g_ftClassInfoIke;

ftIke::ftIke(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftIkeBuildConfig>(entryId,
                                         Fighter_Ike,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftIke is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftIkeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftIkeInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_119_58E4(u8* p) { return *(u8*)(p + 0x4); }
void fn_119_7610() {}
int fn_119_91E4() { return 0; }
void fn_119_9698() {}
void fn_119_969C() {}
void fn_119_96A0() {}
void fn_119_96A4() {}
int fn_119_96A8() { return 0; }
void fn_119_96EC() {}
void fn_119_96F0() {}
void fn_119_96F4() {}
void fn_119_96F8() {}
int fn_119_9714() { return 0; }
int fn_119_9728() { return 0; }
int fn_119_9730() { return 0; }
void fn_119_974C() {}
u8* fn_119_9810(u8* p) { return p + 0x458; }
u8* fn_119_9818(u8* p) { return p + 0x3C8; }
u8* fn_119_9820(u8* p) { return p + 0x8; }
int fn_119_9860(u8* p) { return *(int*)(p + 0x20); }
int fn_119_993C(u8* p) { return *(int*)(p + 0x18); }
int fn_119_99D4(u8* p) { return *(int*)(p + 0x10); }
int fn_119_A89C() { return 1; }
void fn_119_A8A4(u8* p, u8 v) { *(u8*)(p + 0x2318) = v; }
u8* fn_119_A8AC(u8* p) { return p + 0xA5CC; }
u8* fn_119_A8CC(u8* p) { return p + 0xA608; }
u8* fn_119_A8D8(u8* p) { return p + 0xAAC0; }
void fn_119_B690() {}
void fn_119_B778(u8* p) { *(u8*)(p + 0x31) = 0; }
void fn_119_B784(u8* p) { *(u8*)(p + 0x31) = 1; }
int fn_119_BECC() { return 0; }
int fn_119_BFB4() { return 0; }
int fn_119_C09C() { return 0; }
int fn_119_C184() { return 0; }
int fn_119_C26C() { return 0; }
int fn_119_C354() { return 0; }
int fn_119_C43C() { return 0; }
int fn_119_C524() { return 0; }

}

// Placeholders for weak inline methods of library classes (their names exist in sora_melee, so the REL copies cannot be renamed): the shim calls the inline method.
extern "C" {

bool fn_119_98DC(const soGeneralWorkSimple* p, u32 a0, u32 a1) { return p->soGeneralWorkSimple::isFlag(a0, a1); }
void fn_119_98F8(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::offFlag(a0, a1); }
void fn_119_9910(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::clearFlag(a0); }
void fn_119_9924(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::onFlag(a0, a1); }
void fn_119_996C(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::mulFloatWork(a0, a1); }
void fn_119_9984(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::subFloatWork(a0, a1); }
void fn_119_999C(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::addFloatWork(a0, a1); }
void fn_119_99B4(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::setFloatWork(a0, a1); }
float fn_119_99C4(const soGeneralWorkSimple* p, u32 a0) { return p->soGeneralWorkSimple::getFloatWork(a0); }
void fn_119_99DC(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::decIntWork(a0); }
void fn_119_99F4(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::incIntWork(a0); }
void fn_119_9A0C(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::divIntWork(a0, a1); }
void fn_119_9A2C(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::mulIntWork(a0, a1); }
void fn_119_9A44(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::subIntWork(a0, a1); }
void fn_119_9A5C(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::addIntWork(a0, a1); }
void fn_119_9A74(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::setIntWork(a0, a1); }
Vec2f fn_119_B7A4(soKineticEnergyNormal* p) { return p->soKineticEnergyNormal::getSpeed(); }

}
