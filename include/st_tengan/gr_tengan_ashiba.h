#pragma once

#include <gr/gr_yakumono.h>
#include <st_tengan/gr_tengan.h>

class grTenganAshiba : public grTengan {
protected:
    u8 m_ashibaState;
    float m_ashibaTimer;
    Vec3f *m_posLimitWork;
    Vec3f m_ashibaPos;
    float m_ashibaPosY;
    float m_speed;
    bool m_isMovingUp;
    u8 unk1F1;

public:
    grTenganAshiba(const char* taskName);
    virtual ~grTenganAshiba();
    virtual void update(float deltaFrame);
    virtual void updateMove(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);

    //virtual void setTgtNode(char *tgtNode);
    //virtual char* getTgtNode();
    virtual void setPosLimitWork(Vec3f* pos);

    static grTenganAshiba* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
