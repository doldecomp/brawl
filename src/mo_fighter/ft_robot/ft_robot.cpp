#define SO_SLOW_GET_INSTANCE_OUT_OF_LINE
// The constructor calls the status table's default constructor in sora_melee instead of inlining it.
#define FT_ROBOT_SHARED_STATUS_TABLE_CTOR
#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/robot/ft_robot.h>
#include <ft/robot/ft_robot_extend_param_accesser.h>
#include <ft/robot/ft_robot_link_event.h>
#include <ft/robot/ft_robot_unk8.h>
#include <ft/robot/ft_robot_status_uniq_process_special_arm_spin.h>
#include <ft/robot/ft_robot_status_uniq_process_final.h>
#include <ft/robot/ft_robot_status_uniq_process_special_beam.h>
#include <ft/robot/ft_robot_status_uniq_process_special_burner.h>
#include <ft/robot/ft_robot_status_uniq_process_special_burner_attack.h>
#include <ft/robot/ft_robot_status_uniq_process_special_burner_start.h>
#include <ft/robot/ft_robot_status_uniq_process_special_gyro.h>
#include <ft/robot/ft_robot_transactor.h>
#include <ac/ac_anim_cmd_impl.h>
#include <it/it_manager.h>
#include <so/link/so_link_event_presenter.h>
#include <so/so_slow.h>
#include <so/so_value_accesser.h>

#define FT_BC ftRobotBuildConfig
#include <ft/builder/ft_builder_noinline.h>

// The fighter and Gyro status translation units each construct their own pair of article tags.
// HYPOTHESIS: their values select the two shared item/article template instances.
static ftRobotUnk8 s_unkTag0(0xff, 0);
static ftRobotUnk8 s_unkTag1(0xff, 1);

ftRobotExtendParamAccesser g_ftRobotExtendParamAccesser;
ftClassInfoImpl<Fighter_Robot, ftRobot> g_ftClassInfoRobot;

// The physics module's second interface is not declared yet: the constructor calls slot 0x54 of the vtable at +8
// with the module pointer itself and a zero argument (HYPOTHESIS: resets the physics state).
static void ftRobotPhysicsModuleCall54(void* module, int arg) {
    typedef void (*Fn)(void*, int);
    void** table = *reinterpret_cast<void***>(reinterpret_cast<u8*>(module) + 8);
    reinterpret_cast<Fn>(table[0x54 / sizeof(void*)])(module, arg);
}

