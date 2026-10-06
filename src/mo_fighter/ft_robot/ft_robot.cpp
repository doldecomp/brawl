#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/robot/ft_robot.h>
#include <ft/robot/ft_robot_extend_param_accesser.h>

#define FT_BC ftRobotBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftRobotExtendParamAccesser g_ftRobotExtendParamAccesser;
ftClassInfoImpl<Fighter_Robot, ftRobot> g_ftClassInfoRobot;

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
    // TODO: install Robot status processes, model/node conversion and physics configuration.
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

template <class W, int N>
static s32 ftRobotCountActiveArticles(ftRobotArticleSubPool<W, N>& pool) {
    s32 count = 0;
    for (s32 i = 0; i < N; ++i) {
        if (pool.getInstanceAt(i)->isActiveArticle() == true) {
            ++count;
        }
    }
    return count;
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

s32 ftRobotArticleMediator::getGenerateMaxNum(s32 articleId) {
    switch (articleId) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 1;
    case 3: return 1;
    default: return 0;
    }
}

s32 ftRobotArticleMediator::getActiveNum(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0:
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub());
    case 1:
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub());
    case 2:
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub());
    case 3:
        return ftRobotCountActiveArticles(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub());
    default: return 0;
    }
}

bool ftRobotArticleMediator::isGeneratable(soModuleAccesser*, s32 articleId) {
    switch (articleId) {
    case 0:
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub());
    case 1:
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub());
    case 2:
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub());
    case 3:
        return ftRobotCanGenerateArticle(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub());
    default: return false;
    }
}

void ftRobot::onActivate() {
    m_moduleAccesser->getWorkManageModule().setInt(0, 0x10000044);
}

void ftRobot::notifyEventOnDamage(soDamage* damage, bool flag, soModuleAccesser* acc) {
    Fighter::notifyEventOnDamage(damage, flag, acc);
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
    case 0:
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotGyro, 1, ftRobotBeamPool> &>(m_pools).getSub(), acc);
    case 1:
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotBeam, 2, ftRobotGyroHolderPool> &>(m_pools).getSub(), acc);
    case 2:
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> &>(m_pools).getSub(), acc);
    case 3:
        return ftRobotGenerateFromPool(static_cast<ftRobotArticlePool<wnRobotFinalBeam, 1, soInstancePoolRoot> &>(m_pools).getSub(), acc);
    default: return ftRobotGetNullArticle();
    }
}

bool ftRobotArticleMediator::shoot(soModuleAccesser*, soArticle* article) {
    s32 articleId = ftRobotGetArticleId(article);
    switch (articleId) {
    case 0: (void)dynamic_cast<wnRobotGyro&>(*article); break;
    case 1: (void)dynamic_cast<wnRobotBeam&>(*article); break;
    case 2: (void)dynamic_cast<wnRobotGyroHolder&>(*article); break;
    case 3: (void)dynamic_cast<wnRobotFinalBeam&>(*article); break;
    default:
        // The remaining generated article kinds have no Robot-specific action.
        return articleId >= 4 && articleId <= 16;
    }
    return true;
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
