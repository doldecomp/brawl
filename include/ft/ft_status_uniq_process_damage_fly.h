#pragma once

#include <StaticAssert.h>
#include <ft/ft_status_uniq_process_damage.h>
#include <so/collision/so_collision_log.h>
#include <types.h>

// Knockback (launch/tumble) variant of the hitstun status process.
class ftStatusUniqProcessDamageFly : public ftStatusUniqProcessDamage {
public:
    ftStatusUniqProcessDamageFly() { }
    virtual ~ftStatusUniqProcessDamageFly() { }
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind);
    virtual void execFixPosCounter(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void checkAttack(soModuleAccesser* moduleAccesser, void* collisionLog, float unk);

    virtual void initNormalDamage(soModuleAccesser* moduleAccesser);
    virtual void execNormalDamage(soModuleAccesser* moduleAccesser);
    virtual void initNormalDamageCommon(soModuleAccesser* moduleAccesser);
    virtual void execNormalDamageCommon(soModuleAccesser* moduleAccesser);

    void setDamageCamera(soModuleAccesser* moduleAccesser);
    void correctDamageVector(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(ftStatusUniqProcessDamageFly) == 4, "Class is wrong size!");

extern ftStatusUniqProcessDamageFly g_ftStatusUniqProcessDamageFly;
