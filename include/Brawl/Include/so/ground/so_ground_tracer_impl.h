#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/posture/so_posture_module_simple.h>
#include <so/so_null.h>
#include <types.h>

class soGroundModule;

class soGroundTracer : public soNullable {
public:
    virtual ~soGroundTracer();
    virtual bool isTraced();
    virtual bool canStart(u32, u8, soGroundModule* groundModule, u32 index, float);
    virtual bool start(u32, u8, soPostureModule* postureModule, soGroundModule* groundModule, u32 index, u8, float, float, float);
    virtual Vec2f getTraceTargetVec(soGroundModule* groundModule, u32 index, float);
    virtual Vec2f getTraceTargetPosturePos(soGroundModule* groundModule, u32 index, float);
    virtual bool isArrived(soPostureModule* postureModule, soGroundModule* groundModule, u32 index, float);
    virtual bool canIntercept(u32, u8, soGroundModule* groundModule, u32 index, float);
    virtual bool renew(u32, u8, soPostureModule* postureModule, soGroundModule* groundModule, u32 index, float, float);
    virtual void end();
    virtual void update(bool, soGroundModule* groundModule, u32 index);
    virtual Vec2f getGroundMovementSpeed();
    virtual Vec2f getDistanceFromCurrentLine(soGroundModule* groundModule, u32 index, bool);
    virtual Vec2f getVecFromCurrentLine(soGroundModule* groundModule, u32 index);
    virtual bool isSameNormalTraceLineCurrentAndNext(soGroundModule* groundModule, u32);
    virtual bool isOpenTraceLineCurrentAndNext(soGroundModule* groundModule, u32);
    virtual bool isTouchCurrentLine(soGroundModule* groundModule, u32 index);
};

class soGroundTracerImpl : public soGroundTracer {
    char _4[12];
    Vec2f m_20;
    Vec2f m_groundMovementSpeed;
    bool m_isTraced;
    char _pad[3];

public:
    virtual ~soGroundTracerImpl();
    virtual bool isTraced();
    virtual bool canStart(u32, u8, soGroundModule* groundModule, u32 index, float);
    virtual bool start(u32, u8, soPostureModule* postureModule, soGroundModule* groundModule, u32 index, u8, float, float, float);
    virtual Vec2f getTraceTargetVec(soGroundModule* groundModule, u32 index, float);
    virtual Vec2f getTraceTargetPosturePos(soGroundModule* groundModule, u32 index, float);
    virtual bool isArrived(soPostureModule* postureModule, soGroundModule* groundModule, u32 index, float);
    virtual bool canIntercept(u32, u8, soGroundModule* groundModule, u32 index, float);
    virtual bool renew(u32, u8, soPostureModule* postureModule, soGroundModule* groundModule, u32 index, float, float);
    virtual void end();
    virtual void update(bool, soGroundModule* groundModule, u32 index);
    virtual Vec2f getGroundMovementSpeed();
    virtual Vec2f getDistanceFromCurrentLine(soGroundModule* groundModule, u32 index, bool);
    virtual Vec2f getVecFromCurrentLine(soGroundModule* groundModule, u32 index);
    virtual bool isSameNormalTraceLineCurrentAndNext(soGroundModule* groundModule, u32);
    virtual bool isOpenTraceLineCurrentAndNext(soGroundModule* groundModule, u32);
    virtual bool isTouchCurrentLine(soGroundModule* groundModule, u32 index);
};
static_assert(sizeof(soGroundTracerImpl) == 40, "Class is wrong size!");