ftRobot::ftRobot(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftRobotBuildConfig>(entryId,
                                        Fighter_Robot,
                                        instHeap,
                                        nwModelInstHeap,
                                        nwMotionInstHeap) {
    m_commonData = g_ftCommonDataAccesser.getData(Fighter_Robot);
    // Register the character-specific status processes in action order (index 6 is unused).
    soStatusUniqProcess* processes[12] = {0};
    processes[0] = &g_ftRobotStatusUniqProcessSpecialBeam;
    processes[1] = &g_ftRobotStatusUniqProcessSpecialArmSpin;
    processes[2] = &g_ftRobotStatusUniqProcessSpecialBurnerStart;
    processes[3] = &g_ftRobotStatusUniqProcessSpecialGyro;
    processes[4] = &g_ftRobotStatusUniqProcessFinal;
    processes[5] = &g_ftRobotStatusUniqProcessSpecialArmSpin;
    processes[7] = &g_ftRobotStatusUniqProcessSpecialBurner;
    processes[8] = &g_ftRobotStatusUniqProcessSpecialBurnerAttack;
    processes[9] = &g_ftRobotStatusUniqProcessSpecialGyro;
    processes[10] = &g_ftRobotStatusUniqProcessSpecialGyro;
    processes[11] = &g_ftRobotStatusUniqProcessSpecialGyro;
    m_moduleAccesser->getStatusModule().addRangeUniqProc(processes, 12);

    // HYPOTHESIS: the common data record points at the reflector shape groups (+0xb0); group index 2 is the one added.
    soCollisionReflectorGroupData* reflectors = *reinterpret_cast<soCollisionReflectorGroupData**>(reinterpret_cast<u8*>(m_commonData) + 0xb0);
    m_moduleAccesser->getCollisionReflectorModule().add(reflectors, 2);
    m_moduleAccesser->getCollisionReflectorModule().setStatus(0, 0, 2);
    ftRobotPhysicsModuleCall54(m_moduleAccesser->m_enumerationStart->m_physicsModule, 0);
    soSlopeModule* slope = static_cast<soSlopeModule*>(m_moduleAccesser->m_enumerationStart->m_slopeModule);
    slope->setPartNode(0x5D);
    slope->setInvalidStatus(6);
}

// Emit the event builder and shared resource accesser used by this REL, following
// the existing fighter translation units until their users are reconstructed.
void testBuilder() {
    soInsideEventManageModuleBuilder<ftRobotInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftRobotInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// The original article ownership chain calls these destructors out of line.
#pragma dont_inline on
template <class W>
ftRobotArticleHolder<W>::~ftRobotArticleHolder() { }
template <class W, int N>
ftRobotArticleSubPool<W, N>::~ftRobotArticleSubPool() { }
template <class W, int N, class Base>
inline ftRobotArticlePool<W, N, Base>::~ftRobotArticlePool() { }
template <class W, int N, class Base>
ftRobotArticleHierarchy<W, N, Base>::~ftRobotArticleHierarchy() { }
template ftRobotArticleHolder<wnRobotFinalBeam>::~ftRobotArticleHolder();
template ftRobotArticleSubPool<wnRobotFinalBeam, 1>::~ftRobotArticleSubPool();
template ftRobotArticleHolder<wnRobotGyroHolder>::~ftRobotArticleHolder();
template ftRobotArticleSubPool<wnRobotGyroHolder, 1>::~ftRobotArticleSubPool();
template ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool>::~ftRobotArticlePool();
template ftRobotArticleHolder<wnRobotBeam>::~ftRobotArticleHolder();
template ftRobotArticleSubPool<wnRobotBeam, 1>::~ftRobotArticleSubPool();
template ftRobotArticleSubPool<wnRobotBeam, 2>::~ftRobotArticleSubPool();
template ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool>::~ftRobotArticlePool();
template ftRobotArticleHolder<wnRobotGyro>::~ftRobotArticleHolder();
template ftRobotArticleSubPool<wnRobotGyro, 1>::~ftRobotArticleSubPool();
template ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool>::~ftRobotArticlePool();
template ftRobotArticleHierarchy<wnRobotGyro, 1, ftRobotBeamPool>::~ftRobotArticleHierarchy();
template ftRobotArticleHierarchy<wnRobotFinalBeam, 1, soInstancePoolRoot>::~ftRobotArticleHierarchy();
ftRobotArticleMediator::~ftRobotArticleMediator() { }
ftRobotSelectedArticleMediator::~ftRobotSelectedArticleMediator() { }
ftRobotArticleManageModuleBuilder::~ftRobotArticleManageModuleBuilder() { }
#pragma dont_inline off

soArticleMediator::~soArticleMediator() { }

template <class W>
ftRobotArticleHolder<W>::ftRobotArticleHolder(soModuleAccesser* acc) : soInstancePoolRoot(acc),
        m_instance(ftRobotArticleTraits<W>::ArticleId,
                   ftRobotArticleConstructionInfo(ftRobotArticleKindInfo(),
                       acc->m_enumerationStart->m_heapModule),
                   ftRobotArticleTraits<W>::getData()) { }

static void* ftRobotGetBeamData() {
    bool resourceGroup = false;
    const ftRobotArticleDataAccesser* accesser =
        reinterpret_cast<const ftRobotArticleDataAccesser*>(&g_ftCommonDataAccesser);
    return accesser->getBeamData(Fighter_Robot, &resourceGroup);
}

// Two Beam instances use this same holder constructor in the original builder.
template <>
ftRobotArticleHolder<wnRobotBeam>::ftRobotArticleHolder(soModuleAccesser* acc) :
    soInstancePoolRoot(acc),
    m_instance(1, ftRobotArticleConstructionInfo(ftRobotArticleKindInfo(),
                    acc->m_enumerationStart->m_heapModule), ftRobotGetBeamData()) { }

ftRobotArticleManageModuleBuilder::ftRobotArticleManageModuleBuilder(soModuleAccesser* acc) :
    m_articles(0), m_observers(4, 0), m_mediator(acc),
    m_module(acc, &m_articles, &m_mediator, &m_observers) { }

// Emit the indexed accessors used by article deactivation.
#pragma dont_inline on
template wnRobotGyro* ftRobotArticleSubPool<wnRobotGyro, 1>::getInstanceAt(s32);
template wnRobotBeam* ftRobotArticleSubPool<wnRobotBeam, 2>::getInstanceAt(s32);
template wnRobotGyroHolder* ftRobotArticleSubPool<wnRobotGyroHolder, 1>::getInstanceAt(s32);
template wnRobotFinalBeam* ftRobotArticleSubPool<wnRobotFinalBeam, 1>::getInstanceAt(s32);

#pragma dont_inline off

ftRobotUnk8::ftRobotUnk8(int a, int b) : unk0(a), unk4(b) { }

s32 ftRobotArticleMediator::getMediateNum() { return 4; }
void ftRobotArticleMediator::setAutoRecycle(bool enabled) { m_autoRecycle = enabled; }

#pragma dont_inline on
void ftRobotArticleMediator::deactivate() {
    for (s32 i = 0; i < 1; ++i) {
        wnRobotGyro* weapon = static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub().getInstanceAt(i);
        if (!ftRobotDeactivateArticle(static_cast<soArticle*>(weapon))) {
            return;
        }
    }
    for (s32 i = 0; i < 2; ++i) {
        wnRobotBeam* weapon = static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub().getInstanceAt(i);
        if (!ftRobotDeactivateArticle(static_cast<soArticle*>(weapon))) {
            return;
        }
    }
    for (s32 i = 0; i < 1; ++i) {
        wnRobotGyroHolder* weapon = static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub().getInstanceAt(i);
        if (!ftRobotDeactivateArticle(static_cast<soArticle*>(weapon))) {
            return;
        }
    }
    for (s32 i = 0; i < 1; ++i) {
        wnRobotFinalBeam* weapon = static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub().getInstanceAt(i);
        if (!ftRobotDeactivateArticle(static_cast<soArticle*>(weapon))) {
            return;
        }
    }
}
#pragma dont_inline off

// The mediator walks a list of 17 article slots (only the first four are used by R.O.B.; the original code has one
// switch case per slot). Every case builds a two-byte empty tag on the stack, which is why each case owns its own slot
// of the frame (HYPOTHESIS: the tag is the per-slot type-list marker of the generic mediator template).
struct ftRobotArticleSlotTag {
    u8 m_pad0;
    u8 m_pad1;
    ftRobotArticleSlotTag() : m_pad0(0), m_pad1(0) { }
    ~ftRobotArticleSlotTag() { } // MATCH-ONLY: a non-trivial destructor keeps the otherwise dead tag stores
};

#define FT_ROBOT_UNUSED_SLOT(n, value) \
    case n: { \
        ftRobotArticleSlotTag tag; \
        return value; \
    }
#define FT_ROBOT_UNUSED_SLOTS(value) \
    FT_ROBOT_UNUSED_SLOT(4, value) FT_ROBOT_UNUSED_SLOT(5, value) FT_ROBOT_UNUSED_SLOT(6, value) \
    FT_ROBOT_UNUSED_SLOT(7, value) FT_ROBOT_UNUSED_SLOT(8, value) FT_ROBOT_UNUSED_SLOT(9, value) \
    FT_ROBOT_UNUSED_SLOT(10, value) FT_ROBOT_UNUSED_SLOT(11, value) FT_ROBOT_UNUSED_SLOT(12, value) \
    FT_ROBOT_UNUSED_SLOT(13, value) FT_ROBOT_UNUSED_SLOT(14, value) FT_ROBOT_UNUSED_SLOT(15, value) \
    FT_ROBOT_UNUSED_SLOT(16, value)

s32 ftRobotArticleMediator::getGenerateMaxNum(s32 articleId) {
    switch (articleId) {
    case 0: { ftRobotArticleSlotTag tag; return 1; }
    case 1: { ftRobotArticleSlotTag tag; return 2; }
    case 2: { ftRobotArticleSlotTag tag; return 1; }
    case 3: { ftRobotArticleSlotTag tag; return 1; }
    FT_ROBOT_UNUSED_SLOTS(0)
    default: return 0;
    }
}

// The original counts with a small functor on the stack: the first word is the address of a thunk that calls the
// article's isActiveArticle virtual on the article subobject (a weak function at 0xAFB0), followed by the number of
// active and of inactive articles seen so far.
static bool ftRobotIsActiveArticle(soArticle* article) { return article->isActiveArticle(); }

struct ftRobotArticleActiveCounter {
    bool (*m_isActive)(soArticle*);
    s32 m_activeNum;
    s32 m_inactiveNum;
    ftRobotArticleActiveCounter() : m_isActive(ftRobotIsActiveArticle), m_activeNum(0), m_inactiveNum(0) { }
};

template <class W, int N>
static s32 ftRobotCountActiveArticles(ftRobotArticleSubPool<W, N>& pool) {
    ftRobotArticleActiveCounter counter;
    for (s32 i = 0; i < N; ++i) {
        if (counter.m_isActive(pool.getInstanceAt(i)) == true) {
            ++counter.m_activeNum;
        } else {
            ++counter.m_inactiveNum;
        }
    }
    return counter.m_activeNum;
}

s32 ftRobotArticleMediator::getActiveNum(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0: {
        ftRobotArticleSlotTag tag;
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub());
    }
    case 1: {
        ftRobotArticleSlotTag tag;
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub());
    }
    case 2: {
        ftRobotArticleSlotTag tag;
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub());
    }
    case 3: {
        ftRobotArticleSlotTag tag;
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub());
    }
    FT_ROBOT_UNUSED_SLOTS(0)
    default: return 0;
    }
}

