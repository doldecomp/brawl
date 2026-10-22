#pragma once

#include <StaticAssert.h>
#include <it/item.h>
#include <types.h>

class itBadgeCustomizer : public itCustomizer<itBadgeCustomizer> {
public:
    enum Action {
        Action_Infinity = 0x0,
        Action_Set_Have_Counter = 0x1,
    };

    virtual ~itBadgeCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itBadgeCustomizer) == 12, "Class is wrong size!");

class itBananaCustomizer : public itCustomizer<itBananaCustomizer> {
    virtual ~itBananaCustomizer();
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
};
static_assert(sizeof(itBananaCustomizer) == 12, "Class is wrong size!");

class itBeamSwordCustomizer : public itCustomizer<itBeamSwordCustomizer> {
public:
    enum Action {
        Action_Begin = 0x64,
        Action_End = 0x65,
        Action_Effect = 0x66,
        Action_Begin2 = 0x67,
    };

    virtual ~itBeamSwordCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itBeamSwordCustomizer) == 12, "Class is wrong size!");

class itMoneyCustomizer : public itCustomizer<itMoneyCustomizer> {
public:
    enum Action {

    };

    virtual ~itMoneyCustomizer();
    virtual void onReset(BaseItem* item);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual bool isSafe(BaseItem* item);
};
static_assert(sizeof(itMoneyCustomizer) == 12, "Class is wrong size!");

class itBombheiCustomizer : public itCustomizer<itBombheiCustomizer> {
    virtual ~itBombheiCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
};
static_assert(sizeof(itBombheiCustomizer) == 12, "Class is wrong size!");

class itChewingCustomizer : public itCustomizer<itChewingCustomizer> {
    virtual ~itChewingCustomizer();
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual bool onHave(BaseItem* item, int);
    virtual bool onReflect(BaseItem* item);
    virtual bool isReferenceControlerHave(BaseItem* item);
};
static_assert(sizeof(itChewingCustomizer) == 12, "Class is wrong size!");

class itClackerCustomizer : public itCustomizer<itClackerCustomizer> {
    virtual ~itClackerCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
};
static_assert(sizeof(itClackerCustomizer) == 12, "Class is wrong size!");

class itCurryShotCustomizer : public itCustomizer<itCurryShotCustomizer> {
    virtual ~itCurryShotCustomizer();
    virtual void onReset(BaseItem* item);
    virtual void onUpdateKinetic(BaseItem* item);
    virtual void onThrowAttack(BaseItem* item, float, float* lr, Vec3f*, Vec3f*, float* powerMulStatus, bool*);
};
static_assert(sizeof(itCurryShotCustomizer) == 12, "Class is wrong size!");

class itDoseisanCustomizer : public itCustomizer<itDoseisanCustomizer> {
    virtual ~itDoseisanCustomizer();
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
    virtual bool isUseSpeedDamage(BaseItem* item);
};
static_assert(sizeof(itDoseisanCustomizer) == 12, "Class is wrong size!");

class itDragoonSetCustomizer : public itCustomizer<itDragoonSetCustomizer> {
    virtual ~itDragoonSetCustomizer();
    virtual void onDestruct(BaseItem* item);
    virtual void onReset(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onProcessHit(BaseItem* item);
    virtual void onRenderDebug(BaseItem* item);
    virtual bool isUseScaleZ(BaseItem* item);
    virtual bool isConstraintHave(BaseItem* item);
    virtual bool isReferenceControlerHave(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itDragoonSetCustomizer) == 12, "Class is wrong size!");

class itDragoonSightCustomizer : public itCustomizer<itDragoonSightCustomizer> {
    virtual ~itDragoonSightCustomizer();
    virtual void onConstruct(BaseItem* item);
    virtual void onDestruct(BaseItem* item);
    virtual void onReset(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual int onGetLayerType(BaseItem* item);
};
static_assert(sizeof(itDragoonSightCustomizer) == 12, "Class is wrong size!");

class itFigureCustomizer : public itCustomizer<itFigureCustomizer> {
public:
    enum Action {
        Action_Touch_Get = 0x0,
        Action_Sleep = 0x1,
    };

    virtual ~itFigureCustomizer();
    virtual void onConstruct(BaseItem* item);
    virtual void onDestruct(BaseItem* item);
    virtual void onReset(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onRenderPre(BaseItem* item);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itFigureCustomizer) == 12, "Class is wrong size!");

class itFireFlowerCustomizer : public itCustomizer<itFireFlowerCustomizer> {
public:
    enum Action {
        Action_Open = 0x0,
        Action_Close = 0x1,
    };

    virtual ~itFireFlowerCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itFireFlowerCustomizer) == 12, "Class is wrong size!");

class itGoldenHammerCustomizer : public itCustomizer<itGoldenHammerCustomizer> {
public:
    enum Action {
       Action_Attack_On = 0x1,
       Action_Attack_Off = 0x2,
       Action_Flashing_On = 0x3,
    };

