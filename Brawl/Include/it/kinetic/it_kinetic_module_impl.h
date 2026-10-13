#pragma once

#include <StaticAssert.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/so_module_accesser.h>
#include <types.h>

class itKineticModuleImpl : public soKineticModuleImpl, public soStatusEventObserver, public soAnimCmdEventObserver {
    char _0x38[4];
    itParam::KineticFlag m_kineticFlag;
    char _0x40[0x2EC];

public:
    virtual void activate();
    virtual void updateEnergy(soModuleAccesser* moduleAccesser, soKineticEnergy::AttributeFlag);
    virtual Vec2f getSumSpeed(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumSpeed3f(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumRotation(soKineticEnergy::AttributeFlag);
    virtual void mulSpeed(Vec3f* speed, soKineticEnergy::AttributeFlag);
    virtual void changeKinetic(int kineticType, soModuleAccesser* moduleAccesser);
    virtual void addSpeed(soKineticEnergy::AttributeFlag attr, soModuleAccesser* moduleAccesser);
    virtual void addSpeedOutside(soKineticEnergy::OutsideType, Vec3f* speed);

    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual bool isObserv(char unk1);

    virtual void onDebugRender(Vec2f*, Vec2f*);
    virtual void onProcessMapCorrection(soModuleAccesser* moduleAccesser);
    virtual void addRotation(Vec3f* rot, soModuleAccesser* moduleAccesser);
    virtual void clearRotation();
    virtual void addSpeed(Vec3f* speed, bool, soModuleAccesser* moduleAccesser);
    virtual void clearSpeed(bool);
    virtual void addSpeedDamage(Vec3f*, soModuleAccesser* moduleAccesser);
    virtual void setThrowParam(Vec3f* speed, Vec3f* rot, soModuleAccesser* moduleAccesser, bool);
    virtual void characterBound(soModuleAccesser* moduleAccesser, bool);
    virtual void setSlopeType(itParam::SlopeType);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
};