template <class W, int N>
static bool ftRobotCanGenerateArticle(ftRobotArticleSubPool<W, N>& pool) {
    for (s32 i = 0; i < N; ++i) {
        if (pool.getInstanceAt(i)->isActiveArticle() == false) {
            return true;
        }
    }
    return false;
}

bool ftRobotArticleMediator::isGeneratable(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0: {
        ftRobotArticleSlotTag tag;
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub());
    }
    case 1: {
        ftRobotArticleSlotTag tag;
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub());
    }
    case 2: {
        ftRobotArticleSlotTag tag;
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub());
    }
    case 3: {
        ftRobotArticleSlotTag tag;
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub());
    }
    FT_ROBOT_UNUSED_SLOTS(false)
    default: return false;
    }
}

void ftRobot::onActivate() {
    m_moduleAccesser->getWorkManageModule().setInt(0, 0x10000044);
}

void ftRobot::notifyEventOnDamage(soDamage* damage, bool flag, soModuleAccesser* acc) {
    Fighter::notifyEventOnDamage(damage, flag, acc);
}

// Work variables (HYPOTHESIS names, from how the statuses and this class use them):
//   float 0x11000015  Robo Burner fuel (refills on the ground)
//   int   0x10000042  frames left of the Final Smash   int 0x10000043  frames until the next beam volley
//   int   0x10000044  generation counter handed to the beam articles
//   flag  0x12000040  the arm spin partial animation has to be restarted when landing
//   flag  0x12000041  that partial animation is running
//   flag  0x12000042  the Final Smash is active   0x12000043  its beams are firing   0x12000045  volley pending
//   flag  0x12000046  the Final Smash music/camera cue was started   0x12000047  Robo Beam charge does not recover

