#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/ft_util.h>
#include <ft/zako/ft_zako.h>
#include <ft/zako/ft_zako_extend_param_accesser.h>

// The four Zako fighters share their module configurations, so one set of builder instantiations covers all of them.
#define FT_BC ftZakoBoyBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftZakoBoyExtendParamAccesser g_ftZakoBoyExtendParamAccesser;
ftZakoGirlExtendParamAccesser g_ftZakoGirlExtendParamAccesser;
ftZakoChildExtendParamAccesser g_ftZakoChildExtendParamAccesser;
ftZakoBallExtendParamAccesser g_ftZakoBallExtendParamAccesser;

ftClassInfoImpl<Fighter_Zako_Boy, ftZakoBoy> g_ftClassInfoZakoBoy;
ftClassInfoImpl<Fighter_Zako_Girl, ftZakoGirl> g_ftClassInfoZakoGirl;
ftClassInfoImpl<Fighter_Zako_Child, ftZakoChild> g_ftClassInfoZakoChild;
ftClassInfoImpl<Fighter_Zako_Ball, ftZakoBall> g_ftClassInfoZakoBall;

#define FT_ZAKO_IMPL(NAME)                                                                  \
    ftZako##NAME::ftZako##NAME(s32 entryId,                                                 \
                               Heaps::HeapType instHeap,                                    \
                               Heaps::HeapType nwModelInstHeap,                             \
                               Heaps::HeapType nwMotionInstHeap) :                          \
        ftFighterBuilder<ftZako##NAME##BuildConfig>(entryId,                                \
                                                    Fighter_Zako_##NAME,                    \
                                                    instHeap,                               \
                                                    nwModelInstHeap,                        \
                                                    nwMotionInstHeap) {                     \
    }                                                                                       \
    bool ftZako##NAME::checkTransitionStatus(u32 status) {                                  \
        bool result = false;                                                                \
        if (Fighter::checkTransitionStatus(status)) {                                       \
            if (ftUtil::isValidStatusKindZako(m_moduleAccesser, status)) {                  \
                result = true;                                                              \
            }                                                                               \
        }                                                                                   \
        return result;                                                                      \
    }                                                                                       \
    bool ftZako##NAME::isHeartSwapEnableCondition() { return false; }                       \
    bool ftZako##NAME::setMetal(bool setStatus, float health, int unk3) { return false; }

FT_ZAKO_IMPL(Boy)
FT_ZAKO_IMPL(Girl)
FT_ZAKO_IMPL(Child)
FT_ZAKO_IMPL(Ball)

// Plays the common "other" animation layer and sets four work flags on activation.
// HYPOTHESIS: the flags are the invincibility/ground-state flags set by the common statuses; names unknown.
#define FT_ZAKO_ON_ACTIVATE(NAME)                                                           \
    void ftZako##NAME::onActivate() {                                                       \
        soModuleAccesser* acc = m_moduleAccesser;                                           \
        float one = 1.0f;                                                                   \
        acc->getMotionModule().addOtherAnim(0.0f, one, 1, 0x1CE, true);                     \
        acc->getMotionModule().setOtherAnimRate(one, 1);                                    \
        acc->getWorkManageModule().onFlag(0x12000021);                                     \
        acc->getWorkManageModule().onFlag(0x12000022);                                     \
        acc->getWorkManageModule().onFlag(0x12000023);                                     \
        acc->getWorkManageModule().onFlag(0x1200001D);                                     \
    }

FT_ZAKO_ON_ACTIVATE(Boy)
FT_ZAKO_ON_ACTIVATE(Girl)
FT_ZAKO_ON_ACTIVATE(Child)
FT_ZAKO_ON_ACTIVATE(Ball)

// MATCH-ONLY: the REL emits Fighter's empty onActivate (the vtable base entry); keep it alive.
#pragma dont_inline on
void ftZakoKeepFighterOnActivate(Fighter* fighter) { fighter->Fighter::onActivate(); }
#pragma dont_inline off

// FIXME: Test code present only to emit the shared builder functions
void testBuilder() {
    soInsideEventManageModuleBuilder<ftZakoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftZakoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