    virtual ~itGoldenHammerCustomizer();
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual bool onHave(BaseItem* item, int);
};
static_assert(sizeof(itGoldenHammerCustomizer) == 12, "Class is wrong size!");

class itGreenShellCustomizer : public itCustomizer<itGreenShellCustomizer> {
    virtual ~itGreenShellCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual bool onReflect(BaseItem* item);
    virtual bool isTreadPassive(BaseItem* item);
    virtual bool isUseShake(BaseItem* item);
};
static_assert(sizeof(itGreenShellCustomizer) == 12, "Class is wrong size!");

class itHammerCustomizer : public itCustomizer<itHammerCustomizer> {
public:
    enum Action {
        Action_Drop_Head = 0x0,
        Action_Attack_On = 0x1,
        Action_Attack_Off = 0x2,
        Action_Flashing_On = 0x3,
    };
    virtual ~itHammerCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itHammerCustomizer) == 12, "Class is wrong size!");

class itHarisenCustomizer : public itCustomizer<itHarisenCustomizer> {
public:
    enum Action {

    };

    virtual ~itHarisenCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itHarisenCustomizer) == 12, "Class is wrong size!");

class itKusudamaCustomizer : public itCustomizer<itKusudamaCustomizer> {
    virtual ~itKusudamaCustomizer();
    virtual bool isUsePhysics(BaseItem* item);
};
static_assert(sizeof(itKusudamaCustomizer) == 12, "Class is wrong size!");

class itTuchCustomizer : public itCustomizer<itTuchCustomizer> {
    virtual ~itTuchCustomizer();
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
};
static_assert(sizeof(itTuchCustomizer) == 12, "Class is wrong size!");

class itMetalBlockCustomizer : public itCustomizer<itMetalBlockCustomizer> {
    virtual ~itMetalBlockCustomizer();
    virtual bool onDamage(BaseItem* item, int, soDamageLog*);
};
static_assert(sizeof(itMetalBlockCustomizer) == 12, "Class is wrong size!");

class itPasaranCustomizer : public itCustomizer<itPasaranCustomizer> {
    virtual ~itPasaranCustomizer();
    virtual void onReset(BaseItem* item);
    virtual bool onReflect(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itPasaranCustomizer) == 12, "Class is wrong size!");

class itRayGunCustomizer : public itCustomizer<itRayGunCustomizer> {
    virtual ~itRayGunCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
};
static_assert(sizeof(itRayGunCustomizer) == 12, "Class is wrong size!");

class itRayGunShotCustomizer : public itCustomizer<itRayGunShotCustomizer> {
    virtual ~itRayGunShotCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
};
static_assert(sizeof(itRayGunShotCustomizer) == 12, "Class is wrong size!");

class itRipStickCustomizer : public itCustomizer<itRipStickCustomizer> {
    virtual ~itRipStickCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
};
static_assert(sizeof(itRipStickCustomizer) == 12, "Class is wrong size!");

class itRipStickFlowerCustomizer : public itCustomizer<itRipStickFlowerCustomizer> {
    virtual ~itRipStickFlowerCustomizer();
    virtual bool isUsePhysics(BaseItem* item);
};
static_assert(sizeof(itRipStickFlowerCustomizer) == 12, "Class is wrong size!");

