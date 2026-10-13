#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_shield_group.h>
#include <so/collision/so_collision_shield_event_presenter_absorber.h>
#include <so/collision/so_collision_shield_event_presenter_reflector.h>
#include <so/collision/so_collision_shield_event_presenter_shield.h>

class soCollisionShieldModule
{
public:
	virtual ~soCollisionShieldModule();
	virtual void activate(double, double, double);
	virtual void activate(double, double, double, u32 taskId);
	virtual void deactivate();
	virtual void begin();
	virtual void clean();
	virtual void add(soCollisionShieldGroupData*, u32 collisionShieldGroupIndex);
	virtual void add(soCollisionReflectorGroupData*, u32 collisionShieldGroupIndex);
	virtual void set(u32, soCollisionShieldData*, u32 collisionShieldGroupIndex);
	virtual void setReflectorData(soCollisionReflectorData*, u32 collisionShieldGroupIndex);
	virtual void update(double, double, double, u32 collisionShieldGroupIndex);
	virtual void update(double, double, double);
	virtual u8 isShield(u32, u32 collisionShieldGroupIndex);
	virtual void setStatus(u32, u32, u32);
	virtual void setStatusAll(u32, u32);
	virtual u8 isTurn(u32 collisionShieldGroupIndex);
	virtual u8 isFront(u32 collisionShieldGroupIndex);
	virtual u8 isHop(u32 collisionShieldGroupIndex);
	virtual double getHopAngle();
	virtual void isNoHop(u32 collisionShieldGroupIndex);
	virtual void setTurn(u32, u32 collisionShieldGroupIndex);
	virtual void setFront(u32, u32 collisionShieldGroupIndex);
	virtual void setHop(double, u32, u32 collisionShieldGroupIndex);
	virtual double getAttackMul(u32 collisionShieldGroupIndex);
	virtual double getSpeedMul(u32 collisionShieldGroupIndex);
	virtual double getLifeMul(u32 collisionShieldGroupIndex);
	virtual void getAttackLimit(u32 collisionShieldGroupIndex);
	virtual u8 isNoMBall(u32 collisionShieldGroupIndex);
	virtual int getPartSize(u32 collisionShieldGroupIndex);
	virtual u32 getTeam();
	virtual void checkLog();
	virtual void check();
	virtual void renderDebug();
	virtual void clearAll();
	virtual void clearAll(u32 collisionShieldGroupIndex);
	virtual Vec3f getCenterPos(u32, u32 collisionShieldGroupIndex);
	virtual double getLR(u32 collisionShieldGroupIndex);
	virtual u32 getGroupNum();
	virtual double getPosX(u32 collisionShieldGroupIndex);
	virtual void setTargetProperty(u32, u32 collisionShieldGroupIndex);
};

class soCollisionShieldModuleImpl : public soCollisionShieldModule, public soStatusEventObserver, public soAnimCmdEventObserver
{
public:
	soModuleAccesser* m_moduleAccesser;
	u32 _20;
	u32 _24;
	soCollision m_collision;
	u8 _40[0x8];
	soArray<soCollisionShieldGroup>* m_collisionShieldGroupArray;
	u32 _4C;
	u8 _50;
	u8 m_collisionOccurred;
	u8 _52;
	u8 _53_padding;

	virtual ~soCollisionShieldModuleImpl();
	virtual void activate(double, double, double);
	virtual void activate(double, double, double, u32 taskId);
	virtual void deactivate();
	virtual void begin();
	virtual void clean();
	virtual void add(soCollisionShieldGroupData*, u32 collisionShieldGroupIndex);
	virtual void add(soCollisionReflectorGroupData*, u32 collisionShieldGroupIndex);
	virtual void set(u32, soCollisionShieldData*, u32 collisionShieldGroupIndex);
	virtual void setReflectorData(soCollisionReflectorData*, u32 collisionShieldGroupIndex);
	virtual void update(double, double, double, u32 collisionShieldGroupIndex);
	virtual void update(double, double, double);
	virtual u8 isShield(u32, u32 collisionShieldGroupIndex);
	virtual void setStatus(u32, u32 status, u32 collisionShieldGroupIndex);
	virtual void setStatusAll(u32 status, u32 collisionShieldGroupIndex);
	virtual u8 isTurn(u32 collisionShieldGroupIndex);
	virtual u8 isFront(u32 collisionShieldGroupIndex);
	virtual u8 isHop(u32 collisionShieldGroupIndex);
	virtual double getHopAngle();
	virtual void isNoHop(u32 collisionShieldGroupIndex);
	virtual void setTurn(u32, u32 collisionShieldGroupIndex);
	virtual void setFront(u32, u32 collisionShieldGroupIndex);
	virtual void setHop(double, u32, u32 collisionShieldGroupIndex);
	virtual double getAttackMul(u32 collisionShieldGroupIndex);
	virtual double getSpeedMul(u32 collisionShieldGroupIndex);
	virtual double getLifeMul(u32 collisionShieldGroupIndex);
	virtual void getAttackLimit(u32 collisionShieldGroupIndex);
	virtual u8 isNoMBall(u32 collisionShieldGroupIndex);
	virtual int getPartSize(u32 collisionShieldGroupIndex);
	virtual u32 getTeam();
	virtual void checkLog();
	virtual void check();
	virtual void renderDebug();
	virtual void clearAll();
	virtual void clearAll(u32 collisionShieldGroupIndex);
	virtual Vec3f getCenterPos(u32, u32 collisionShieldGroupIndex);
	virtual double getLR(u32 collisionShieldGroupIndex);
	virtual u32 getGroupNum();
	virtual double getPosX(u32 collisionShieldGroupIndex);
	virtual void setTargetProperty(u32, u32 collisionShieldGroupIndex);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soCollisionShieldModuleImpl) == 0x54, "Class is wrong size!");