static soGenerateArticleManageModule& ftRobotGetArticleModule(soModuleAccesser* acc) {
    return *static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule);
}

void ftRobot::onDeactivate() {
    int taskId = m_moduleAccesser->getStageObject().m_taskId;
    itManager::getInstance()->removeItem1(taskId);
}

void ftRobot::onStart(int param) {
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000040);
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000041);
    m_moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(m_moduleAccesser, 0xfbf, 0), 0x11000015);
    m_moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000014);
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000042);
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000043);
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000045);
    m_moduleAccesser->getWorkManageModule().setInt(0, 0x10000042);
    m_moduleAccesser->getWorkManageModule().setInt(0, 0x10000043);
    ftRobotGetArticleModule(m_moduleAccesser).removeExist(3, 0);
    m_moduleAccesser->getWorkManageModule().offFlag(0x12000046);
    Fighter::onStart(param);
    m_moduleAccesser->getMotionModule().removePartialAnimChr(2);
    ftRobotTransactor::getInstance()->initTransact(m_moduleAccesser);
    m_moduleAccesser->getEffectModule().removeCommon(0x1a);
    m_moduleAccesser->getEffectModule().removeCommon(0x26);
    m_moduleAccesser->getEffectModule().removeCommon(0x25);
    if ((u32)(param - 4) < 2) {
        m_moduleAccesser->getWorkManageModule().onFlag(0x12000047);
    } else {
        m_moduleAccesser->getWorkManageModule().offFlag(0x12000047);
    }
}

void ftRobot::processUpdate() {
    soModuleAccesser* acc = m_moduleAccesser;
    if (soSlow::getInstance()->isEstimate() == 1 && acc->getStopModule().isStop() == 0 && acc->getSlowModule().isSkip() == 0) {
        if (!acc->getWorkManageModule().isFlag(0x12000042)) {
            ftRobotTransactor::getInstance()->processUpdateSpecialNTransact(acc);
        }
        updateSpecialHi(acc);
    }
    Fighter::processUpdate();
}

