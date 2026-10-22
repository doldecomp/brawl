#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/collision/so_collision_log.h>
#include <so/damage/so_damage.h>
#include <so/damage/so_damage_attacker_info.h>
#include <yk/yakumono.h>

class grYakumono : public grGimmick {

protected:
    Yakumono* m_yakumono;

public:
    grYakumono(const char* taskName);
    virtual void processUpdate();
    virtual void startup(gfArchive* data, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void setValid(u32 unk1);
    virtual void setValidAttachedEffect(u32 unk1);
    virtual void preExit();
    virtual void setTransparency(u32 unk1, u32 unk2);
    virtual ~grYakumono();

    virtual void onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo);
    virtual void onInflict(soCollisionLog* collisionLog, u32 unk2, float power);
    virtual void onInflictEach(soCollisionLog* collisionLog, float power);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual bool enableYakumono(u32 unk1);
    virtual bool disableYakumono(u32 unk1, u32 unk2);
    virtual bool enableHit(u32 unk1, u32 unk2);
    virtual bool disableHit(u32 unk1, u32 unk2);
    virtual bool disableAttack(u32 unk1);
    virtual bool enableArea();
    virtual bool disableArea();
    virtual bool setSleepArea(bool unk1);
    virtual bool setTeamYakumonoOwnerId(u32 teamOwnerId);
    virtual bool setTeamYakumono(u32 teamId, u32 teamOwnerId);
    virtual bool getTeamYakumono(int* team);
    virtual bool setOffsetAttack(Vec3f* offsetPos, int index);
    virtual void setAreaGimmick(soAreaData* areaData, soSet<soAreaData>* areaInit, ykAreaData* data, bool unk4);
    virtual void setAttackGimmick(int index, int groupIndex, u32 nodeIndex, AttackData* grAttackData,
                                  AttackDetails* grAttackDetails);
    virtual void setSoCollisionAttackData(soCollisionAttackData* attackData, AttackData* grAttackData,
                                          AttackDetails* grAttackDetails);
    virtual void setAttackGimmickDetails(soCollisionAttackData* attackData, float size, float tripRate,
                                         float hitstopMultiplier, float sdiMultiplier, int power, Vec3f* offsetPos,
                                         int vector, int reactionEffect, int reactionFix, int reactionAdd,
                                         u32 nodeIndex, soCollision::CategoryMask collisionCategoryMask, soCollision::SituationMask collisionSituationMask,
                                         bool unk1, soCollision::PartMask collisionPartMask, soCollisionAttackData::Attribute attribute,
                                         soCollisionAttackData::SoundLevel soundLevel, soCollisionAttackData::SoundAttribute soundAttr,
                                         bool isClankable, bool unk2, bool unk3, bool isShieldable, bool isReflectable,
                                         bool isAbsorbable, u32 addedShieldDamage, u32 detectionRate, bool unk5, bool ignoreInvincibility,
                                         bool ignoreIntangibility, soCollisionAttackData::LrCheck lrCheck,
                                         bool unk6, bool unk7, bool disableHitstop, bool disableHitGfx,
                                         bool disableFlinch, soCollisionAttackData::Region region, bool isShapeCapsule);
    virtual bool isEnableAttackPersonAttacked(u32 unk1, u32 unk2, u32 unk3);
    virtual bool isEnableAttackAttribute(u32 unk1, u32 unk2);

    void clearAttackerInfo();
    int getPlayerNumber(int* unk1);
    int getPlayerNumber(grCollStatus* collStatus);
    bool isSubFighter(int* unk1);
    void setAreaShape(int unk1, float* unk2, float* unk3);
    void setAttackSize(int index, int unk2, float size);
    void setAttackTargetCategory(int index, soCollision::CategoryMask categoryMask);
    void setSleepAttack(bool isSleep);
    void setSleepHit(bool isSleep);
    void setSituationODD();
};
static_assert(sizeof(grYakumono) == 0x150, "Class is wrong size!");