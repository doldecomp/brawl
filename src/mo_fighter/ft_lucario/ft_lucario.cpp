#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/lucario/ft_lucario.h>
#include <ft/lucario/ft_lucario_extend_param_accesser.h>

#define FT_BC ftLucarioBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftLucarioExtendParamAccesser g_ftLucarioExtendParamAccesser;

ftClassInfoImpl<Fighter_Lucario, ftLucario> g_ftClassInfoLucario;

ftLucario::ftLucario(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftLucarioBuildConfig>(entryId,
                                         Fighter_Lucario,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftLucario is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftLucarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftLucarioInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_118_6D04(u8* p) { return *(u8*)(p + 0x4); }
void fn_118_8A80() {}
void fn_118_8B38() {}
int fn_118_9C50() { return 0; }
void fn_118_9E70() {}
void fn_118_A120() {}
void fn_118_A124() {}
void fn_118_A128() {}
void fn_118_A12C() {}
int fn_118_A130() { return 0; }
void fn_118_A174() {}
void fn_118_A178() {}
void fn_118_A17C() {}
void fn_118_A180() {}
int fn_118_A19C() { return 0; }
void fn_118_A1A4() {}
int fn_118_A1B4() { return 0; }
int fn_118_A1BC() { return 0; }
u8* fn_118_A294(u8* p) { return p + 0x458; }
u8* fn_118_A29C(u8* p) { return p + 0x3C8; }
u8* fn_118_A2A4(u8* p) { return p + 0x8; }
int fn_118_A344(u8* p) { return *(int*)(p + 0x20); }
int fn_118_A420(u8* p) { return *(int*)(p + 0x18); }
int fn_118_A4B8(u8* p) { return *(int*)(p + 0x10); }
int fn_118_B584() { return 2; }
void fn_118_B58C(u8* p, u8 v) { *(u8*)(p + 0x7F60) = v; }
u8* fn_118_B594(u8* p) { return p + 0xFF98; }
u8* fn_118_B5B4(u8* p) { return p + 0xFFD4; }
u8* fn_118_B5C0(u8* p) { return p + 0x1048C; }
void fn_118_C3B0() {}
void fn_118_C498(u8* p) { *(u8*)(p + 0x31) = 0; }
void fn_118_C4A4(u8* p) { *(u8*)(p + 0x31) = 1; }
int fn_118_CBEC() { return 0; }
int fn_118_CCD4() { return 0; }
int fn_118_CDBC() { return 0; }
int fn_118_CEA4() { return 0; }
int fn_118_CF8C() { return 0; }
int fn_118_D074() { return 0; }
int fn_118_D15C() { return 0; }
int fn_118_D244() { return 0; }

}

// Placeholders for weak inline methods of library classes (their names exist in sora_melee, so the REL copies cannot be renamed): the shim calls the inline method.
extern "C" {

bool fn_118_A3C0(const soGeneralWorkSimple* p, u32 a0, u32 a1) { return p->soGeneralWorkSimple::isFlag(a0, a1); }
void fn_118_A3DC(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::offFlag(a0, a1); }
void fn_118_A3F4(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::clearFlag(a0); }
void fn_118_A408(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::onFlag(a0, a1); }
void fn_118_A450(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::mulFloatWork(a0, a1); }
void fn_118_A468(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::subFloatWork(a0, a1); }
void fn_118_A480(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::addFloatWork(a0, a1); }
void fn_118_A498(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::setFloatWork(a0, a1); }
float fn_118_A4A8(const soGeneralWorkSimple* p, u32 a0) { return p->soGeneralWorkSimple::getFloatWork(a0); }
void fn_118_A4C0(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::decIntWork(a0); }
void fn_118_A4D8(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::incIntWork(a0); }
void fn_118_A4F0(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::divIntWork(a0, a1); }
void fn_118_A510(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::mulIntWork(a0, a1); }
void fn_118_A528(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::subIntWork(a0, a1); }
void fn_118_A540(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::addIntWork(a0, a1); }
void fn_118_A558(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::setIntWork(a0, a1); }
Vec2f fn_118_C4C4(soKineticEnergyNormal* p) { return p->soKineticEnergyNormal::getSpeed(); }

}