// The Robo Burner fuel refills while standing on the ground.
void ftRobot::updateSpecialHi(soModuleAccesser* acc) {
    if (acc->getSituationModule().getKind() == 0) {
        if (acc->getWorkManageModule().getFloat(0x11000015) < soValueAccesser::getConstantFloat(acc, 0xfbf, 0)) {
            acc->getWorkManageModule().addFloat(soValueAccesser::getConstantFloat(acc, 0xfcc, 0), 0x11000015);
        }
    }
}

void ftRobot::notifyEventCollisionAttackFighter(soCollisionLog* collisionLog, soModuleAccesser* acc) {
    if (acc->getStatusModule().getStatusKind() == 0x113) {
        g_ftRobotStatusUniqProcessSpecialArmSpin.setEventCollisionAttack(acc);
    }
}

void ftRobot::notifyEventLink(soLinkEventArgs* eventInfo, soModuleAccesser* acc, StageObject* object, int unk4) {
    switch (eventInfo->m_eventKind) {
    case 0x456:
        if (acc->getWorkManageModule().isFlag(0x12000042)) {
            acc->getControllerModule().setRumble(0xe, 0, false, 8);
        }
        break;
    }
    Fighter::notifyEventLink(eventInfo, acc, object, unk4);
}

// HYPOTHESIS: layout of the seal record: a kind and a float amount.
struct ftRobotSealInfo {
    s32 kind;
    float amount;
};

void ftRobot::analyzeSeal(void* sealInfo) {
    ftRobotSealInfo* info = static_cast<ftRobotSealInfo*>(sealInfo);
    if (info->kind == 0x3f) {
        s32 generation = (s32)(info->amount * 0.5f);
        m_moduleAccesser->getWorkManageModule().setInt(generation, 0x10000044);
    }
}

void ftRobot::processFixPosition() {
    soModuleAccesser* acc = m_moduleAccesser;
    if (soSlow::getInstance()->isAdjust() == 1 && acc->getStopModule().isStop() == 0) {
        if (acc->getSlowModule().isSkip() == 0) {
            if (acc->getWorkManageModule().isFlag(0x12000042)) {
                updateFinal(acc);
            }
            ftRobotTransactor::getInstance()->processUpdateEffectTransact(acc);
        }
        if (m_moduleAccesser->getWorkManageModule().isFlag(0x12000041) && m_moduleAccesser->getMotionModule().isEndPartial(2)) {
            m_moduleAccesser->getMotionModule().removePartialAnimChr(2);
            m_moduleAccesser->getWorkManageModule().offFlag(0x12000041);
        }
    }
    Fighter::processFixPosition();
}

// HYPOTHESIS: the statuses that cut the Final Smash beam short (hit reactions, knockdowns, grabs, ...).
static bool ftRobotIsFinalInterruptStatus(int status) {
    switch (status) {
    case 0x3d:
    case 0x3e:
    case 0x3f:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0xbd:
    case 0xcc:
    case 0xcd:
    case 0xce:
    case 0xcf:
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd7:
    case 0xd8:
    case 0xd9:
    case 0xda:
    case 0xdb:
    case 0xe6:
    case 0xe7:
    case 0xe8:
    case 0xe9:
    case 0xea:
    case 0xeb:
    case 0xec:
    case 0xed:
    case 0xee:
    case 0xef:
    case 0xf0:
        return true;
    default:
        return false;
    }
}

void ftRobot::notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* acc) {
    if (acc->getWorkManageModule().isFlag(0x12000042)) {
        soGenerateArticleManageModule& articles = ftRobotGetArticleModule(acc);
        acc->getCollisionHitModule().setWhole(2, 0);
        if (ftRobotIsFinalInterruptStatus(statusKind)) {
            articles.removeExist(3, 0);
            acc->getControllerModule().stopRumbleKind(2, 8);
        } else if (articles.isGeneratable(3)) {
            soArticle* beam = articles.generate(3, NULL, NULL);
            if (!beam->isNull()) {
                articles.entry(beam);
            }
        }
    }
    Fighter::notifyEventChangeStatus(statusKind, prevStatusKind, statusData, acc);
}

