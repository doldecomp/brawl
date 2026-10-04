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

#pragma dont_inline on
template soResourceModuleBuilder<FT_BC::ResourceModuleBuildConfig>::soResourceModuleBuilder(u32, u32, u8, soModuleAccesser*);
template soModelModuleBuilder<FT_BC::ModelModuleBuildConfig>::soModelModuleBuilder(soModuleAccesser*, void*, soEventObserverRegistrationDesc*, float);
template soPostureModuleBuilder<FT_BC::PostureModuleBuildConfig>::soPostureModuleBuilder(soModuleAccesser*, soEventObserverRegistrationDesc*);
template soGroundModuleBuilder<FT_BC::GroundModuleBuildConfig>::soGroundModuleBuilder(soModuleAccesser*, soGroundConditionChecker*);
template soCollisionAttackModuleBuilder<FT_BC::CollisionAttackModuleBuildConfig>::soCollisionAttackModuleBuilder(soModuleAccesser*, int, u8, soEventObserverRegistrationDesc*);
template soCollisionHitModuleBuilder<FT_BC::CollisionHitModuleBuildConfig>::soCollisionHitModuleBuilder(soModuleAccesser*, int, u8, soEventObserverRegistrationDesc*);
template soCollisionShieldModuleBuilder<FT_BC::CollisionShieldModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
template soCollisionShieldModuleBuilder<FT_BC::CollisionReflectorModuleBuildConfig>::soCollisionShieldModuleBuilder(soModuleAccesser*, int, gfTask::Category);
template soCollisionCatchModuleBuilder<FT_BC::CollisionCatchModuleBuildConfig>::soCollisionCatchModuleBuilder(soModuleAccesser*, int, gfTask::Category, soEventObserverRegistrationDesc*);
template soDamageModuleBuilder<FT_BC::DamageModuleBuildConfig>::soDamageModuleBuilder(soModuleAccesser*, soEventObserverRegistrationDesc*);
template soShakeModuleBuilder<FT_BC::ShakeModuleBuildConfig>::soShakeModuleBuilder(soModuleAccesser*, void*);
template soSoundModuleBuilder<FT_BC::SoundModuleBuildConfig>::soSoundModuleBuilder(soModuleAccesser*, soSoundIdExchanger*, soEventObserverRegistrationDesc*);
template soLinkModuleBuilder<FT_BC::LinkModuleBuildConfig>::soLinkModuleBuilder(s32);
template soControllerModuleBuilder<FT_BC::ControllerModuleBuildConfig>::soControllerModuleBuilder(soModuleAccesser*, s16);
template soCameraModuleBuilder<FT_BC::CameraModuleBuildConfig>::soCameraModuleBuilder(soModuleAccesser*, soSet<soCameraRange>*, soSet<soCameraClipSphere>*, soEventObserverRegistrationDesc*);
template soEffectModuleBuilder<FT_BC::EffectModuleBuildConfig>::soEffectModuleBuilder(soModuleAccesser*, void*, void*, void*, void*, soEventObserverRegistrationDesc*);
template soPhysicsModuleBuilder<FT_BC::PhysicsModuleBuildConfig>::soPhysicsModuleBuilder(soModuleAccesser*, void*);
template soItemManageModuleBuilder<FT_BC::ItemManageModuleBuildConfig>::soItemManageModuleBuilder(soModuleAccesser*, void*);
#pragma dont_inline off
