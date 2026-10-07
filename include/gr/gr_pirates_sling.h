#pragma once

#include <gr/gr_pirates.h>
#include <gr/collision/gr_collision_joint.h>
#include <mt/mt_matrix.h>
#include <snd/snd_3d_generator.h>

class grPiratesSling : public grPirates {
    enum State {
        State_Reset = 0,
        State_Wait = 1,
        State_Active = 4,
        State_Raising = 5,
        State_Lowering = 10,
    };

    Matrix* m_mtxWork;                 // 0x160
    u8* m_stateWork;                   // 0x164
    u8 m_firstActivation;              // 0x168
    u8 m_motionId;                    // 0x169
    u8 unk16A[2];
    float m_motionEndFrame;            // 0x16C
    grCollisionJoint* m_collisionJoint; // 0x170
    u8 m_yakumonoInitialized;          // 0x174
    u8 m_attackEnabled;                // 0x175
    u8 unk176[2];
    u32 unk178;
    snd3DGenerator m_sndGenerator;     // 0x17C
    s32 m_soundHandle;                 // 0x184
    u32 unk188;
    s32 m_dangerZoneId;                // 0x18C

public:
    // Derived virtual entries begin at slot 0x1D0.
    virtual void updateYakumono(float deltaFrame);
    virtual void updateJoint(float deltaFrame);
    virtual void updateCollision(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updateSE(float deltaFrame);
    virtual void updateAI(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setMotion(u32 motion, u32 loop, bool force, float* endFrame);

};
static_assert(sizeof(grPiratesSling) == 0x190, "grPiratesSling layout");
