#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/so_enable.h>
#include <mt/mt_vector.h>
#include <types.h>

class soModuleAccesser;

class soAreaEnviromentElementChecker : public soNull, public soNullable {
public:
    virtual ~soAreaEnviromentElementChecker();
    virtual void check(soModuleAccesser*);
    virtual void clearWaterInfo();
    virtual void clear();
    virtual void enable();
    virtual void unable();
    virtual bool isEnable();
    virtual bool isWater();
    virtual bool isWaterAreaIndex(int);
    virtual int getWaterAreaId();
    virtual float getWaterSurfaceY();
    virtual u32 getOnMovementGroundArea();
    virtual bool testWater(Vec2f*, int*);
};
static_assert(sizeof(soAreaEnviromentElementChecker) == 0xC, "Class is wrong size!");

class soAreaEnviromentElementCheckerImpl : public soAreaEnviromentElementChecker, public soEnable {
    char _0xd[15];
public:
    virtual ~soAreaEnviromentElementCheckerImpl();
    virtual void check(soModuleAccesser*);
    virtual void clearWaterInfo();
    virtual void clear();
    virtual void enable();
    virtual void unable();
    virtual bool isEnable();
    virtual bool isWater();
    virtual bool isWaterAreaIndex(int);
    virtual int getWaterAreaId();
    virtual float getWaterSurfaceY();
    virtual u32 getOnMovementGroundArea();
    virtual bool testWater(Vec2f*, int*);
};
static_assert(sizeof(soAreaEnviromentElementCheckerImpl) == 0x1C, "Class is wrong size!");

typedef soAreaEnviromentElementChecker soAreaEnvironmentElementChecker;
typedef soAreaEnviromentElementCheckerImpl soAreaEnvironmentElementCheckerImpl;
