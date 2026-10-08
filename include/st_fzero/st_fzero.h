#pragma once

#include <mt/mt_matrix.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <st_fzero/gr_fzero.h>

class grCollision;

// The stage matrices are plain storage (constructed with setIdentity in the constructor, not through Matrix's own).
struct stFzeroMtx {
    float m[3][4];
};

template<typename T>
class stClassInfoImpl<Stages::FZero, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::FZero, this);
    }

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::FZero, nullptr);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

// Mute City (F-Zero). The stage runs a course sequence (m_scene) and keeps the shared state its gimmicks read through
// pointers: the scene frame, matrices for every moving piece, the car table and the camera limits.
class stFzero : public stMelee {
    float m_sceneFrame;          // 0x1D8 frame counter of the current course section
    float unk1DC;                // 0x1DC
    u8 m_scene;                  // 0x1E0 current course section (7 = none yet)
    u8 m_prevScene;              // 0x1E1 section seen by the last isEventEnd
    u8 m_state;                  // 0x1E2 stage state (8 = idle)
    stFzeroMtx m_mtx[40];        // 0x1E4 matrices the gimmicks follow
    Vec3f m_limitMin;            // 0x964 camera limits: min corner
    Vec3f m_limitMax;            // 0x970 max corner
    u8 m_sceneState;             // 0x97C progress of the stage-position reloads (updateScene)
    u8 m_carState;               // 0x97D progress of the car spawner
    float m_carTimer;            // 0x980 frames until the next car event
    u8 m_carMode;                // 0x984 current car mode (8 = idle)
    u8 m_carMotion;              // 0x985 motion of the cars
    stFzeroCarData m_carData[30]; // 0x988
    u8 m_stateWall;              // 0xBE0 wall progress (8 = idle)
    u8 m_eventFlag;              // 0xBE1 set in the adventure mode level this stage is used by
    stCollisionWork m_collisionWork; // 0xBE4
    u16 unkBF0;                  // 0xBF0
    u8 unkBF2;                   // 0xBF2
    grCollision* m_floorCollision; // 0xBF4 collision of the floor that is enabled while the course is out

public:
    stFzero();
    virtual ~stFzero();
    virtual void createObj();
    virtual bool loading();
    virtual bool isEventEnd(int param1, int* eventState, int* eventDecision);
    virtual GXColor getFinalTechniqColor();
    virtual void update(float deltaFrame);
    virtual void createObjBg(int index);
    virtual void createObjStartLine(int index);
    virtual void createObjPlateRing(int index);
    virtual void createObjAshiba(int index);
    virtual void createObjWall(int index);
    virtual void createObjTrainer(int index);
    virtual void createObjAttack(int index);
    virtual void createObjWarning(int index);
    virtual void createObjMachineNode(int index);
    virtual void createObjMachine();
    virtual void createObjMachine1(int index);
    virtual void updateLimit();
    virtual void updateCar(float deltaFrame);
    virtual void updateScene(float deltaFrame);
    virtual void updateFloor(float deltaFrame);
    virtual bool isStageDown();

    Matrix* mtx(int index) { return reinterpret_cast<Matrix*>(&m_mtx[index]); }

    static stFzero* create();
    static stClassInfoImpl<Stages::FZero, stFzero> bss_loc_14;
};
static_assert(sizeof(stFzero) == 0xBF8, "stFzero layout");
