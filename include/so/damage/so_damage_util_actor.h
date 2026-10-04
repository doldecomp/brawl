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
    static double getDamageAngle(soModuleAccesser* moduleAccesser, double reaction, double lr, int attackVector, Vec2f *speed);
    static int getDamageFlyStatus(soModuleAccesser* moduleAccesser, float reaction, float angle);
    static int getDamageHitStopFrame(soModuleAccesser* moduleAccesser, soDamage* damage, bool unk, float mul);
};
