#pragma once

#include <StaticAssert.h>
#include <cm/cm_controller_anm.h>
#include <cm/cm_quake.h>
#include <cm/cm_stage_param.h>
#include <gf/gf_task.h>
#include <types.h>

class CameraController : public gfTask {
public:
    enum Kind {
        None = 0x0,
        Animation = 0x1,
        AI = 0x2,
        Adventure = 0x3,
        AdventureFree = 0x4,
        AnimationLocked = 0x5,
        FighterTarget = 0x6,
        Photo = 0x7,
        MenuPad = 0x8,
        MenuFixed = 0x9,
        FigDisp1 = 0xa,
        Tech = 0xb,
        MeleeFixed = 0xc,
        Demo = 0xd,
        Default = 0xe
    };

    Kind m_currentControllerKind;
    char _68[4];
    gfCameraController* m_currentController;
    gfCameraController* m_defaultController;
    cmAnimationController* m_animationController;
    gfCameraController* m_fighterTargetController;
    gfCameraController* m_aiController;
    gfCameraController* m_meleeFixedController;
    gfCameraController* m_adventureController;
    gfCameraController* m_adventureFreeController;
    gfCameraController* m_photoController;
    gfCameraController* m_menuPadController;
    gfCameraController* m_menuFixedController;
    gfCameraController* m_figDisp1Controller;
    gfCameraController* m_techController;
    void* m_quake;
    gfCameraController* m_demoController;
    cmStageParam m_stageCameraParam; // 0x84
    cmStageParamPaused m_stageCameraParamPaused; // 0xC4
    cmStageParamFixed m_stageCameraParamFixed; // 0x110
    Rect2D m_stageCameraRange; // 0x128
    Rect2D m_stageDeadRange; // 0x138
    char _328[16]; // 0x148
    float unk158;
    float unk15C;
    float unk160;
    float unk164;
    char unk168[60];

    virtual void processCamera();
    virtual void processDebug();
    virtual void renderDebug();
    virtual void init();
    virtual ~CameraController();

    void changeInput(Kind cameraControllerKind);
    void setRangeOffset(Vec2f* offset);
    void setCameraRange(Rect2D*);
    gfCameraController* getCameraController(Kind kind);
    static CameraController* getInstance();
};
static_assert(sizeof(CameraController) == 420, "Class is wrong size!");
