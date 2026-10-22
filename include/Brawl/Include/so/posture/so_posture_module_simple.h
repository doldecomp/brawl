#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/so_null.h>
#include <types.h>

class soModuleAccesser;

class soPostureModule : public soNullable {
public:
    virtual ~soPostureModule();
    virtual void init(Vec3f* pos, float lr);
    virtual void initPos(Vec3f* pos);
    virtual Vec3f getPos();
    virtual void setPos(Vec3f* pos);
    virtual Vec3f getPrevPos();
    virtual Vec3f getPrevRoughPos();
    virtual void setPrevRoughPos(Vec3f* roughPos);
    virtual float getLr();
    virtual void setLr(float lr);
    virtual void reverseLr();
    virtual void initRot();
    virtual void initRot(u32 index);
    virtual Vec3f getRot(u32 index);
    virtual void setRot(Vec3f* rot, u32 index);
    virtual void initRotYLr();
    virtual bool isRotYLrDifferentInnerLr();
    virtual float getRotYLr();
    virtual void updateRotYLr();
    virtual void reverseRotYLr();
    virtual float getBaseScale();
    virtual float getScale();
    virtual void setScale(float scale);
    virtual void initScale();
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
};

class soPostureModuleSimple : public soPostureModule {

    soModuleAccesser* m_moduleAccesser;
    Vec3f m_pos;
    Vec3f m_prevPos;
    Vec3f _36;
    char _48[12];
    float m_baseScale;
    float m_lr;

public:
    virtual ~soPostureModuleSimple();
    virtual void init(Vec3f* pos, float lr);
    virtual void initPos(Vec3f* pos);
    virtual Vec3f getPos();
    virtual void setPos(Vec3f* pos);
    virtual Vec3f getPrevPos();
    virtual Vec3f getPrevRoughPos();
    virtual void setPrevRoughPos(Vec3f* roughPos);
    virtual float getLr();
    virtual void setLr(float lr);
    virtual void reverseLr();
    virtual void initRot();
    virtual void initRot(u32 index);
    virtual Vec3f getRot(u32 index);
    virtual void setRot(Vec3f* rot, u32 index);
    virtual void initRotYLr();
    virtual bool isRotYLrDifferentInnerLr();
    virtual float getRotYLr();
    virtual void updateRotYLr();
    virtual void reverseRotYLr();
    virtual float getBaseScale();
    virtual float getScale();
    virtual void setScale(float scale);
    virtual void initScale();
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
};
static_assert(sizeof(soPostureModuleSimple) == 68, "Class is wrong size!");