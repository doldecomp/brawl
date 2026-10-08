#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>
#include <so/so_module_accesser.h>
#include <so/damage/so_damage.h>

class soDamageUtilActor : public soNullable {
    // TODO:
public:
    static int getDamageLevel(soModuleAccesser* moduleAccesser, float reaction);
    static bool checkDamageMeteor(soModuleAccesser* moduleAccesser, int attackVector);
    static float getDamageAngle(soModuleAccesser* moduleAccesser, double reaction, double lr, int attackVector, Vec2f *speed);
    static int getDamageFlyStatus(soModuleAccesser* moduleAccesser, float reaction, float angle);
    // Callee takes three floating values, then accessor, collision attack data, and mode.
    static int calcHitStopFrame(double, double, double, soModuleAccesser*, soCollisionAttackData*, int);
    static int getDamageHitStopFrame(soModuleAccesser* moduleAccesser, soDamage* damage, bool unk, float mul);
};
