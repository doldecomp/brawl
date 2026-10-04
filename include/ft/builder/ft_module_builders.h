#pragma once

// Module builders shared by all fighters. Each soXModuleBuilder<BC> owns the storage a module needs
// (arrays, helper objects) followed by the module implementation, and constructs them in the order
// Brawl did. See ft_fighter_builder.h for how they are assembled (soModuleAccesserBuilder).
//
// Naming follows Brawl (soXModuleBuildConfig<...> / soXModuleBuilder<BC>).

#include <ft/builder/ft_dol_array_list.h>
#include <ft/builder/ft_dol_types.h>
#include <so/so_array.h>
#include <so/so_module_accesser.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/collision/so_collision_hit_module_impl.h>
#include <so/posture/so_posture_module_impl.h>
#include <so/model/so_model_module_impl.h>
#include <types.h>

////////////////////////////////////////
// Module access for the BrawlHeaders attack/hit builders. Their getModule() cannot be instantiated
// (the module member of the build config is private), so locate the module behind the arrays instead.
////////////////////////////////////////

template <class B>
struct ftBuilderModule;

template <soCollision::Category Cat, u32 P, u32 A, class M, u32 G, bool b1, bool b2>
struct ftBuilderModule<soCollisionAttackModuleBuilder<soCollisionAttackModuleBuildConfig<Cat, P, A, M, G, b1, b2> > > {
    typedef soCollisionAttackModuleBuilder<soCollisionAttackModuleBuildConfig<Cat, P, A, M, G, b1, b2> > BuilderType;
    static soCollisionAttackModule* get(BuilderType* b) {
        return (soCollisionAttackModule*)((u8*)b + sizeof(soArrayVector<soCollisionAttackPart, P>) +
                                          sizeof(soArrayVector<soCollisionGroup, G>) +
                                          sizeof(soArrayVector<soCollisionAttackAbsolute, A>));
    }
};

template <soCollision::Category Cat, u32 P, u32 G, class M, u32 Mask, bool b1>
struct ftBuilderModule<soCollisionHitModuleBuilder<soCollisionHitModuleBuildConfig<Cat, P, G, M, Mask, b1> > > {
    typedef soCollisionHitModuleBuilder<soCollisionHitModuleBuildConfig<Cat, P, G, M, Mask, b1> > BuilderType;
    static soCollisionHitModule* get(BuilderType* b) {
        return (soCollisionHitModule*)((u8*)b + sizeof(soArrayVector<soCollisionHitPart, P>) +
                                       sizeof(soArrayVector<soCollisionGroup, G>) +
                                       sizeof(soArrayVector<soCollisionHitGroup, G>));
    }
};


////////////////////////////////////////
// soGroundModuleBuilder
////////////////////////////////////////


template <s32 ShapeCap, typename T>
class soGroundModuleBuildConfig {
    soArrayVector<soGroundShapeImpl, ShapeCap> m_shapes;
    T m_groundModule;
public:
    soGroundModuleBuildConfig(soModuleAccesser* acc, soGroundConditionChecker* checker) :
        m_shapes(1, 0),
        m_groundModule(acc, &m_shapes, checker, &g_soEventObserverRegistrationDescNull) { }
    T* getModule() { return &m_groundModule; }
};

template <typename BC>
class soGroundModuleBuilder {
    BC m_buildConfig;
public:
    soGroundModuleBuilder(soModuleAccesser* acc, soGroundConditionChecker* checker) : m_buildConfig(acc, checker) { }
    soGroundModule* getModule() { return m_buildConfig.getModule(); }
};

////////////////////////////////////////
// soCameraModuleBuilder
////////////////////////////////////////


template <typename T>
class soCameraModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soCameraModuleBuilder {
    soArrayVector<soCameraSubject, 1> m_subjects;
    typename BC::ModuleType m_cameraModule;
public:
    soCameraModuleBuilder(soModuleAccesser* acc, soSet<soCameraRange>* rangeSet, soSet<soCameraClipSphere>* clipSet,
                          soEventObserverRegistrationDesc* regDesc) :
        m_subjects(1, 0), m_cameraModule(acc, &m_subjects, rangeSet, clipSet, regDesc) { }
    typename BC::ModuleType* getModule() { return &m_cameraModule; }
};

////////////////////////////////////////
// soShakeModuleBuilder
////////////////////////////////////////


template <s32 N, typename T>
class soShakeModuleBuildConfig {
public:
    enum { TermCapacity = N };
    typedef T ModuleType;
};

template <typename BC>
class soShakeModuleBuilder {
    soArrayVector<soShakeTerm, BC::TermCapacity> m_terms;
    typename BC::ModuleType m_shakeModule;
public:
    soShakeModuleBuilder(soModuleAccesser* acc, void* shakeData) :
        m_terms(4, 0), m_shakeModule(acc, &m_terms, shakeData) { }
    typename BC::ModuleType* getModule() { return &m_shakeModule; }
};

////////////////////////////////////////
// soControllerModuleBuilder
////////////////////////////////////////


