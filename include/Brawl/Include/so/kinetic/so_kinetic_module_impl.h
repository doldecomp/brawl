#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/so_instance_manager.h>
#include <so/event/so_event_presenter.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <so/anim/so_anim_cmd_event_presenter.h>

class soKineticModule : public soNullable {
public:
    virtual void activate();
    virtual void deactivate();
    virtual void addEnergy(soKineticEnergy* kineticEnergy, int, soKineticEnergy::AttributeFlag, short);
    virtual void eraseEnergy(int index);
    virtual void eraseEnergyAll();
    virtual soKineticEnergy* getEnergy(int index);
    virtual bool isContain(int index);
    virtual void updateEnergy(soModuleAccesser* moduleAccesser, soKineticEnergy::AttributeFlag);
    virtual void clearSpeedAll();
    virtual void suspendEnergyAll();
    virtual void resumeEnergyAll();
    virtual void unableEnergyAll();
    virtual Vec2f getSumSpeed(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumSpeed3f(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumRotation(soKineticEnergy::AttributeFlag);
    virtual void setConsiderGroundFriction(bool, soKineticEnergy::AttributeFlag);
    virtual void mulSpeed(Vec3f* speed, soKineticEnergy::AttributeFlag);
    virtual void mulAccel(Vec3f* accel, soKineticEnergy::AttributeFlag);
    virtual void reflectSpeed(Vec3f* speed, soKineticEnergy::AttributeFlag);
    virtual void reflectAccel(Vec3f* accel, soKineticEnergy::AttributeFlag);
    virtual void changeKinetic(int kineticType, soModuleAccesser* moduleAccesser);
    virtual int getKineticType();
    virtual void addSpeed(Vec3f* speed, soModuleAccesser* moduleAccesser);
    virtual void addSpeedOutside(soKineticEnergy::OutsideType, Vec3f* speed);
};
static_assert(sizeof(soKineticModule) == 8, "Class is wrong size!");

class soKineticModuleImpl : public soKineticModule, public soAnimCmdEventObserver {
    soInstanceManagerFullProperty<soKineticEnergy*>* m_kineticEnergyInstanceManager;
    int m_kineticType;
    soModuleAccesser* m_moduleAccesser;

public:

    virtual void activate();
    virtual void deactivate();
    virtual void addEnergy(soKineticEnergy* kineticEnergy, int, soKineticEnergy::AttributeFlag, short);
    virtual void eraseEnergy(int index);
    virtual void eraseEnergyAll();
    virtual soKineticEnergy* getEnergy(int index);
    virtual bool isContain(int index);
    virtual void updateEnergy(soModuleAccesser* moduleAccesser, soKineticEnergy::AttributeFlag);
    virtual void clearSpeedAll();
    virtual void suspendEnergyAll();
    virtual void resumeEnergyAll();
    virtual void unableEnergyAll();
    virtual Vec2f getSumSpeed(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumSpeed3f(soKineticEnergy::AttributeFlag);
    virtual Vec3f getSumRotation(soKineticEnergy::AttributeFlag);
    virtual void setConsiderGroundFriction(bool, soKineticEnergy::AttributeFlag);
    virtual void mulSpeed(Vec3f* speed, soKineticEnergy::AttributeFlag);
    virtual void mulAccel(Vec3f* accel, soKineticEnergy::AttributeFlag);
    virtual void reflectSpeed(Vec3f* speed, soKineticEnergy::AttributeFlag);
    virtual void reflectAccel(Vec3f* accel, soKineticEnergy::AttributeFlag);
    virtual void changeKinetic(int kineticType, soModuleAccesser* moduleAccesser);
    virtual int getKineticType();

    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual bool isObserv(char unk1);

};
static_assert(sizeof(soKineticModuleImpl) == 32, "Class is wrong size!");