// While the gyro is out the arms keep the "holding" animation; landing starts the partial animation of the second hand.
void ftRobot::notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* acc) {
    switch (acc->getStatusModule().getStatusKind()) {
    case 0x115:
    case 0x11b:
    case 0x11c:
    case 0x11d:
        if (kind == 2) {
            ftRobotGyroLinkEvent event(0x83d);
            acc->getLinkModule().sendEventNodes(-1, event, 0);
        } else {
            ftRobotGyroLinkEvent event(0x83c);
            acc->getLinkModule().sendEventNodes(-1, event, 0);
        }
        break;
    }
    if (acc->getWorkManageModule().isFlag(0x12000040) && kind == 0) {
        m_moduleAccesser->getMotionModule().removePartialAnimChr(2);
        acc->getMotionModule().addPartialAnimChr(0.0f, 1.0f, 2, 0x1d9, 0x60, 0, 0);
        acc->getWorkManageModule().offFlag(0x12000040);
        acc->getWorkManageModule().onFlag(0x12000041);
    }
    Fighter::notifyEventChangeSituation(kind, prevKind, acc);
}

bool ftRobot::notifyEventAnimCmd(acAnimCmd* cmd, soModuleAccesser* acc, int index) {
    bool result;
    char group = cmd->getGroup();
    if (!isObserv(group)) {
        result = false;
    } else {
        switch (cmd->getType()) {
        case ')':
            acc->getVisibilityModule().set(0, 1);
            result = true;
            break;
        default:
            result = Fighter::notifyEventAnimCmd(cmd, acc, index);
            break;
        }
    }
    return result;
}

// The SDK keeps soArticle::getArticleId private. This view describes its observed
// PPC virtual slot rather than assuming every article is a Weapon (the null
// article is a valid input too). Replace it when the SDK interface is complete.
static s32 ftRobotGetArticleId(soArticle* article) {
    typedef s32 (*GetArticleId)(soArticle*);
    void** table = *reinterpret_cast<void***>(article);
    GetArticleId getter = reinterpret_cast<GetArticleId>(table[0x20 / sizeof(void*)]);
    return getter(article);
}

static soArticle* ftRobotGetNullArticle() {
    return reinterpret_cast<soArticle*>(g_ftRobotNullArticleStorage);
}

bool ftRobotArticleActivator<wnRobotBeam>::activate(wnRobotBeam* weapon, soModuleAccesser* acc) {
    u32 resourceId = acc->getResourceModule().getResourceIdAccesser()->getEtcResId();
    return ftRobotTransactor::getInstance()->activeArticle1(weapon, acc, resourceId);
}

template <class W, int N>
static soArticle* ftRobotGenerateFromPool(ftRobotArticleSubPool<W, N>& pool, soModuleAccesser* acc) {
    soArticleDeactivateChecker checker;
    W* weapon = NULL;
    // The original checks the newest pool slot first (Beam index 1 before 0).
    for (s32 i = N - 1; i >= 0; --i) {
        W* candidate = pool.getInstanceAt(i);
        if (checker(static_cast<soArticle*>(candidate)) == true) {
            weapon = candidate;
            break;
        }
    }
    if (weapon == NULL) {
        weapon = static_cast<W*>(checker.getCandidate());
        if (weapon == NULL) {
            return ftRobotGetNullArticle();
        }
        weapon->deactivateArticle();
    }
    if (ftRobotArticleActivator<W>::activate(weapon, acc) == true) {
        return static_cast<soArticle*>(weapon);
    }
    return ftRobotGetNullArticle();
}

soArticle* ftRobotArticleMediator::generate(s32 articleId, soModuleAccesser* acc) {
    switch (articleId) {
    case 0: {
        ftRobotArticleSlotTag tag;
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub(), acc);
    }
    case 1: {
        ftRobotArticleSlotTag tag;
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub(), acc);
    }
    case 2: {
        ftRobotArticleSlotTag tag;
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub(), acc);
    }
    case 3: {
        ftRobotArticleSlotTag tag;
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub(), acc);
    }
    FT_ROBOT_UNUSED_SLOTS(ftRobotGetNullArticle())
    default: return ftRobotGetNullArticle();
    }
}

// Shooting only type-checks the article; the unused slots accept anything.
bool ftRobotArticleMediator::shoot(soModuleAccesser*, soArticle* article) {
    switch (ftRobotGetArticleId(article)) {
    case 0: { ftRobotArticleSlotTag tag; (void)dynamic_cast<wnRobotGyro&>(*article); return true; }
    case 1: { ftRobotArticleSlotTag tag; (void)dynamic_cast<wnRobotBeam&>(*article); return true; }
    case 2: { ftRobotArticleSlotTag tag; (void)dynamic_cast<wnRobotGyroHolder&>(*article); return true; }
    case 3: { ftRobotArticleSlotTag tag; (void)dynamic_cast<wnRobotFinalBeam&>(*article); return true; }
    FT_ROBOT_UNUSED_SLOTS(true)
    default: return false;
    }
}