template <typename T>
class soControllerModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soControllerModuleBuilder {
    soArrayVector<soControllerImpl, 10> m_controllers;
    soArrayVector<soControllerClatter, 2> m_clatters;
    typename BC::ModuleType m_controllerModule;
public:
    soControllerModuleBuilder(soModuleAccesser* acc, s16 unitId) :
        m_controllers(10, 0), m_clatters(2, 0), m_controllerModule(acc, unitId, &m_controllers, &m_clatters) { }
    typename BC::ModuleType* getModule() { return &m_controllerModule; }
};

////////////////////////////////////////
// soDamageModuleBuilder
////////////////////////////////////////


template <typename T>
class soDamageModuleBuildConfig {
public:
    typedef T ModuleType;
};

extern char g_soDamageModuleNullA[];
extern char g_soDamageModuleNullB[];

template <typename BC>
class soDamageModuleBuilder {
    soArrayVector<soDamage, 1> m_damages;
    typename BC::ModuleType m_damageModule;
public:
    soDamageModuleBuilder(soModuleAccesser* acc, soEventObserverRegistrationDesc* regDesc) :
        m_damages(1, 0), m_damageModule(acc, &m_damages, g_soDamageModuleNullA, g_soDamageModuleNullB, regDesc) { }
    typename BC::ModuleType* getModule() { return &m_damageModule; }
};

////////////////////////////////////////
// soCollisionCatchModuleBuilder
////////////////////////////////////////


template <typename T>
class soCollisionCatchModuleBuildConfig {
public:
    enum { Flag = 1 };
    typedef T ModuleType;
};

template <typename BC>
class soCollisionCatchModuleBuilder {
    soArrayVector<soCollisionCatchPart, 4> m_parts;
    typename BC::ModuleType m_catchModule;
public:
    soCollisionCatchModuleBuilder(soModuleAccesser* acc, int taskId, gfTask::Category category, soEventObserverRegistrationDesc* regDesc) :
        m_parts(4, soCollisionCatchPart(soCollision::Category_Fighter), 0),
        m_catchModule(acc, taskId, category, &m_parts, regDesc, BC::Flag, BC::Flag) { }
    typename BC::ModuleType* getModule() { return &m_catchModule; }
};

////////////////////////////////////////
// soCollisionShieldModuleBuilder (shield / reflector)
////////////////////////////////////////


template <s32 Kind, s32 NumParts, typename Presenter, typename T>
class soCollisionShieldModuleBuildConfig {
public:
    enum { PartKind = Kind, PartCapacity = NumParts };
    typedef Presenter PresenterType;
    typedef T ModuleType;
};

template <typename BC>
class soCollisionShieldModuleBuilder {
    soArrayVector<soCollisionShieldPart, BC::PartCapacity> m_parts;
    soArrayVector<soCollisionShieldGroup, 2> m_shieldGroups;
    soArrayVector<soCollisionGroup, 2> m_groups;
    typename BC::PresenterType m_presenter;
    typename BC::ModuleType m_shieldModule;
public:
    soCollisionShieldModuleBuilder(soModuleAccesser* acc, int taskId, gfTask::Category category) :
        m_parts(BC::PartCapacity, soCollisionShieldPart(soCollision::Category_Fighter, BC::PartKind), 0),
        m_shieldGroups(2, 0), m_groups(2, 0), m_presenter(acc),
        m_shieldModule(acc, taskId, category, &m_parts, &m_groups, &m_shieldGroups, &m_presenter, BC::PartKind, true) { }
    typename BC::ModuleType* getModule() { return &m_shieldModule; }
};

////////////////////////////////////////
// soLinkModuleBuilder
////////////////////////////////////////


template <typename T>
class soLinkModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soLinkModuleBuilder {
    soArrayVector<soLinkConnection, 7> m_connections;
    typename BC::ModuleType m_linkModule;
public:
    soLinkModuleBuilder(s32 unitId) : m_connections(7, 0), m_linkModule(unitId, &m_connections) { }
    typename BC::ModuleType* getModule() { return &m_linkModule; }
};

////////////////////////////////////////
// soPhysicsModuleBuilder
////////////////////////////////////////


template <typename T>
class soPhysicsModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soPhysicsModuleBuilder {
    soArrayVector<soPhysicsIKHandle, 2> m_ikHandles;
    typename BC::ModuleType m_physicsModule;
public:
    soPhysicsModuleBuilder(soModuleAccesser* acc, void* ikData) :
        m_ikHandles(2, 0), m_physicsModule(acc, ikData, &m_ikHandles, 1) { }
    typename BC::ModuleType* getModule() { return &m_physicsModule; }
};

////////////////////////////////////////
// soItemManageModuleBuilder
////////////////////////////////////////


template <typename T>
class soItemManageModuleBuildConfig {
public:
    typedef T ModuleType;
};

extern char g_soItemManageNullA[];
extern char g_soItemManageNullB[];

