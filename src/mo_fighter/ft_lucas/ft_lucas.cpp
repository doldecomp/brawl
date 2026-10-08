#define FT_ROBOT_SHARED_STATUS_TABLE_CTOR // MATCH-ONLY: call the shared table constructor used by this REL.
#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/lucas/ft_lucas.h>
#include <ft/lucas/ft_lucas_extend_param_accesser.h>
#include <ft/lucas/ft_lucas_status_uniq_process.h>

#define FT_NO_REFLECTOR_INSTANTIATION
#define FT_BC ftLucasBuildConfig
#include <ft/builder/ft_builder_noinline.h>

#pragma dont_inline on
template soCollisionShieldModuleBuilder<ftLucasCollisionReflectorBaseModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
template soCollisionShieldModuleBuilder<ftLucasCollisionAbsorberModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
#pragma dont_inline off

ftLucasExtendParamAccesser g_ftLucasExtendParamAccesser;

ftClassInfoImpl<Fighter_Lucas, ftLucas> g_ftClassInfoLucas;

ftLucas::ftLucas(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftLucasBuildConfig>(entryId,
                                         Fighter_Lucas,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap),
    m_commonData(g_ftCommonDataAccesser.getData(Fighter_Lucas)) {
    unk48CC4[0] = 0;
    unk48CC4[1] = 0;

    // Lucas owns 16 character action slots. A null entry differs from the
    // shared no-op process used by the other four otherwise unused slots.
    soStatusUniqProcess* processes[16] = {0};
    processes[0] = &g_soStatusUniqProcessNull;
    processes[1] = &g_ftLucasStatusUniqProcessSpecialS;
    processes[3] = &g_ftLucasStatusUniqProcessSpecialLw;
    processes[5] = &g_soStatusUniqProcessNull;
    processes[6] = &g_soStatusUniqProcessNull;
    processes[7] = &g_soStatusUniqProcessNull;
    processes[8] = &g_ftLucasStatusUniqProcessSpecialHi;
    processes[9] = &g_ftLucasStatusUniqProcessSpecialHiAttackEnd;
    processes[10] = &g_ftLucasStatusUniqProcessSpecialHiAttack;
    processes[11] = &g_ftLucasStatusUniqProcessSpecialHiReflect;
    processes[12] = &g_ftLucasStatusUniqProcessSpecialHiAttackEnd;
    processes[13] = &g_ftLucasStatusUniqProcessSpecialLwHold;
    processes[14] = &g_ftLucasStatusUniqProcessSpecialLwHold;
    m_moduleAccesser->getStatusModule().addRangeUniqProc(processes, 16);

    // Generic aerial transitions and Lucas's forward smash/rope-snake
    // actions override entries outside the consecutive character range.
    m_moduleAccesser->getStatusModule().setUniqProc(0x33, &g_ftStatusUniqProcessAttackAirInheritJumpAerialMotion);
    m_moduleAccesser->getStatusModule().setUniqProc(0x21, &g_ftStatusUniqProcessEscapeAirInheritJumpAerialMotion);
    m_moduleAccesser->getStatusModule().setUniqProc(0x2C, &g_ftLucasStatusUniqProcessAttackS4);
    m_moduleAccesser->getStatusModule().setUniqProc(0x7F, &g_ftLucasStatusUniqProcessAirLasso);
}

void** ftLucas::getExtendParam() {
    return m_commonData->extendParam;
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftLucas is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftLucasInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftLucasInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_114_8BC0(u8* p) { return *(u8*)(p + 0x4); }
void fn_114_ADE8() {}
int fn_114_C6AC(u8* p) { return *(int*)(p + 0x28); }
int fn_114_C6B4() { return 0; }
void fn_114_C854() {}
void fn_114_CB04() {}
void fn_114_CB08() {}
void fn_114_CB0C() {}
void fn_114_CB10() {}
int fn_114_CB14() { return 0; }
void fn_114_CB58() {}
void fn_114_CB5C() {}
void fn_114_CB60() {}
void fn_114_CB64() {}
int fn_114_CB80() { return 0; }
void fn_114_CB88() {}
int fn_114_CB98() { return 0; }
int fn_114_CBA0() { return 0; }
u8* fn_114_CC7C(u8* p) { return p + 0x458; }
u8* fn_114_CC84(u8* p) { return p + 0x3C8; }
u8* fn_114_CC8C(u8* p) { return p + 0x8; }
int fn_114_CD24(u8* p) { return *(int*)(p + 0x20); }
int fn_114_CE00(u8* p) { return *(int*)(p + 0x18); }
int fn_114_CE98(u8* p) { return *(int*)(p + 0x10); }
int fn_114_E6E8() { return 5; }
u8* fn_114_E6FC(u8* p) { return p + 0x48714; }
u8* fn_114_E71C(u8* p) { return p + 0x48750; }
u8* fn_114_E728(u8* p) { return p + 0x48C08; }
void fn_114_F680() {}
void fn_114_F768(u8* p) { *(u8*)(p + 0x31) = 0; }
void fn_114_F774(u8* p) { *(u8*)(p + 0x31) = 1; }
int fn_114_FEC0() { return 0; }
int fn_114_FFA8() { return 0; }
int fn_114_10090() { return 0; }
int fn_114_10178() { return 0; }
int fn_114_10260() { return 0; }
int fn_114_10348() { return 0; }
int fn_114_10430() { return 0; }
int fn_114_10518() { return 0; }

}

// Placeholders for weak inline methods of library classes (their names exist in sora_melee, so the REL copies cannot be renamed): the shim calls the inline method.
extern "C" {

bool fn_114_CDA0(const soGeneralWorkSimple* p, u32 a0, u32 a1) { return p->soGeneralWorkSimple::isFlag(a0, a1); }
void fn_114_CDBC(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::offFlag(a0, a1); }
void fn_114_CDD4(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::clearFlag(a0); }
void fn_114_CDE8(soGeneralWorkSimple* p, u32 a0, u32 a1) { p->soGeneralWorkSimple::onFlag(a0, a1); }
void fn_114_CE30(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::mulFloatWork(a0, a1); }
void fn_114_CE48(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::subFloatWork(a0, a1); }
void fn_114_CE60(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::addFloatWork(a0, a1); }
void fn_114_CE78(soGeneralWorkSimple* p, float a0, u32 a1) { p->soGeneralWorkSimple::setFloatWork(a0, a1); }
float fn_114_CE88(const soGeneralWorkSimple* p, u32 a0) { return p->soGeneralWorkSimple::getFloatWork(a0); }
void fn_114_CEA0(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::decIntWork(a0); }
void fn_114_CEB8(soGeneralWorkSimple* p, u32 a0) { p->soGeneralWorkSimple::incIntWork(a0); }
void fn_114_CED0(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::divIntWork(a0, a1); }
void fn_114_CEF0(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::mulIntWork(a0, a1); }
void fn_114_CF08(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::subIntWork(a0, a1); }
void fn_114_CF20(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::addIntWork(a0, a1); }
void fn_114_CF38(soGeneralWorkSimple* p, s32 a0, u32 a1) { p->soGeneralWorkSimple::setIntWork(a0, a1); }
Vec2f fn_114_F798(soKineticEnergyNormal* p) { return p->soKineticEnergyNormal::getSpeed(); }

}
