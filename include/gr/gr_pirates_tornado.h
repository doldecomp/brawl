#pragma once
#include <gr/gr_pirates.h>
#include <snd/snd_3d_generator.h>

class grPiratesTornado : public grPirates {
protected:
    u8 m_ctrlFrameAdvanced;
    u8 m_motionPhase;
    u8 unk162[2];
    void* unk164;
    u8* m_stateWork;
    u8 m_previousShipState;
    u8 m_motionId;
    u8 unk16E[2];
    float m_motionTimer;
    u8 m_reducedGravity;
    u8 unk175[3];
    snd3DGenerator m_soundGenerator;
    u32 unk180;
    u8 unk184;
    u8 unk185[3];
public:
    virtual ~grPiratesTornado();
    virtual void update(float deltaFrame);
    virtual void updateMotion(float deltaFrame);
    virtual void updateSE(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 motion, u32 loop, bool force, float* endFrame);
};
static_assert(sizeof(grPiratesTornado) == 0x188, "grPiratesTornado layout");
