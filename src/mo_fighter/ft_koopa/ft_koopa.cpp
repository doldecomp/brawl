#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/koopa/ft_koopa.h>
#include <ft/koopa/ft_koopa_extend_param_accesser.h>

#define FT_BC ftKoopaBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftKoopaExtendParamAccesser g_ftKoopaExtendParamAccesser;

ftClassInfoImpl<Fighter_Koopa, ftKoopa> g_ftClassInfoKoopa;

ftKoopa::ftKoopa(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftKoopaBuildConfig>(entryId,
                                         Fighter_Koopa,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftKoopa is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftKoopaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftKoopaInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_102_61A8(u8* p) { return *(u8*)(p + 0x4); }
void fn_102_7F04() {}
void fn_102_8A2C() {}
int fn_102_8A30() { return 0; }
void fn_102_8C18() {}
void fn_102_8EAC() {}
void fn_102_8EB0() {}
void fn_102_8EB4() {}
void fn_102_8EB8() {}
int fn_102_8EBC() { return 0; }
void fn_102_8F00() {}
void fn_102_8F04() {}
void fn_102_8F08() {}
void fn_102_8F0C() {}
int fn_102_8F28() { return 0; }
void fn_102_8F30() {}
int fn_102_8F3C() { return 0; }
int fn_102_8F58() { return 32675; }
int fn_102_8F64() { return 0; }
u8* fn_102_902C(u8* p) { return p + 0x458; }
u8* fn_102_9034(u8* p) { return p + 0x3C8; }
u8* fn_102_903C(u8* p) { return p + 0x8; }
int fn_102_90DC(u8* p) { return *(int*)(p + 0x20); }
int fn_102_91B8(u8* p) { return *(int*)(p + 0x18); }
int fn_102_9250(u8* p) { return *(int*)(p + 0x10); }
int fn_102_A19C() { return 1; }
u8* fn_102_A1B0(u8* p) { return p + 0x13BD0; }
u8* fn_102_A1D0(u8* p) { return p + 0x13C0C; }
u8* fn_102_A1DC(u8* p) { return p + 0x140C4; }
void fn_102_AFE8() {}
void fn_102_B0D0(u8* p) { *(u8*)(p + 0x31) = 0; }
void fn_102_B0DC(u8* p) { *(u8*)(p + 0x31) = 1; }
int fn_102_B828() { return 0; }
int fn_102_B910() { return 0; }
int fn_102_B9F8() { return 0; }
int fn_102_BAE0() { return 0; }
int fn_102_BBC8() { return 0; }
int fn_102_BCB0() { return 0; }
int fn_102_BD98() { return 0; }
int fn_102_BE80() { return 0; }

}

// Placeholders for weak inline methods of library classes (their names exist in sora_melee, so the REL copies cannot be renamed): the shim calls the inline method.
extern "C" {

bool fn_102_9158(const soGeneralWorkSimple* p, u32 a0, u32 a1) { return p->soGeneralWorkSimple::isFlag(a0, a1); }
void fn_102_9174(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::offFlag(a0, a1); }
void fn_102_918C(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::clearFlag(a0); }
void fn_102_91A0(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::onFlag(a0, a1); }
void fn_102_91E8(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::mulFloatWork(a0, a1); }
void fn_102_9200(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::subFloatWork(a0, a1); }
void fn_102_9218(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::addFloatWork(a0, a1); }
void fn_102_9230(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::setFloatWork(a0, a1); }
float fn_102_9240(const soGeneralWorkSimple* p, u32 a0) { return p->soGeneralWorkSimple::getFloatWork(a0); }
void fn_102_9258(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::decIntWork(a0); }
void fn_102_9270(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::incIntWork(a0); }
void fn_102_9288(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::divIntWork(a0, a1); }
void fn_102_92A8(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::mulIntWork(a0, a1); }
void fn_102_92C0(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::subIntWork(a0, a1); }
void fn_102_92D8(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::addIntWork(a0, a1); }
void fn_102_92F0(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::setIntWork(a0, a1); }
Vec2f fn_102_B100(soKineticEnergyNormal* p) { return p->soKineticEnergyNormal::getSpeed(); }

}
