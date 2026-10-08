#pragma once

#include <ft/builder/ft_builder_kinetic.h>
#include <so/article/so_article.h>
#include <wn/weapon.h>
#include <ft/ft_common_data_accesser.h>

// Shared soArticle::setDeactivateDescendant entry point, declared under a local
// name until the SDK exposes it. It receives the soArticle base pointer.
extern "C" bool ftRobotDeactivateArticle(soArticle* article);

// Construction descriptors inferred from the article holder call sites.
struct ftRobotArticleKindInfo {
    s32 m_kind;
    s32 m_subKind;
    ftRobotArticleKindInfo() : m_kind(0), m_subKind(Fighter_Robot) { }
};
struct ftRobotArticleConstructionInfo {
    const ftRobotArticleKindInfo* m_kindInfo;
    void* m_heapModule;
    ftRobotArticleConstructionInfo(const ftRobotArticleKindInfo& kind, void* heap) :
        m_kindInfo(&kind), m_heapModule(heap) { }
};
// Robot-specific declaration of the shared weapon-data lookup entry point.
// Its full SDK template type is not reconstructed yet.
class ftRobotArticleDataAccesser {
public:
    void* getBeamData(ftKind kind, bool* resourceGroup) const;
    void* getFinalBeamData(ftKind kind, bool* resourceGroup) const;
    void* getGyroHolderData(ftKind kind, bool* resourceGroup) const;
    void* getGyroData(ftKind kind, bool* resourceGroup) const;
};
static_assert(sizeof(ftRobotArticleKindInfo) == 8, "Article kind descriptor is wrong!");
static_assert(sizeof(ftRobotArticleConstructionInfo) == 8, "Article construction descriptor is wrong!");

// Shared checker preserves the inactive/oldest-active selection policy.
class soArticleDeactivateChecker {
    soArticle* m_candidate;
public:
    soArticleDeactivateChecker();
    ~soArticleDeactivateChecker();
    bool operator()(soArticle* article);
    soArticle* getCandidate() const { return m_candidate; }
};
static_assert(sizeof(soArticleDeactivateChecker) == 4, "Article checker is wrong!");
// The shared null article has a 0x24-byte implementation; only its address is used.
extern u8 g_ftRobotNullArticleStorage[0x24];

// Weapon implementation storage is still opaque. Sizes follow adjacent holder
// offsets in the article builder; each destructor is an existing REL entry point.
class wnRobotGyro : public Weapon {
    u8 m_unreconstructed[0x2030 - sizeof(Weapon)];
public:
    wnRobotGyro(s32 articleId, const ftRobotArticleConstructionInfo& info, void* data);
    virtual ~wnRobotGyro();
};
class wnRobotBeam : public Weapon {
    u8 m_unreconstructed[0x2020 - sizeof(Weapon)];
public:
    wnRobotBeam(s32 articleId, const ftRobotArticleConstructionInfo& info, void* data);
    virtual ~wnRobotBeam();
};
class wnRobotGyroHolder : public Weapon {
    u8 m_unreconstructed[0x1bfc - sizeof(Weapon)];
public:
    wnRobotGyroHolder(s32 articleId, const ftRobotArticleConstructionInfo& info, void* data);
    virtual ~wnRobotGyroHolder();
};
class wnRobotFinalBeam : public Weapon {
    u8 m_unreconstructed[0x220c - sizeof(Weapon)];
public:
    wnRobotFinalBeam(s32 articleId, const ftRobotArticleConstructionInfo& info, void* data);
    virtual ~wnRobotFinalBeam();
};
static_assert(sizeof(wnRobotGyro) == 0x2030, "Gyro layout is wrong!");
static_assert(sizeof(wnRobotBeam) == 0x2020, "Beam layout is wrong!");
static_assert(sizeof(wnRobotGyroHolder) == 0x1bfc, "Gyro holder layout is wrong!");
static_assert(sizeof(wnRobotFinalBeam) == 0x220c, "Final beam layout is wrong!");

template <class W> struct ftRobotArticleActivator;
template <> struct ftRobotArticleActivator<wnRobotGyro> {
    static bool activate(wnRobotGyro* weapon, soModuleAccesser* acc);
};
template <> struct ftRobotArticleActivator<wnRobotGyroHolder> {
    static bool activate(wnRobotGyroHolder* weapon, soModuleAccesser* acc);
};
template <> struct ftRobotArticleActivator<wnRobotFinalBeam> {
    static bool activate(wnRobotFinalBeam* weapon, soModuleAccesser* acc);
};
class ftRobotTransactor {
public:
    ftRobotTransactor();
    virtual ~ftRobotTransactor();
    // Local declaration of the REL singleton-holder entry point.
    static ftRobotTransactor* getInstance();
    bool activeArticle1(wnRobotBeam* weapon, soModuleAccesser* acc, u32 resourceId);
};
static_assert(sizeof(ftRobotTransactor) == 4, "Transactor singleton layout is wrong!");
template <> struct ftRobotArticleActivator<wnRobotBeam> {
    static bool activate(wnRobotBeam* weapon, soModuleAccesser* acc);
};