// The abstract matrix pool still needs its base destructor for derived pools.
#pragma dont_inline on
ftVirtualNodeMatrixPool::~ftVirtualNodeMatrixPool() { }
#pragma dont_inline off

#pragma dont_inline on
soStatusModuleImpl::~soStatusModuleImpl() { }
#pragma dont_inline off

#pragma dont_inline on
soResourceIdAccesser::~soResourceIdAccesser() { }
#pragma dont_inline off

// Shared owner/weapon methods are absent from the SDK declarations. These ABI
// declarations preserve the observed PPC arguments until their classes are complete.
extern "C" s32 ftRobotOwnerGetTeam(ftOwner* owner);
extern "C" void ftRobotActivateGyro(wnRobotGyro* weapon, s32 founderTaskId,
                                   u32 resourceId, s32 team, const Vec3f* position,
                                   float lr, float power);

// The original Fighter owner getter uses slot 0x2EC of the primary vtable
// at +0x3C; the SDK declaration currently places getOwner at +0x2F0.
static ftOwner* ftRobotGetFounderOwner(Fighter* fighter) {
    typedef ftOwner* (*GetOwner)(Fighter*);
    void** table = *reinterpret_cast<void***>(reinterpret_cast<u8*>(fighter) + 0x3C);
    GetOwner getter = reinterpret_cast<GetOwner>(table[0x2EC / sizeof(void*)]);
    return getter(fighter);
}

bool ftRobotArticleActivator<wnRobotGyro>::activate(wnRobotGyro* weapon, soModuleAccesser* acc) {
    Fighter& founder = dynamic_cast<Fighter&>(*acc->m_stageObject);
    s32 founderTaskId = founder.m_taskId;
    float power = acc->getWorkManageModule().getFloat(0x11000014);
    float lr = acc->getPostureModule().getLr();
    Vec3f position(0.0f, 0.0f, 0.0f);
    s32 team = ftRobotOwnerGetTeam(ftRobotGetFounderOwner(&founder));
    u32 resourceId = acc->getResourceModule().getResourceIdAccesser()->getMdlResId();
    ftRobotActivateGyro(weapon, founderTaskId, resourceId, team, &position, lr, power);
    return true;
}

#include <mt/mt_prng.h>
#include <so/so_value_accesser.h>

// The SDK's team module is opaque. Only these observed virtual slots are used;
// neither view is constructed, and no fields or replacement vtables are emitted.
class ftRobotTeamAbiView {
public:
    virtual ~ftRobotTeamAbiView();
    virtual void reserved0C();
    virtual s32 getTeam(); // +0x10
};
class ftRobotTeamModuleAbiView {
public:
    virtual ~ftRobotTeamModuleAbiView();
    virtual void reserved0C();
    virtual ftRobotTeamAbiView* getTeam(); // +0x10
};
static s32 ftRobotGetModuleTeam(soModuleAccesser* acc) {
    ftRobotTeamModuleAbiView* module =
        reinterpret_cast<ftRobotTeamModuleAbiView*>(acc->m_enumerationStart->m_teamModule);
    return module->getTeam()->getTeam();
}
extern "C" u32 ftRobotOwnerGetFighterColor(ftOwner* owner);
extern "C" void ftRobotActivateGyroHolder(wnRobotGyroHolder* weapon, s32 founderTaskId,
                                         u32 resourceId, s32 team, const Vec3f* position,
                                         SituationKind situation, float lr);
extern "C" void ftRobotActivateFinalBeam(wnRobotFinalBeam* weapon, s32 founderTaskId,
                                        u32 resourceId, s32 team, const Vec3f* position,
                                        s32 count, s32 selection, float lr);

bool ftRobotArticleActivator<wnRobotGyroHolder>::activate(wnRobotGyroHolder* weapon, soModuleAccesser* acc) {
    Fighter& founder = dynamic_cast<Fighter&>(*acc->m_stageObject);
    (void)ftRobotOwnerGetFighterColor(ftRobotGetFounderOwner(&founder));
    s32 founderTaskId = acc->m_stageObject->m_taskId;
    SituationKind situation = acc->getSituationModule().getKind();
    Vec3f position(0.0f, 0.0f, 0.0f);
    float lr = acc->getPostureModule().getLr();
    s32 team = ftRobotGetModuleTeam(acc);
    u32 resourceId = acc->getResourceModule().getResourceIdAccesser()->getMdlResId();
    ftRobotActivateGyroHolder(weapon, founderTaskId, resourceId, team, &position, situation, lr);
    return true;
}

