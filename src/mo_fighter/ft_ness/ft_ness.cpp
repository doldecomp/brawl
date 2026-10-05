#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ness/ft_ness.h>
#include <ft/ness/ft_ness_extend_param_accesser.h>

#define FT_NO_REFLECTOR_INSTANTIATION
#define FT_BC ftNessBuildConfig
#include <ft/builder/ft_builder_noinline.h>

#pragma dont_inline on
template soCollisionShieldModuleBuilder<ftNessCollisionReflectorBaseModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
template soCollisionShieldModuleBuilder<ftNessCollisionAbsorberModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
#pragma dont_inline off

ftNessExtendParamAccesser g_ftNessExtendParamAccesser;

ftClassInfoImpl<Fighter_Ness, ftNess> g_ftClassInfoNess;

ftNess::ftNess(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftNessBuildConfig>(entryId,
                                         Fighter_Ness,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftNess is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftNessInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftNessInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_101_92E8(u8* p) { return *(u8*)(p + 0x4); }
void fn_101_B58C() {}
int fn_101_CC78() { return 0; }
void fn_101_CE18() {}
void fn_101_D0C8() {}
void fn_101_D0CC() {}
void fn_101_D0D0() {}
void fn_101_D0D4() {}
int fn_101_D0D8() { return 0; }
void fn_101_D11C() {}
void fn_101_D120() {}
void fn_101_D124() {}
void fn_101_D128() {}
int fn_101_D144() { return 0; }
void fn_101_D14C() {}
int fn_101_D15C() { return 0; }
int fn_101_D164() { return 0; }
u8* fn_101_D240(u8* p) { return p + 0x458; }
u8* fn_101_D248(u8* p) { return p + 0x3C8; }
u8* fn_101_D250(u8* p) { return p + 0x8; }
int fn_101_D2E8(u8* p) { return *(int*)(p + 0x20); }
int fn_101_D3C4(u8* p) { return *(int*)(p + 0x18); }
int fn_101_D45C(u8* p) { return *(int*)(p + 0x10); }
int fn_101_EE70() { return 6; }
u8* fn_101_EE84(u8* p) { return p + 0x4A874; }
u8* fn_101_EEA4(u8* p) { return p + 0x4A8B0; }
u8* fn_101_EEB0(u8* p) { return p + 0x4AD68; }
void fn_101_FE20() {}
void fn_101_FF08(u8* p) { *(u8*)(p + 0x31) = 0; }
void fn_101_FF14(u8* p) { *(u8*)(p + 0x31) = 1; }
int fn_101_10660() { return 0; }
int fn_101_10748() { return 0; }
int fn_101_10830() { return 0; }
int fn_101_10918() { return 0; }
int fn_101_10A00() { return 0; }
int fn_101_10AE8() { return 0; }
int fn_101_10BD0() { return 0; }
int fn_101_10CB8() { return 0; }

}

// Placeholders for weak inline methods of library classes (their names exist in sora_melee, so the REL copies cannot be renamed): the shim calls the inline method.
extern "C" {

bool fn_101_D364(const soGeneralWorkSimple* p, u32 a0, u32 a1) { return p->soGeneralWorkSimple::isFlag(a0, a1); }
void fn_101_D380(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::offFlag(a0, a1); }
void fn_101_D398(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::clearFlag(a0); }
void fn_101_D3AC(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::onFlag(a0, a1); }
void fn_101_D3F4(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::mulFloatWork(a0, a1); }
void fn_101_D40C(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::subFloatWork(a0, a1); }
void fn_101_D424(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::addFloatWork(a0, a1); }
void fn_101_D43C(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::setFloatWork(a0, a1); }
float fn_101_D44C(const soGeneralWorkSimple* p, u32 a0) { return p->soGeneralWorkSimple::getFloatWork(a0); }
void fn_101_D464(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::decIntWork(a0); }
void fn_101_D47C(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::incIntWork(a0); }
void fn_101_D494(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::divIntWork(a0, a1); }
void fn_101_D4B4(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::mulIntWork(a0, a1); }
void fn_101_D4CC(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::subIntWork(a0, a1); }
void fn_101_D4E4(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::addIntWork(a0, a1); }
void fn_101_D4FC(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::setIntWork(a0, a1); }
Vec2f fn_101_FF38(soKineticEnergyNormal* p) { return p->soKineticEnergyNormal::getSpeed(); }

}
