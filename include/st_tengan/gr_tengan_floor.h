#pragma once

#include <gr/gr_yakumono.h>
#include <st_tengan/gr_tengan.h>

class grTenganFloor : public grYakumono {
protected:

public:
    Vec3f m_unused;
    u8 m_state;
    float m_stateTimer;
    float* m_frameWork;
    u8* m_stateWork;
    u8 m_type;
    u8 unk16d;
    float unk170;
    u8 m_animId;
    float m_animTimer;

    grTenganFloor(const char* taskName);
    virtual ~grTenganFloor();
    virtual void update(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updatePreBuild(float deltaFrame);
    virtual void setMotion(u8 animId, bool shouldLoop, u32 unk3, float* frameCount);
    virtual void setFrameWork(float* frameWork);
    virtual void setStateWork(u8* stateWork);
    virtual void setType(u8 type);

    //virtual void setTgtNode(char *tgtNode);
    //virtual char* getTgtNode();
    //virtual void setPosDialgaWork(Vec3f* pos);
    //virtual void setPosAshibaWork(Vec3f* pos);

    static grTenganFloor* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
