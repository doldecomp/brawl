// No include guard on purpose: define FT_BC (the character's BuildConfig class) and include this once in the
// character's .cpp, after ft_fighter_builder.h and before the character's constructor is defined.
//
// MATCH-ONLY: In the original build almost every module builder constructor ended up as a separate function
// in the REL (only the heap/param customize builders and the builders that hold a single module were inlined
// into the fighter constructor). MWCC's inliner gives up on such a big constructor, which we cannot reproduce
// by size alone, so the builder constructors are instantiated explicitly with inlining disabled instead.
#ifndef FT_BC
#error define FT_BC before including ft_builder_noinline.h
#endif

// MATCH-ONLY: the REL calls the module constructor out of line (it must be compiled outside of the dont_inline region)
soTransitionModuleImpl::soTransitionModuleImpl(soArray<soTransitionTermGroup>* groups) :
    m_transitionTermGroupArray(groups), m_groupID(0), m_transitionInfo() { } // 99%: the original keeps a dead store to a stack slot (frame 0x10)

// MATCH-ONLY: the original REL emits the vtables of these observers (their addObserver is a REL function); the code that
// needs them is not reconstructed yet, so keep them alive with a dummy user.
void ftKeepObserverVtables(s16 id) {
    soAnimCmdEventObserver animCmd(id);
    soSituationEventObserver situation(id);
}

#pragma dont_inline on
ftStatusGimmickUniqProcessPool::~ftStatusGimmickUniqProcessPool() { }
#pragma dont_inline off
soKineticModuleImpl::~soKineticModuleImpl() { }
#pragma dont_inline on
ftTeam::~ftTeam() { }
ftTeamIndirect::~ftTeamIndirect() { }
ftSound3dGeneratorAccesserImpl::~ftSound3dGeneratorAccesserImpl() { } // MATCH-ONLY: out of line in the REL
soTransitionInfo::~soTransitionInfo() { } // MATCH-ONLY: out of line in the REL
soNullable::soNullable(bool isNull) { m_isNull = isNull; } // MATCH-ONLY: out of line in the REL
soKineticEnergy::~soKineticEnergy() { } // MATCH-ONLY: out of line in the REL
soGeneralWorkAbstract::~soGeneralWorkAbstract() { } // MATCH-ONLY: out of line in the REL
#pragma dont_inline off

// MATCH-ONLY: the REL calls soGeneralWorkSimple's work area constructor out of line (defined here, not in the class).
soGeneralWorkSimple::soGeneralWorkSimple(s32* ints, u32 numInts, float* floats, u32 numFloats, u32* flags, u32 numFlags) :
    soGeneralWorkAbstract(false), m_intWorks(ints), m_intWorkSize(numInts), m_floatWorks(floats), m_floatWorkSize(numFloats),
    m_flagWorks(flags), m_flagWorkSize(numFlags) { }


#pragma dont_inline on
template soInsideEventManageModuleBuilder<FT_BC::InsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes>::soInsideEventManageModuleBuilder();
template soDamageModuleBuilder<FT_BC::DamageModuleBuildConfig>::soDamageModuleBuilder(soModuleAccesser*, soEventObserverRegistrationDesc*);
template soCameraModuleBuilder<FT_BC::CameraModuleBuildConfig>::soCameraModuleBuilder(soModuleAccesser*, soSet<soCameraRange>*, soSet<soCameraClipSphere>*, soEventObserverRegistrationDesc*);
template soResourceModuleBuilder<FT_BC::ResourceModuleBuildConfig>::soResourceModuleBuilder(u32, u32, u8, soModuleAccesser*);
template soModelModuleBuilder<FT_BC::ModelModuleBuildConfig>::soModelModuleBuilder(soModuleAccesser*, void*, soEventObserverRegistrationDesc*, float);
template soPostureModuleBuilder<FT_BC::PostureModuleBuildConfig>::soPostureModuleBuilder(soModuleAccesser*, soEventObserverRegistrationDesc*);
template soGroundModuleBuilder<FT_BC::GroundModuleBuildConfig>::soGroundModuleBuilder(soModuleAccesser*, soGroundConditionChecker*);
template soCollisionAttackModuleBuilder<FT_BC::CollisionAttackModuleBuildConfig>::soCollisionAttackModuleBuilder(soModuleAccesser*, int, u8, soEventObserverRegistrationDesc*);
template soCollisionHitModuleBuilder<FT_BC::CollisionHitModuleBuildConfig>::soCollisionHitModuleBuilder(soModuleAccesser*, int, u8, soEventObserverRegistrationDesc*);
template soCollisionShieldModuleBuilder<FT_BC::CollisionShieldModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
#ifndef FT_NO_REFLECTOR_INSTANTIATION // the builder with the folded in absorber instantiates its builders itself
template soCollisionReflectorModuleBuilder<FT_BC::CollisionReflectorModuleBuildConfig>::soCollisionReflectorModuleBuilder(soModuleAccesser*, int, gfTask::Category);
#endif
template soCollisionCatchModuleBuilder<FT_BC::CollisionCatchModuleBuildConfig>::soCollisionCatchModuleBuilder(soModuleAccesser*, int, gfTask::Category, soEventObserverRegistrationDesc*);
template soShakeModuleBuilder<FT_BC::ShakeModuleBuildConfig>::soShakeModuleBuilder(soModuleAccesser*, void*);
template soSoundModuleBuilder<FT_BC::SoundModuleBuildConfig>::soSoundModuleBuilder(soModuleAccesser*, soSoundIdExchanger*, soEventObserverRegistrationDesc*);
template soLinkModuleBuilder<FT_BC::LinkModuleBuildConfig>::soLinkModuleBuilder(s32);
template soControllerModuleBuilder<FT_BC::ControllerModuleBuildConfig>::soControllerModuleBuilder(soModuleAccesser*, s16);
template soEffectModuleBuilder<FT_BC::EffectModuleBuildConfig>::soEffectModuleBuilder(soModuleAccesser*, void*, void*, void*, void*, soEventObserverRegistrationDesc*);
template soPhysicsModuleBuilder<FT_BC::PhysicsModuleBuildConfig>::soPhysicsModuleBuilder(soModuleAccesser*, void*);
template soItemManageModuleBuilder<FT_BC::ItemManageModuleBuildConfig>::soItemManageModuleBuilder(soModuleAccesser*, void*);
template soMotionModuleBuilder<FT_BC::MotionModuleBuildConfig>::soMotionModuleBuilder(soModuleAccesser*, void*);
template soTeamModuleBuilder<FT_BC::TeamModuleBuildConfig>::soTeamModuleBuilder(s32, soModuleAccesser*);
template soAnimCmdModuleBuilder<FT_BC::AnimCmdModuleBuildConfig>::soAnimCmdModuleBuilder(s16);
template soStatusModuleBuilder<FT_BC::StatusModuleBuildConfig>::soStatusModuleBuilder(soModuleAccesser*, const soStatusData*, void*);
template soKineticModuleBuilder<FT_BC::KineticModuleBuildConfig>::soKineticModuleBuilder(soModuleAccesser*);
template soGeneralWorkBuilder<FT_BC::GeneralWorkBuildConfig>::soGeneralWorkBuilder();
template soAreaModuleBuilder<FT_BC::AreaModuleBuildConfig>::soAreaModuleBuilder(soModuleAccesser*, u8, soEventObserverRegistrationDesc*);
#pragma dont_inline off