class itSandbagCustomizer : public itCustomizer<itSandbagCustomizer> {
    virtual ~itSandbagCustomizer();
    virtual void onReset(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual bool onNotifyEventCaptureStatus(BaseItem* item); // TODO
    virtual bool onDamage(BaseItem* item, int, soDamageLog*);
    virtual void onPreBound(BaseItem* item, float*, BaseItem::BoundMask);
    virtual bool isUseTurnDamage(BaseItem* item);
    virtual bool isUseSpeedDamage(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itSandbagCustomizer) == 12, "Class is wrong size!");

class itSlowCustomizer : public itCustomizer<itSlowCustomizer> {
    virtual ~itSlowCustomizer();
    virtual int onResult(BaseItem* item);
};
static_assert(sizeof(itSlowCustomizer) == 12, "Class is wrong size!");

class itSmartBombCustomizer : public itCustomizer<itSmartBombCustomizer> {
    virtual ~itSmartBombCustomizer();
    virtual void onReset(BaseItem* item);
};
static_assert(sizeof(itSmartBombCustomizer) == 12, "Class is wrong size!");

class itSmashBallCustomizer : public itCustomizer<itSmashBallCustomizer> {
    virtual ~itSmashBallCustomizer();
    virtual void onNotifyEventAnimCmd(BaseItem* item, acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void onUpdateAiDir(BaseItem* item, Vec2f*, Vec2f*, Vec2f*, Vec2f*);
    virtual void onUpdateAiMove(BaseItem* item, Vec2f*, Vec2f*, Vec2f*);
    virtual bool onPreDamageCheck(BaseItem* item, int, soDamageLog*);
    virtual bool isUseSpeedDamage(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itSmashBallCustomizer) == 12, "Class is wrong size!");

class itSmokeScreenCustomizer : public itCustomizer<itSmokeScreenCustomizer> {
    virtual ~itSmokeScreenCustomizer();
    virtual void onReset(BaseItem* item);
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual bool onReflect(BaseItem* item);
    virtual bool isReferenceControlerHave(BaseItem* item);
};
static_assert(sizeof(itSmokeScreenCustomizer) == 12, "Class is wrong size!");

class itSpringCustomizer : public itCustomizer<itSpringCustomizer> {
    virtual ~itSpringCustomizer();
    virtual void onDestruct(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual void onNotifyEventGimmick(BaseItem* item, soGimmickEventArgs* eventInfo, int* taskId);
    virtual bool onHave(BaseItem* item, int);
};
static_assert(sizeof(itSpringCustomizer) == 12, "Class is wrong size!");

class itStarRodCustomizer : public itCustomizer<itStarRodCustomizer> {
    enum Action {
        Action_Begin = 0x64,
        Action_End = 0x65,
        Action_Effect = 0x66,
        Action_Begin2 = 0x67,
    };

    virtual ~itStarRodCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
    virtual void onAction(BaseItem* item, u32, float rate);
};
static_assert(sizeof(itStarRodCustomizer) == 12, "Class is wrong size!");

class itStarRodShotCustomizer : public itCustomizer<itStarRodShotCustomizer> {
    virtual ~itStarRodShotCustomizer();
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itStarRodShotCustomizer) == 12, "Class is wrong size!");

class itSuperScopeCustomizer : public itCustomizer<itSuperScopeCustomizer> {
    virtual ~itSuperScopeCustomizer();
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
};
static_assert(sizeof(itSuperScopeCustomizer) == 12, "Class is wrong size!");

class itTeamHealingCustomizer : public itCustomizer<itTeamHealingCustomizer> {
    virtual ~itTeamHealingCustomizer();
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
};
static_assert(sizeof(itTeamHealingCustomizer) == 12, "Class is wrong size!");

class itThunderCustomizer : public itCustomizer<itThunderCustomizer> {
    virtual ~itThunderCustomizer();
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual int onResult(BaseItem* item);
};
static_assert(sizeof(itThunderCustomizer) == 12, "Class is wrong size!");

class itUsagiHatCustomizer : public itCustomizer<itUsagiHatCustomizer> {
public:
    enum Action {
        Action_Infinity = 0x0,
        Action_Set_Have_Counter = 0x1,
    };

    virtual ~itUsagiHatCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual bool isUsePhysics(BaseItem* item);
};
static_assert(sizeof(itUsagiHatCustomizer) == 12, "Class is wrong size!");

class itWarpstarCustomizer : public itCustomizer<itWarpstarCustomizer> {
    virtual ~itWarpstarCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual bool isConstraintHave(BaseItem* item);
    virtual bool isReferenceControlerHave(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itWarpstarCustomizer) == 12, "Class is wrong size!");

class itAroarosCustomizer : public itCustomizer<itAroarosCustomizer> {
    virtual ~itAroarosCustomizer();
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itAroarosCustomizer) == 12, "Class is wrong size!");

class itCBoxCustomizer : public itCustomizer<itCBoxCustomizer> {
public:
    enum Action {
        Action_Result = 0x0,
        Action_Enable_PickUp = 0x1,
    };

    virtual ~itCBoxCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual bool onHave(BaseItem* item, int);
    virtual bool onRemoveModelConstraint(BaseItem* item, int);
    virtual bool isUseScaleZ(BaseItem* item);
    virtual bool isUseThrowRotParam(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itCBoxCustomizer) == 12, "Class is wrong size!");

class itDiddyPeanutsCustomizer : public itCustomizer<itDiddyPeanutsCustomizer> {
public:
    enum Action {
        Action_Final = 0x0,
    };

    virtual ~itDiddyPeanutsCustomizer();
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual bool isUseSpeedDamage(BaseItem* item);
};
static_assert(sizeof(itDiddyPeanutsCustomizer) == 12, "Class is wrong size!");

class itLinkBombCustomizer : public itCustomizer<itLinkBombCustomizer> {
    virtual ~itLinkBombCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
};
static_assert(sizeof(itLinkBombCustomizer) == 12, "Class is wrong size!");

class itRobotGyroCustomizer : public itCustomizer<itRobotGyroCustomizer> {
public:
    enum Action {
        Action_Set_Charge_Frame = 0x0,
    };