template <typename BC>
class soItemManageModuleBuilder {
    soArrayVector<soItemInfo, 3> m_items;
    soArrayVector<soItemInfo, 4> m_items2;
    typename BC::ModuleType m_itemModule;
public:
    soItemManageModuleBuilder(soModuleAccesser* acc, void* itemNodeData) :
        m_items(3, 0), m_items2(), m_itemModule(acc, &m_items, &m_items2, itemNodeData, g_soItemManageNullA, g_soItemManageNullB) { }
    typename BC::ModuleType* getModule() { return &m_itemModule; }
};

////////////////////////////////////////
// soEffectModuleBuilder
////////////////////////////////////////


template <typename T>
class soEffectModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soEffectModuleBuilder {
    soArrayVector<soEffectContinual, 1> m_continuals;
    soArrayVector<soEffectTime, 1> m_times;
    soArrayVector<efScreenHandle, 1> m_screens;
    soArrayVector<u32, 1> m_u32s;
    typename BC::ModuleType m_effectModule;
public:
    soEffectModuleBuilder(soModuleAccesser* acc, void* nodeData, void* emitData, void* commonData, void* screenData,
                          soEventObserverRegistrationDesc* regDesc) :
        m_continuals(1, 0), m_times(1, 0), m_screens(1, 0), m_u32s(1, 0, 0),
        m_effectModule(acc, &m_continuals, nodeData, &m_u32s, &m_times, emitData, regDesc, commonData, 10, screenData, &m_screens) { }
    typename BC::ModuleType* getModule() { return &m_effectModule; }
};

////////////////////////////////////////
// soAnimCmdModuleBuilder
////////////////////////////////////////

template <typename T>
class soAnimCmdModuleBuildConfig {
public:
    typedef T ModuleType;
};

////////////////////////////////////////
// soSoundModuleBuilder
////////////////////////////////////////

#include <so/sound/so_sound_module_impl.h>

// REL-local 3D sound generator accesser (two generator instances)
class ftSound3dGeneratorAccesserImpl : public soSound3dGeneratorAccesser {
    GeneratorInstance m_instances[2];
public:
    ftSound3dGeneratorAccesserImpl() {
        for (s32 i = 0; i < 2; i++) {
            m_instances[i].initialize();
        }
    }
    virtual ~ftSound3dGeneratorAccesserImpl() { }
    virtual void activate(Vec3f* pos) {
        for (s32 i = 0; i < 2; i++) {
            allocateInstance(&m_instances[i], pos);
        }
    }
    virtual void deactivate() {
        for (s32 i = 0; i < 2; i++) {
            freeInstance(&m_instances[i]);
        }
    }
    virtual GeneratorInstance* getInstance(int idx) { return &m_instances[idx]; }
};

template <typename T>
class soSoundModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soSoundModuleBuilder {
    ftSound3dGeneratorAccesserImpl m_generator;
    typename BC::ModuleType m_soundModule;
public:
    soSoundModuleBuilder(soModuleAccesser* acc, soSoundIdExchanger* exchanger, soEventObserverRegistrationDesc* regDesc) :
        m_generator(), m_soundModule(acc, &m_generator, exchanger, true, true, regDesc) { }
    typename BC::ModuleType* getModule() { return &m_soundModule; }
};

////////////////////////////////////////
// Builders that hold a single module (the original inlined their constructors into the fighter constructor,
// but each of them still has its own out-of-line destructor)
////////////////////////////////////////

template <typename T>
class soSituationModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soSituationModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soSituationModuleBuilder(s16 unitId, soModuleAccesser* acc, soEventObserverRegistrationDesc* regDesc) : m_module(unitId, acc, regDesc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <s32 N, typename T>
class soCatchModuleBuildConfig {
public:
    enum { Flag = N };
    typedef T ModuleType;
};

template <typename BC>
class soCatchModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soCatchModuleBuilder(soModuleAccesser* acc) : m_module(acc, BC::Flag) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soCaptureModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soCaptureModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soCaptureModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soStopModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soStopModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soStopModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soTurnModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soTurnModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soTurnModuleBuilder(soModuleAccesser* acc) : m_module(acc) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T, s32 N>
class soVisibilityModuleBuildConfig {
public:
    enum { Flag = N };
    typedef T ModuleType;
};

template <typename BC>
class soVisibilityModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soVisibilityModuleBuilder(soModuleAccesser* acc, soVisibilityData* data) : m_module(acc, data, BC::Flag) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soWorkManageModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soWorkManageModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soWorkManageModuleBuilder(soModuleAccesser* acc, void* paramAccesser) : m_module(acc, paramAccesser) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <s32 A, s32 B, typename T>
class soSlopeModuleBuildConfig {
public:
    enum { Arg0 = A, Arg1 = B };
    typedef T ModuleType;
};

template <typename BC>
class soSlopeModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soSlopeModuleBuilder(soModuleAccesser* acc, float slopeAngleLimit) : m_module(acc, BC::Arg0, BC::Arg1, 0, slopeAngleLimit) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

template <typename T>
class soShadowModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soShadowModuleBuilder {
    typename BC::ModuleType m_module;
public:
    soShadowModuleBuilder(soModuleAccesser* acc) : m_module(acc, 0.0f, 0) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};
