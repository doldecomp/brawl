#pragma once

#include <gr/gr_yakumono.h>
#include <mt/mt_matrix.h>
#include <st/se_util.h>

// Mute City (F-Zero) stage gimmicks. Every gimmick derives from grFzero, a thin grYakumono that carries a state byte
// and a timer, and receives pointers into the stage object (stFzero) through virtual setters right after it is created:
// the scene state (which part of the course sequence is running), the scene frame, per-gimmick state bytes and matrices.
class grFzero : public grYakumono {
protected:
    u8 m_state;    // 0x150
    float m_timer; // 0x154

public:
#ifdef GR_FZERO_BASE_EXTERNAL
    // MATCH-ONLY: units whose constructors call the base out of line (the weak copies live in the first unit).
    grFzero(const char* taskName);
    virtual ~grFzero();
#else
    // Defined inline: the derived constructors expand it, like every other gimmick base of the stage.
    grFzero(const char* taskName) : grYakumono(taskName) {
        m_state = 0;
        m_timer = 0.0f;
        setupMelee();
    }
    virtual ~grFzero() { }
#endif
};
static_assert(sizeof(grFzero) == 0x158, "grFzero layout");

// Carries the Pokemon Trainer's position along the course (HYPOTHESIS name: the node names are "PTposition01".."04"
// and the stage reserves four trainer positions for the Pokemon Trainer fighter).
class grFzeroTrainer : public grFzero {
    u8* m_sceneWork;            // 0x158 course section the stage is in (0..6)
    float* m_frameSceneWork;    // 0x15C frame counter of that section
    Matrix* m_mtxWork;          // 0x160 stage matrix table; unk164 selects the entry the callback follows
    u8 m_mtxIndex;              // 0x164
    Vec3f* m_posTrainerWork;    // 0x168 four positions published to the stage every frame
    u32 m_node[4];              // 0x16C nodes "PTposition01".."04"
    u8 m_animId;                // 0x17C current animation (7 = none)
    float m_animFrames;         // 0x180 frame count of the current animation

public:
    grFzeroTrainer(const char* taskName);
    virtual ~grFzeroTrainer();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    static grFzeroTrainer* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updatePos(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
    virtual void setMtxWork(Matrix* mtxWork) { m_mtxWork = mtxWork; }
    virtual void setPosTrainerWork(Vec3f* posTrainerWork) { m_posTrainerWork = posTrainerWork; }
};
static_assert(sizeof(grFzeroTrainer) == 0x184, "grFzeroTrainer layout");

// Per-stage parameters of the warning gimmick (read through getStageData()).
struct grFzeroWarningParam {
    float unk00;
    float m_warnFrames; // 0x04 how long the warning lasts
};

// The warning light/sign of the course (HYPOTHESIS name): it plays a short sequence of animations and sound effects
// when the stage announces the cars (scene section 4).
class grFzeroWarning : public grFzero {
    u8* m_sceneWork;               // 0x158
    float* m_frameSceneWork;       // 0x15C
    u8* m_stateWork;               // 0x160
    Matrix* m_mtxGimmickWork;      // 0x164
    u8 m_warned;                   // 0x168
    u8 m_animId;                   // 0x169 current animation (3 = none)
    float m_lastFrame;             // 0x16C
    float m_animFrames;            // 0x170
    StSeUtil::SeSeqInstance<1, 1> m_sePlayer; // 0x174
    SndID m_seIds[1];              // 0x1B0
    StSeUtil::UnkStruct m_seData;  // 0x1B4

public:
    grFzeroWarning(const char* taskName);
    virtual ~grFzeroWarning();
    virtual void update(float deltaFrame);
    static grFzeroWarning* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setMtxGimmickWork(Matrix* mtxGimmickWork) { m_mtxGimmickWork = mtxGimmickWork; }
};
static_assert(sizeof(grFzeroWarning) == 0x1C4, "grFzeroWarning layout");

// The start/finish line of the course (HYPOTHESIS name). It hides itself while the scene is in section 1 and follows
// a stage matrix.
class grFzeroStartLine : public grFzero {
    u8* m_sceneWork;     // 0x158
    Matrix* m_mtxWork;   // 0x15C

public:
    grFzeroStartLine(const char* taskName);
    virtual ~grFzeroStartLine();
    virtual void update(float deltaFrame);
    static grFzeroStartLine* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateCallBack(float deltaFrame);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setMtxWork(Matrix* mtxWork) { m_mtxWork = mtxWork; }
};
static_assert(sizeof(grFzeroStartLine) == 0x160, "grFzeroStartLine layout");

// The ring on the plate (HYPOTHESIS name): same shape as the start line, but it never hides.
class grFzeroPlateRing : public grFzero {
    u8* m_sceneWork;     // 0x158
    Matrix* m_mtxWork;   // 0x15C

public:
    grFzeroPlateRing(const char* taskName);
    virtual ~grFzeroPlateRing();
    virtual void update(float deltaFrame);
    static grFzeroPlateRing* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateCallBack(float deltaFrame);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setMtxWork(Matrix* mtxWork) { m_mtxWork = mtxWork; }
};
static_assert(sizeof(grFzeroPlateRing) == 0x160, "grFzeroPlateRing layout");