FT_DOL_ARRAY_VECTOR(soArticle*, 4);
// The SDK exposes a 12-byte observer prefix. The original array constructor
// uses a 16-byte stride; preserve the trailing word without changing SDK users.
template <>
class soArrayVector<soArticleEventObserver, 4> : public soArrayVectorAbstract<soArticleEventObserver> {
    s32 m_topIndex : sizeof(bit_width<4>) + 1;
    s32 m_lastIndex : sizeof(bit_width<4>) + 1;
    s32 m_size : sizeof(bit_width<4>) + 1;
    u32 m_isFull : 1;
    struct ObserverSlot { soArticleEventObserver m_observer; u32 m_unkC; };
    ObserverSlot m_elements[4];
public:
    soArrayVector(s32 = 0);
    soArrayVector(s32 size, s32);
    soArrayVector(s32 size, const soArticleEventObserver& element, s32);
    virtual s32 size() const;
    virtual ~soArrayVector();
    virtual s32 capacity() const;
    virtual bool isFull() const;
    virtual soArticleEventObserver& atFastAbstractSub(s32 index) const;
    virtual soArticleEventObserver& getArrayValueConst(s32 index);
    virtual s32 getTopIndex() const;
    virtual s32 getLastIndex() const;
    virtual void setSize(s32 size);
    virtual void setTopIndex(s32 topIndex);
    virtual void setLastIndex(s32 lastIndex);
    virtual void onFull();
    virtual void offFull();
};
static_assert(sizeof(soArrayVector<soArticleEventObserver, 4>) == 0x4c, "Observer array layout is wrong!");

template <class W> struct ftRobotArticleTraits;
template <> struct ftRobotArticleTraits<wnRobotGyro> {
    enum { ArticleId = 0 };
    static void* getData() {
        bool resourceGroup = false;
        const ftRobotArticleDataAccesser* accesser =
            reinterpret_cast<const ftRobotArticleDataAccesser*>(&g_ftCommonDataAccesser);
        return accesser->getGyroData(Fighter_Robot, &resourceGroup);
    }
};
template <> struct ftRobotArticleTraits<wnRobotBeam> {
    enum { ArticleId = 1 };
    static void* getData() {
        bool resourceGroup = false;
        const ftRobotArticleDataAccesser* accesser =
            reinterpret_cast<const ftRobotArticleDataAccesser*>(&g_ftCommonDataAccesser);
        return accesser->getBeamData(Fighter_Robot, &resourceGroup);
    }
};
template <> struct ftRobotArticleTraits<wnRobotGyroHolder> {
    enum { ArticleId = 2 };
    static void* getData() {
        bool resourceGroup = false;
        const ftRobotArticleDataAccesser* accesser =
            reinterpret_cast<const ftRobotArticleDataAccesser*>(&g_ftCommonDataAccesser);
        return accesser->getGyroHolderData(Fighter_Robot, &resourceGroup);
    }
};
template <> struct ftRobotArticleTraits<wnRobotFinalBeam> {
    enum { ArticleId = 3 };
    static void* getData() {
        bool resourceGroup = false;
        const ftRobotArticleDataAccesser* accesser =
            reinterpret_cast<const ftRobotArticleDataAccesser*>(&g_ftCommonDataAccesser);
        return accesser->getFinalBeamData(Fighter_Robot, &resourceGroup);
    }
};

// The helpers use their own names while the original template configuration is
// reconstructed. Each subpool owns its predecessor, followed by one weapon.
template <class W>
class ftRobotArticleHolder : public soInstancePoolRoot {
    W m_instance;
public:
    ftRobotArticleHolder(soModuleAccesser* acc);
    virtual ~ftRobotArticleHolder();
    W* getInstance() { return &m_instance; }
};

template <class W, int N>
class ftRobotArticleSubPool : public soInstancePoolRoot {
    ftRobotArticleSubPool<W, N - 1> m_next;
    ftRobotArticleHolder<W> m_holder;
public:
    ftRobotArticleSubPool(soModuleAccesser* acc) : soInstancePoolRoot(acc),
        m_next(acc), m_holder(acc) { }
    virtual ~ftRobotArticleSubPool();
    W* getInstanceAt(s32 index) {
        if (index == N - 1) {
            return m_holder.getInstance();
        }
        return m_next.getInstanceAt(index);
    }
};

