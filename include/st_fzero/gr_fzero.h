#pragma once

#include <gr/gr_yakumono.h>
#include <mt/mt_matrix.h>
#include <st/se_util.h>
#include <gr/collision/gr_collision_joint.h>

// Mute City (F-Zero) stage gimmicks. Every gimmick derives from grFzero, a thin grYakumono that carries a state byte
// and a timer, and receives pointers into the stage object (stFzero) through virtual setters right after it is created:
// the scene state (which part of the course sequence is running), the scene frame, per-gimmick state bytes and matrices.
class grFzero : public grYakumono {
protected:
    u8 m_state;    // 0x150
    float m_timer; // 0x154

public:
    grFzero(const char* taskName);
    virtual ~grFzero();
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
    u8* m_stateWork;               // 0x158 stage state byte (4 = the cars are about to appear)
    u8* m_sceneWork;               // 0x15C
    float* m_frameSceneWork;       // 0x160
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
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
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

// The floating platforms along the course (Ashiba = scaffold). m_scene says which course section the platform belongs
// to; scene 7 is the platform that sinks out of and rises back into the course (the "idou" = moving variant, which also
// owns a collision joint), the others appear when their section starts and disappear when it ends.
class grFzeroAshiba : public grFzero {
    u8* m_sceneWork;       // 0x158 course section the stage is in
    u8 m_scene;            // 0x15C section this platform belongs to (7 = the moving platform)
    u8* m_stateWork;       // 0x160 platform progress shared with the stage
    u8* m_stateNodeWork;   // 0x164
    Matrix* m_mtxWork;     // 0x168 stage matrix the platform is placed with
    float m_offsetX;       // 0x16C offset applied to the matrix
    float m_offsetY;       // 0x170
    float m_offsetZ;       // 0x174
    grCollisionJoint* m_joint; // 0x178 collision joint of the moving platform
    u8 m_animId;           // 0x17C current animation (2 = none)
    float m_timer2;        // 0x180 second timer (animation length / sink time)

public:
    grFzeroAshiba(const char* taskName);
    virtual ~grFzeroAshiba();
    virtual void update(float deltaFrame);
    static grFzeroAshiba* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void updateActiveIdou(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setScene(u8 scene) { m_scene = scene; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setStateNodeWork(u8* stateNodeWork) { m_stateNodeWork = stateNodeWork; }
    virtual void setMtxWork(Matrix* mtxWork) { m_mtxWork = mtxWork; }
};
static_assert(sizeof(grFzeroAshiba) == 0x184, "grFzeroAshiba layout");

// Per-car data the stage keeps for each of the 30 cars (stFzero::m_carData).
struct stFzeroCarData {
    Matrix* m_mtx;   // 0x00 matrix the car follows (NULL = the car is not on the course)
    Vec3f m_pos;     // 0x04 position of the car last frame
    u8 m_state;      // 0x10 progress of the car (8 = idle)
    u8 m_type;       // 0x11 which kind of car it is (0..3)
};
static_assert(sizeof(stFzeroCarData) == 0x14, "stFzeroCarData layout");

// The course background (Mute City): the big backdrop model, the course sections that slide in and out, and the
// platform ("asiba") and dash plate ("Dplate") nodes whose collision it switches. The course section animations are
// numbered like the stage's own scene (0..6); the sound effects of a section are triggered by the animation frame.
struct grFzeroBgData {
    u8 unk0[8];
    float m_chance;   // 0x08 probability the section animation is not replayed
    u8 unkC[8];
    float m_minWait;  // 0x14 shortest wait before the next section is started
    float m_maxWait;  // 0x18 longest wait
};

class grFzeroBg : public grFzero {
    u8 m_phase;                       // 0x158 progress of the current section's animation (0..7)
    u8 m_count;                       // 0x159 how many times the section animation has been replayed
    u8* m_sceneWork;                  // 0x15C
    float* m_frameSceneWork;          // 0x160
    u8* m_stateWork;                  // 0x164
    u8* m_carMotionWork;              // 0x168
    bool m_unk16C;                    // 0x16C HYPOTHESIS: the section animation is running
    bool m_unk16D;                    // 0x16D
    Matrix* m_mtxGimmickWork;         // 0x170 25 matrices, one per node below
    u32 m_nodeHaikei[2];              // 0x174 "haikei_A_rotate", "haikei_A_trans"
    u32 m_nodeAsiba[7];               // 0x17C "L_asiba01".."L_asiba07"
    u32 m_nodeDplate[11];             // 0x198 "L_Dplate_a".."L_Dplate_k"
    u32 m_nodeDplateRing;             // 0x1C4 "Dplate_e_ring"
    u32 m_nodeCourseStart;            // 0x1C8
    u32 m_nodeCourseCol[2];           // 0x1CC "courseColN01", "courseColN02"
    grCollisionJoint* m_joint[7];     // 0x1D4
    float m_motionRate;               // 0x1F0
    u8 m_animId;                      // 0x1F4 current animation (7 = none)
    float m_unk1F8;                   // 0x1F8
    float m_frameLimit;               // 0x1FC frame the current animation ends at
    u8 m_seIndex;                     // 0x200 next sound effect of the section
    int m_seHandle;                   // 0x204
    bool m_isEvent;                   // 0x208 HYPOTHESIS: event match (the test stFzero::isEventEnd relies on)

public:
    grFzeroBg(const char* taskName);
    virtual ~grFzeroBg();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    virtual void setMotionFrame(float frame, u32 sceneModelIndex);
    virtual float getMotionFrame(u32 sceneModelIndex);
    static grFzeroBg* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateJoint(float deltaFrame);
    virtual void updateScene(float deltaFrame);
    virtual void updateSceneMotion(float deltaFrame);
    virtual void updateSE(float deltaFrame);
    virtual void playSECoursePass();
    virtual void playSEMarkPass();
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual float getMotionTotalFrame(u32 sceneModelIndex);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setMtxGimmickWork(Matrix* mtxGimmickWork) { m_mtxGimmickWork = mtxGimmickWork; }
    virtual void setCarMotionWork(u8* carMotionWork) { m_carMotionWork = carMotionWork; }
};
static_assert(sizeof(grFzeroBg) == 0x20C, "grFzeroBg layout");

// A wall of the course that turns into collision for the cars (HYPOTHESIS).
class grFzeroWall : public grFzero {
    u8* m_sceneWork;           // 0x158
    u8* m_stateWork;           // 0x15C
    u8* m_stateWallWork;       // 0x160
    Matrix* m_mtxGimmickWork;  // 0x164
    u8 m_animId;               // 0x168 current animation (1 = none)
    float m_animFrames;        // 0x16C frame count of the current animation

public:
    grFzeroWall(const char* taskName);
    virtual ~grFzeroWall();
    virtual void update(float deltaFrame);
    static grFzeroWall* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setStateWallWork(u8* stateWallWork) { m_stateWallWork = stateWallWork; }
    virtual void setMtxGimmickWork(Matrix* mtxGimmickWork) { m_mtxGimmickWork = mtxGimmickWork; }
};
static_assert(sizeof(grFzeroWall) == 0x170, "grFzeroWall layout");

// 8 bytes of work memory the attack allocates for its hit setup (HYPOTHESIS: filled in by the module builder).
struct grFzeroAttackWork {
    u32 unk0;
    u32 unk4;
};

// The hazards that hit fighters (the cars' attack floor and wall).
class grFzeroAttack : public grFzero {
    u8* m_stateWork;           // 0x158
    u8* m_stateWallWork;       // 0x15C
    u8* m_sceneWork;           // 0x160
    float* m_frameSceneWork;   // 0x164
    Matrix* m_mtxGimmickWork;  // 0x168 the stage matrix table (entries 22/23 are the floor, 39 the wall)
    float* m_posLimitWork;     // 0x16C the stage's lower limit (the y of the upper limit is read from it)
    Vec3f m_pos;               // 0x170 position of the hit area, published to the calc-world callback
    Vec3f m_rot;               // 0x17C rotation of the hit area
    u8 m_type;                 // 0x188 4/5 = the two floors, 6 = the wall
    u8 m_hasYakumono;          // 0x189
    u8 m_attackEnabled;        // 0x18A
    grFzeroAttackWork* m_work; // 0x18C

public:
    grFzeroAttack(const char* taskName);
    virtual ~grFzeroAttack();
    virtual void update(float deltaFrame);
    static grFzeroAttack* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateYakumonoFloor(float deltaFrame);
    virtual void updateYakumonoWall(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setAttackFloor();
    virtual void setAttackWall();
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setStateWallWork(u8* stateWallWork) { m_stateWallWork = stateWallWork; }
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
    virtual void setMtxGimmickWork(Matrix* mtxGimmickWork) { m_mtxGimmickWork = mtxGimmickWork; }
    virtual void setPosLimitWork(float* posLimitWork) { m_posLimitWork = posLimitWork; }
    virtual void setType(u8 type) { m_type = type; }
};
static_assert(sizeof(grFzeroAttack) == 0x190, "grFzeroAttack layout");

// The machine (race track) node: the models of the 15 machines parked beside the course ("FZmachine01".."FZmachine15")
// which change animation with the course section (HYPOTHESIS name for most fields).
class grFzeroNode : public grFzero {
    u8* m_sceneWork;           // 0x158
    float* m_frameSceneWork;   // 0x15C
    float m_motionTimer;       // 0x160 frames since the current animation was started
    u8* m_stateWork;           // 0x164
    u8* m_motionWork;          // 0x168 published copy of the current animation
    u8 m_motionId;             // 0x16C
    Matrix* m_mtxWork;         // 0x170
    Matrix* m_mtxGimmickWork;  // 0x174
    u32 m_node[15];            // 0x178 "FZmachine01".."FZmachine15"
    u8 m_animId;               // 0x1B4 current animation (5 = none)
    float m_animFrames;        // 0x1B8 frame count of the current animation
    u8 unk1BC[5];

public:
    grFzeroNode(const char* taskName);
    virtual ~grFzeroNode();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    static grFzeroNode* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setFrameSceneWork(float* frameSceneWork) { m_frameSceneWork = frameSceneWork; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setMtxWork(Matrix* mtxWork) { m_mtxWork = mtxWork; }
    virtual void setMtxGimmickWork(Matrix* mtxGimmickWork) { m_mtxGimmickWork = mtxGimmickWork; }
    virtual void setMotionWork(u8* motionWork) { m_motionWork = motionWork; }
};
static_assert(sizeof(grFzeroNode) == 0x1C4, "grFzeroNode layout");

// One of the 30 racing machines (cars) that drive past.
class grFzeroCar : public grFzero {
    u8* m_sceneWork;           // 0x158
    u8* m_stateWork;           // 0x15C
    stFzeroCarData* m_carData; // 0x160
    u8 unk164[0x184 - 0x164];

public:
    grFzeroCar(const char* taskName);
    virtual ~grFzeroCar();
    virtual void update(float deltaFrame);
    static grFzeroCar* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setMotionCommon(u32 animId, bool loop, bool force, float* frameCount);
    virtual void setSceneWork(u8* sceneWork) { m_sceneWork = sceneWork; }
    virtual void setStateWork(u8* stateWork) { m_stateWork = stateWork; }
    virtual void setCarData(stFzeroCarData* carData) { m_carData = carData; }
};
static_assert(sizeof(grFzeroCar) == 0x184, "grFzeroCar layout");
