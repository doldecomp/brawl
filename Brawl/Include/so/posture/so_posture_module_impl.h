#pragma once

#include <StaticAssert.h>
#include <so/posture/so_posture_module_simple.h>
#include <so/so_array.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <types.h>

template <class T>
class soInterpolation {
    T m_elements[4];
public:
    soInterpolation() {};
    ~soInterpolation() {};
};

typedef soInterpolation<Vec3f> interpolationVec3f;

class soPostureModuleImpl : public soPostureModuleSimple, public soStatusEventObserver, public soAnimCmdEventObserver {
    soArray<soInterpolation<Vec3f> >* m_interpolationArray;
    float m_rotYLr;
    int m_syncConstraintNode;
    float m_ownerScale;
    Vec3f m_prevRoughPos;

public:
    virtual ~soPostureModuleImpl();
    virtual void init(Vec3f* pos, float lr);
    virtual void initPos(Vec3f* pos);
    virtual Vec3f getPrevRoughPos();
    virtual void setPrevRoughPos(Vec3f* roughPos);
    virtual void setLr(float lr);
    virtual void initRot();
    virtual void initRot(u32 index);
    virtual Vec3f getRot(u32 index);
    virtual void setRot(Vec3f* rot, u32 index);
    virtual void initRotYLr();
    virtual bool isRotYLrDifferentInnerLr();
    virtual float getRotYLr();
    virtual void updateRotYLr();
    virtual void reverseRotYLr();
    virtual float getScale();
    virtual float getOwnerScale();
    virtual void setOwnerScale(float ownerScale);
    virtual void begin();
    virtual void rewind();
    virtual void turnBack();
    virtual float interpolate(float);
    virtual bool setStickLR(float stickLR);
    virtual void setSyncConstraintNode(int);
    virtual void fixConstraintNodePosture(int, void*);
    virtual void fixRot();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);

    soPostureModuleImpl(soModuleAccesser*, soArray<soInterpolation<Vec3f> >*, soEventObserverRegistrationDesc*);
};
static_assert(sizeof(soPostureModuleImpl) == 120, "Class is wrong size!");

template <u32 TNumInterpolation, class TPostureModule>
class soPostureModuleBuildConfig {
public:
    soArrayVector<soInterpolation<Vec3f>,TNumInterpolation> m_interpolationArrayVector;
    TPostureModule m_postureModule;

    soPostureModuleBuildConfig(soModuleAccesser* moduleAccesser,
                               soEventObserverRegistrationDesc* registrationDesc) :
                               m_interpolationArrayVector(TNumInterpolation, 0),
                               m_postureModule(moduleAccesser, &m_interpolationArrayVector, registrationDesc) {
    }
};

template <class TPostureModuleBuildConfig>
class soPostureModuleBuilder {
    TPostureModuleBuildConfig m_buildConfig;
public:
    soPostureModule* getModule() {
        return &m_buildConfig.m_postureModule;
    }

    soPostureModuleBuilder(soModuleAccesser* moduleAccesser,
                           soEventObserverRegistrationDesc* registrationDesc) :
                           m_buildConfig(moduleAccesser, registrationDesc) {
        this->getModule()->initRot();
    };
};