template <class W>
class ftRobotArticleSubPool<W, 0> {
    u32 m_terminal;
public:
    ftRobotArticleSubPool(soModuleAccesser*) : m_terminal(0) { }
    W* getInstanceAt(s32) { return NULL; }
};

template <class W, int N, class Base>
class ftRobotArticlePool : public Base {
    ftRobotArticleSubPool<W, N> m_sub;
public:
    ftRobotArticlePool(soModuleAccesser* acc) : Base(acc), m_sub(acc) { }
    virtual ~ftRobotArticlePool();
    ftRobotArticleSubPool<W, N>& getSub() { return m_sub; }
};

template <class W, int N, class Base>
class ftRobotArticleHierarchy : public ftRobotArticlePool<W, N, Base> {
public:
    ftRobotArticleHierarchy(soModuleAccesser* acc) :
        ftRobotArticlePool<W, N, Base>(acc) { }
    virtual ~ftRobotArticleHierarchy();
};

typedef ftRobotArticleHierarchy<wnRobotFinalBeam, 1, soInstancePoolRoot> ftRobotFinalBeamPool;
typedef ftRobotArticleHierarchy<wnRobotGyroHolder, 1, ftRobotFinalBeamPool> ftRobotGyroHolderPool;
typedef ftRobotArticleHierarchy<wnRobotBeam, 2, ftRobotGyroHolderPool> ftRobotBeamPool;
typedef ftRobotArticleHierarchy<wnRobotGyro, 1, ftRobotBeamPool> ftRobotGyroPool;
static_assert(sizeof(ftRobotGyroPool) == 0x9eb4, "Article pools layout is wrong!");

class soArticleGenerator {
public:
    virtual ~soArticleGenerator() { }
    virtual soArticle* generate(s32 articleId, soModuleAccesser* acc) = 0;
};
class soArticleOperator {
public:
    virtual ~soArticleOperator() { }
    virtual bool shoot(soModuleAccesser* acc, soArticle* article) = 0;
};
class soArticleMediator : public soArticleGenerator, public soArticleOperator {
public:
    soArticleMediator(soModuleAccesser*) { }
    virtual ~soArticleMediator();
    virtual void deactivate() = 0;
    virtual bool isGeneratable(soModuleAccesser* acc, s32 articleId) = 0;
    virtual s32 getActiveNum(soModuleAccesser* acc, s32 articleId) = 0;
    virtual s32 getGenerateMaxNum(s32 articleId) = 0;
    virtual s32 getMediateNum() = 0;
    virtual void setAutoRecycle(bool enabled) = 0;
};

class ftRobotArticleMediator : public soArticleMediator {
    ftRobotGyroPool m_pools;
    u8 m_autoRecycle;
public:
    ftRobotArticleMediator(soModuleAccesser* acc) :
        soArticleMediator(acc), m_pools(acc), m_autoRecycle(false) { }
    virtual ~ftRobotArticleMediator();
    // Generation/shooting are partial; supporting activators still use original entries.
    virtual soArticle* generate(s32 articleId, soModuleAccesser* acc);
    virtual bool shoot(soModuleAccesser* acc, soArticle* article);
    virtual s32 getMediateNum();
    virtual void setAutoRecycle(bool enabled);
    virtual void deactivate();
    virtual s32 getGenerateMaxNum(s32 articleId);
    virtual s32 getActiveNum(soModuleAccesser* acc, s32 articleId);
    virtual bool isGeneratable(soModuleAccesser* acc, s32 articleId);
};
class ftRobotSelectedArticleMediator {
    ftRobotArticleMediator m_mediator;
public:
    ftRobotSelectedArticleMediator(soModuleAccesser* acc) : m_mediator(acc) { }
    ~ftRobotSelectedArticleMediator();
};
static_assert(sizeof(ftRobotSelectedArticleMediator) == 0x9ec0, "Article mediator layout is wrong!");

#include <so/article/so_generate_article_manage_module.h>

class ftRobotArticleManageModuleBuilder {
    soArrayVector<soArticle*, 4> m_articles;
    soArrayVector<soArticleEventObserver, 4> m_observers;
    ftRobotSelectedArticleMediator m_mediator;
    soGenerateArticleManageModuleImpl m_module;
public:
    // Partial construction: vtable/member offsets and descriptor setup still need verification.
    ftRobotArticleManageModuleBuilder(soModuleAccesser* acc);
    ~ftRobotArticleManageModuleBuilder();
    void* getModule() { return &m_module; }
};
static_assert(sizeof(ftRobotArticleManageModuleBuilder) == 0x9f64, "Article builder layout is wrong!");

