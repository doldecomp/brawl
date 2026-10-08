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

// FIXME: the module setup performed by onActivate is not reconstructed yet
void ftZakoBoy::onActivate() { }
void ftZakoGirl::onActivate() { }
void ftZakoChild::onActivate() { }
void ftZakoBall::onActivate() { }

// FIXME: Test code present only to emit the shared builder functions
void testBuilder() {
    soInsideEventManageModuleBuilder<ftZakoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftZakoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;
