#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>
#include <so/so_module_accesser.h>

class soDamageUtilActor : public soNullable {
    // TODO:
public:
    static double getDamageAngle(soModuleAccesser* moduleAccesser, double reaction, double lr, int attackVector, Vec2f *speed);
};