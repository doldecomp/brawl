#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>

struct grGimmickSpringData {
public:
    grGimmickMotionPathData m_motionPathData;
    stGimmickAreaData m_areaData;
    Vec2f m_pos;
    float m_rot;
    float m_bounce;
    char _64[8];
    u8 m_mdlIndex;
    u8 m_collIndex;
    char _74[2];
    stTriggerData m_triggerData;

    inline grGimmickSpringData() {

    };

    inline grGimmickSpringData(Vec2f* pos, float bounce, u8 mdlIndex, Vec2f* areaPos, Vec2f* areaRange) {
        initialize(pos, bounce, mdlIndex, areaPos, areaRange);
    };

    inline grGimmickSpringData(Vec2f* pos, float rot, float bounce, u8 mdlIndex, Vec2f* areaPos, Vec2f* areaRange) {
        initialize(pos, rot, bounce, mdlIndex, areaPos, areaRange);
    };

    inline void initialize(Vec2f* pos, float bounce, u8 mdlIndex, Vec2f* areaPos, Vec2f* areaRange) {
        MEMINIT(this);
        m_pos = *pos;
        m_bounce = bounce;
        m_mdlIndex = mdlIndex;
        m_areaData.set(areaPos, areaRange);
    };

    inline void initialize(Vec2f* pos, float rot, float bounce, u8 mdlIndex, Vec2f* areaPos, Vec2f* areaRange) {
        MEMINIT(this);
        m_pos = *pos;
        m_rot = rot;
        m_bounce = bounce;
        m_mdlIndex = mdlIndex;
        m_areaData.set(areaPos, areaRange);
    };
};
static_assert(sizeof(grGimmickSpringData) == 80, "Class is wrong size!");

class grGimmickSpring : public grYakumono {

protected:
    enum State {
        State_Rest = 0x0,
        State_On = 0x1,
        State_Off = 0x2
    };

    grGimmickSpringData* m_springData;
    int m_276;
    State m_state : 8;
    char _281[3];
    float m_animFrame;
    u32 m_animOnLength;
    u32 m_animOffLength;
    soAreaData m_areaData;
    soSet<soAreaData> m_areaDataSet;
    ykAreaData m_ykData;

public:
    grGimmickSpring(const char* taskName);
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual ~grGimmickSpring();
    virtual void setInitializeFlag();
    virtual bool setSleepArea(bool);
    virtual bool disableArea();
    virtual void setMotionOff();
    virtual void getTopNode(Vec3f* pos);

    void presentPosEvent();
    void presentShootEvent();
};
static_assert(sizeof(grGimmickSpring) == 412, "Class is wrong size!");