bool ftRobotArticleActivator<wnRobotFinalBeam>::activate(wnRobotFinalBeam* weapon, soModuleAccesser* acc) {
    float lr = acc->getPostureModule().getLr();
    Vec3f position(0.0f, 0.0f, 0.0f);
    s32 selection = 0;
    if (soValueAccesser::getConstantInt(acc, 0x5DCB, 0) > 1) {
        selection = randi(soValueAccesser::getConstantInt(acc, 0x5DCB, 0));
        if (selection == 0 || selection == 2) {
            acc->getControllerModule().setRumble(2, 0, false, 8);
        }
    }
    s32 founderTaskId = acc->m_stageObject->m_taskId;
    s32 count = soValueAccesser::getConstantInt(acc, 0x5DCB, 0);
    s32 team = ftRobotGetModuleTeam(acc);
    u32 resourceId = acc->getResourceModule().getResourceIdAccesser()->getEtcResId();
    ftRobotActivateFinalBeam(weapon, founderTaskId, resourceId, team, &position, count, selection, lr);
    return true;
}

#pragma dont_inline on
ftRobotTransactor* ftRobotTransactor::getInstance() {
    static ftRobotTransactor instance;
    return &instance;
}
#pragma dont_inline off

// Link event payload for the Final Smash articles: a kind and a result byte the receiver may set (HYPOTHESIS).
struct ftRobotFinalLinkEvent : soLinkEventArgs {
    s32 result;
    ftRobotFinalLinkEvent(int kind) : soLinkEventArgs(kind), result(-1) { }
};

// Final Smash (Diffusion Beam) driver, run every frame while flag 0x12000042 is set: R.O.B. is invincible, the beam
// article is started once the opening animation raises flag 0x12000044, then the volleys follow until the timer
// (int 0x10000042) runs out.
void ftRobot::updateFinal(soModuleAccesser* acc) {
    soGenerateArticleManageModule& articles = ftRobotGetArticleModule(acc);
    acc->getDamageModule().setReactionMul(soValueAccesser::getConstantFloat(acc, 0xfd4, 0));
    acc->getCollisionHitModule().setWhole(2, 0);
    if (acc->getWorkManageModule().isFlag(0x12000043) && acc->getWorkManageModule().getInt(0x10000042) > 0) {
        acc->getWorkManageModule().subInt(1, 0x10000042);
        int cueFrames = soValueAccesser::getConstantInt(acc, 0x5dca, 0);
        if (acc->getWorkManageModule().getInt(0x10000042) <= cueFrames && !acc->getWorkManageModule().isFlag(0x12000046)) {
            acc->getWorkManageModule().onFlag(0x12000046);
            acc->getEffectModule().reqCommon(0.0f, 0x25);
        }
        if (acc->getWorkManageModule().getInt(0x10000042) == 0) {
            acc->getWorkManageModule().offFlag(0x12000042);
            acc->getWorkManageModule().offFlag(0x12000043);
            acc->getWorkManageModule().offFlag(0x12000045);
            articles.removeExist(3, 0);
            acc->getCollisionHitModule().setWhole(0, 0);
            acc->getEffectModule().removeCommon(0x26);
            acc->getEffectModule().removeCommon(0x25);
            endFinal(true, true, false);
            acc->getControllerModule().stopRumbleKind(2, 8);
        } else if (acc->getWorkManageModule().getInt(0x10000042) == 1) {
            ftRobotGyroLinkEvent event(0x838);
            acc->getLinkModule().sendEventNodes(1, event, 0);
        }
    }
    if (acc->getWorkManageModule().isFlag(0x12000044)) {
        soArticle* beam = articles.generate(3, NULL, NULL);
        if (!beam->isNull()) {
            articles.entry(beam);
        }
        acc->getWorkManageModule().offFlag(0x12000044);
        acc->getWorkManageModule().onFlag(0x12000045);
    }
    if (acc->getWorkManageModule().isFlag(0x12000045) && soValueAccesser::getConstantInt(acc, 0x5dcb, 0) > 1) {
        acc->getWorkManageModule().subInt(1, 0x10000043);
        if (acc->getWorkManageModule().getInt(0x10000043) <= 0) {
            ftRobotFinalLinkEvent event(0x839);
            acc->getLinkModule().sendEventNodes(1, event, 0);
            acc->getControllerModule().stopRumbleKind(2, 8);
            if (event.result != 1) {
                acc->getControllerModule().setRumble(2, 0, false, 8);
            }
            m_moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(acc, 0x5dcc, 0), 0x10000043);
        }
    }
}