    virtual ~itRobotGyroCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itRobotGyroCustomizer) == 12, "Class is wrong size!");

class itWarioBikeCustomizer : public itCustomizer<itWarioBikeCustomizer> {
    virtual ~itWarioBikeCustomizer();
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual bool onRemoveModelConstraint(BaseItem* item, int);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itWarioBikeCustomizer) == 12, "Class is wrong size!");

class itGokulinCustomizer : public itCustomizer<itGokulinCustomizer> {
    virtual ~itGokulinCustomizer();
    virtual void onDestruct(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual bool onEnumFighter(BaseItem* item, Fighter* fighter);
};
static_assert(sizeof(itGokulinCustomizer) == 12, "Class is wrong size!");

class itManaphyCustomizer : public itCustomizer<itManaphyCustomizer> {
    virtual ~itManaphyCustomizer();
    virtual void onDestruct(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
};
static_assert(sizeof(itManaphyCustomizer) == 12, "Class is wrong size!");

class itSonansCustomizer : public itCustomizer<itSonansCustomizer> {
    virtual ~itSonansCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
    virtual bool onDamage(BaseItem* item, int, soDamageLog*);
    virtual bool isUseSpeedDamage(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
};
static_assert(sizeof(itSonansCustomizer) == 12, "Class is wrong size!");

class itDevilCustomizer : public itCustomizer<itDevilCustomizer> {
    virtual ~itDevilCustomizer();
    virtual void onConstruct(BaseItem* item);
    virtual void onDestruct(BaseItem* item);
    virtual void onProcessGameProc(BaseItem* item);
    virtual void onNotifyEventAnimCmd(BaseItem* item, acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(itDevilCustomizer) == 12, "Class is wrong size!");

class itJeffCustomizer : public itCustomizer<itJeffCustomizer> {
    virtual ~itJeffCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
};
static_assert(sizeof(itJeffCustomizer) == 12, "Class is wrong size!");

class itJeffPencilCustomizer : public itCustomizer<itJeffPencilCustomizer> {
    virtual ~itJeffPencilCustomizer();
    virtual bool onReflect(BaseItem* item);
};
static_assert(sizeof(itJeffPencilCustomizer) == 12, "Class is wrong size!");

class itHeririnCustomizer : public itCustomizer<itHeririnCustomizer> {
    virtual ~itHeririnCustomizer();
    virtual void onProcessUpdate(BaseItem* item);
};
static_assert(sizeof(itHeririnCustomizer) == 12, "Class is wrong size!");

class itKatanaAnaCustomizer : public itCustomizer<itKatanaAnaCustomizer> {
    virtual ~itKatanaAnaCustomizer();
    virtual bool onSearchTarget(BaseItem* item, int* taskId, Vec3f pos, int);
};
static_assert(sizeof(itKatanaAnaCustomizer) == 12, "Class is wrong size!");

class itLittlemacCustomizer : public itCustomizer<itLittlemacCustomizer> {
    virtual ~itLittlemacCustomizer();
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
};
static_assert(sizeof(itLittlemacCustomizer) == 12, "Class is wrong size!");

class itMetroidCustomizer : public itCustomizer<itMetroidCustomizer> {
    virtual ~itMetroidCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
};
static_assert(sizeof(itMetroidCustomizer) == 12, "Class is wrong size!");

class itNintendogsHiCustomizer : public itCustomizer<itNintendogsHiCustomizer> {
    virtual ~itNintendogsHiCustomizer();
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual bool onHave(BaseItem* item, int);
    virtual bool isReferenceControlerHave(BaseItem* item);
};
static_assert(sizeof(itNintendogsHiCustomizer) == 12, "Class is wrong size!");

class itResetsanCustomizer : public itCustomizer<itResetsanCustomizer> {
    virtual ~itResetsanCustomizer();
    virtual void onConstruct(BaseItem* item);
    virtual void onReset(BaseItem* item);
    virtual void onNotifyEventAnimCmd(BaseItem* item, acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
    virtual void getFighterKind(ftKind* fighterKind, char** fighterName, int*, ftKind* fighterKind2, char** fighterName2, int*);
};
static_assert(sizeof(itResetsanCustomizer) == 12, "Class is wrong size!");

class itShadowCustomizer : public itCustomizer<itShadowCustomizer> {
    virtual ~itShadowCustomizer();
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void onNotifyEventAnimCmd(BaseItem* item, acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(itShadowCustomizer) == 12, "Class is wrong size!");

class itTingleCustomizer : public itCustomizer<itTingleCustomizer> {
    virtual ~itTingleCustomizer();
    virtual void onDestruct(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual bool onEnumFighter(BaseItem* item, Fighter* fighter);
};
static_assert(sizeof(itTingleCustomizer) == 12, "Class is wrong size!");
