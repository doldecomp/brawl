#include <cm/cm_camera_controller.h>
#include <gf/gf_archive.h>
#include <gm/gm_global.h>
#include <gr/collision/gr_collision.h>
#include <math.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/math/math_triangular.h>
#include <st/st_positions.h>
#include <st_fzero/st_fzero.h>

// MATCH-ONLY: the stage's empty string (shared by the createCollisionSelf name arguments).
extern const char g_fzeroEmptyString[];

// HYPOTHESIS: tears down a stCollisionWork (an unnamed function of sora_melee).
extern "C" void fn_27_239F6C(stCollisionWork* work);
// HYPOTHESIS: an inline helper of the original (a tolerance test used by both the stage and its cars).
static inline bool fzeroIsNearZero(float value) {
    bool result = false;
    if ((float)fabs(value) < 1e-5f) {
        result = true;
    }
    return result;
}

// MATCH-ONLY: a view of the joint's flag word (HYPOTHESIS: byte 2 selects the joint's collision mode).
struct fzeroJointBits {
    unsigned m_hi : 8;
    unsigned m_mode : 8;
    unsigned m_lo : 16;
};

stClassInfoImpl<Stages::FZero, stFzero> stFzero::bss_loc_14;

stFzero* stFzero::create() {
    return new (Heaps::StageInstance) stFzero;
}

stFzero::stFzero() : stMelee("stFzero", Stages::FZero) {
    m_sceneFrame = 0.0f;
    unk1DC = 0.0f;
    m_scene = 7;
    m_prevScene = 7;
    m_state = 8;
    for (u8 i = 0; i < 40; i++) {
        mtx(i)->setIdentity();
    }
    memset(&m_limitMin, 0, 0x18);
    m_sceneState = 0;
    m_carState = 0;
    m_carTimer = 0.0f;
    m_carMode = 8;
    m_carMotion = 5;
    for (u8 i = 0; i < 30; i++) {
        stFzeroCarData* car = &m_carData[i];
        car->m_mtx = NULL;
        car->m_pos.m_x = 0.0f;
        car->m_pos.m_y = 0.0f;
        car->m_pos.m_z = 0.0f;
        car->m_state = 8;
        car->m_type = 0;
    }
    m_stateWall = 8;
    m_eventFlag = 0;
    m_collisionWork.initialize();
    m_collisionWork.m_isClosed = false;
    m_collisionWork.m_vtxLen = 2;
    m_floorCollision = NULL;
}

stFzero::~stFzero() {
    fn_27_239F6C(&m_collisionWork);
    releaseArchive();
}

bool stFzero::loading() {
    return true;
}

void stFzero::createObj() {
    testStageParamInit(m_fileData, 10);
    testStageDataInit(m_fileData, 20, 92);
    initPosPokeTrainer(4, 1);
    createObjBg(0);
    createCollision(m_fileData, 2, NULL);
    createObjStartLine(1);
    createObjPlateRing(3);
    createObjAshiba(2);
    createObjAshiba(4);
    createObjAshiba(5);
    createObjAshiba(6);
    createObjAshiba(7);
    createObjAshiba(8);
    createObjWall(9);
    createObjTrainer(10);
    createObjAttack(11);
    createObjAttack(12);
    createObjAttack(13);
    createObjWarning(14);
    createObjMachineNode(15);
    createObjMachine();
    m_floorCollision = createCollisionSelf(&m_collisionWork, NULL, g_fzeroEmptyString, g_fzeroEmptyString, 0x400);
    initCameraParam();
    loadStageAttrParam(m_fileData, 30);
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 100, 0xFFFE));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        createStagePositions();
    }
    createWind2ndOnly();
    registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    gmGlobalModeMelee* melee = g_GameGlobal->m_modeMelee;
    if (melee != NULL && melee->m_meleeInitData.m_gameMode == 7 && *((u8*)melee + 0x10) == 0x1f) {
        m_eventFlag = 1;
    }
}

void stFzero::createObjBg(int index) {
    grFzeroBg* ground = grFzeroBg::create(1, "StgFzero00", "grFzeroMainBg");
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setFrameSceneWork(&m_sceneFrame);
        ground->setStateWork(&m_state);
        ground->setMtxGimmickWork(mtx(0));
        ground->setCarMotionWork(&m_carMotion);
    }
}

void stFzero::createObjStartLine(int index) {
    grFzeroStartLine* ground = grFzeroStartLine::create(2, "TopN", "grFzeroStartLine");
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setMtxWork(mtx(21));
    }
}

void stFzero::createObjPlateRing(int index) {
    grFzeroPlateRing* ground = grFzeroPlateRing::create(4, "Dplate_e_ring", "grFzeroPlateRing");
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setMtxWork(mtx(20));
    }
}

void stFzero::createObjAshiba(int index) {
    grFzeroAshiba* ground;
    Matrix* mtxWork;
    u8 scene;
    int collisionIndex;
    switch (index) {
    case 2:
        ground = grFzeroAshiba::create(10, "StgFzeroAsibaIdou", "grFzeroAshibaIdou");
        mtxWork = NULL;
        scene = 7;
        collisionIndex = 0x37;
        break;
    case 4:
        ground = grFzeroAshiba::create(12, "StgFzeroAshiba02", "grFzeroAshiba02");
        mtxWork = mtx(3);
        scene = 0;
        collisionIndex = 0x32;
        break;
    case 5:
        ground = grFzeroAshiba::create(13, "StgFzeroAshiba03", "grFzeroAshiba03");
        mtxWork = mtx(4);
        scene = 1;
        collisionIndex = 0x33;
        break;
    case 6:
        ground = grFzeroAshiba::create(14, "StgFzeroAshiba04", "grFzeroAshiba04");
        mtxWork = mtx(5);
        scene = 2;
        collisionIndex = 0x34;
        break;
    case 7:
        ground = grFzeroAshiba::create(15, "StgFzeroAshiba05", "grFzeroAshiba05");
        mtxWork = mtx(6);
        scene = 3;
        collisionIndex = 0x35;
        break;
    case 8:
        ground = grFzeroAshiba::create(17, "StgFzeroAshiba07", "grFzeroAshiba07");
        mtxWork = mtx(8);
        scene = 5;
        collisionIndex = 0x36;
        break;
    default:
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setScene(scene);
        ground->setStateWork(&m_state);
        ground->setStateNodeWork(&m_carMode);
        ground->setMtxWork(mtxWork);
        createCollision(m_fileData, collisionIndex, ground);
    }
}

void stFzero::createObjWall(int index) {
    grFzeroWall* ground;
    if (index == 9) {
        ground = grFzeroWall::create(0x5a, "wall_col", "grFzeroWall");
    } else {
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setStateWork(&m_state);
        ground->setStateWallWork(&m_stateWall);
        ground->setMtxGimmickWork(mtx(0));
        createCollision(m_fileData, 0x5a, ground);
    }
}

void stFzero::createObjTrainer(int index) {
    grFzeroTrainer* ground;
    if (index == 10) {
        ground = grFzeroTrainer::create(5, "StgFzeroPTposition", "grFzeroTrainer");
    } else {
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setFrameSceneWork(&m_sceneFrame);
        ground->setMtxWork(mtx(0));
        ground->setPosTrainerWork(m_pokeTrainerPos);
    }
}

void stFzero::createObjAttack(int index) {
    grFzeroAttack* ground;
    u8 type;
    switch (index) {
    case 11:
        ground = grFzeroAttack::create(0x50, "nodeIndex", "grFzeroAttackFloor00");
        type = 4;
        break;
    case 12:
        ground = grFzeroAttack::create(0x50, "nodeIndex", "grFzeroAttackFloor01");
        type = 5;
        break;
    case 13:
        ground = grFzeroAttack::create(0x50, "nodeIndex", "grFzeroAttackWall");
        type = 6;
        break;
    default:
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setFrameSceneWork(&m_sceneFrame);
        ground->setStateWork(&m_state);
        ground->setStateWallWork(&m_stateWall);
        ground->setMtxGimmickWork(mtx(0));
        ground->setPosLimitWork(&m_limitMin.m_x);
        ground->setType(type);
    }
}

void stFzero::createObjWarning(int index) {
    grFzeroWarning* ground;
    if (index == 14) {
        ground = grFzeroWarning::create(0x5f, "StgFzeroWarning", "grFzeroWarning");
    } else {
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setFrameSceneWork(&m_sceneFrame);
        ground->setStateWork(&m_state);
        ground->setMtxGimmickWork(mtx(0));
    }
}

void stFzero::createObjMachineNode(int index) {
    grFzeroNode* ground;
    if (index == 15) {
        ground = grFzeroNode::create(0x41, "StgFzeroMachineNode", "grFzeroNode");
    } else {
        ground = NULL;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setFrameSceneWork(&m_sceneFrame);
        ground->setStateWork(&m_carMode);
        ground->setMtxWork(mtx(21));
        ground->setMtxGimmickWork(mtx(0));
        ground->setMotionWork(&m_carMotion);
    }
}

void stFzero::createObjMachine() {
    for (u32 i = 1; i < 0x1f; i++) {
        createObjMachine1(i & 0xff);
    }
}

void stFzero::createObjMachine1(int index) {
    grFzeroCar* ground;
    switch (index) {
    case 1:
        ground = grFzeroCar::create(0x1f, "StgFzeroMachine01", "grFzeroMachine01");
        break;
    case 2:
        ground = grFzeroCar::create(0x20, "StgFzeroMachine02", "grFzeroMachine02");
        break;
    case 3:
        ground = grFzeroCar::create(0x21, "StgFzeroMachine03", "grFzeroMachine03");
        break;
    case 4:
        ground = grFzeroCar::create(0x22, "StgFzeroMachine04", "grFzeroMachine04");
        break;
    case 5:
        ground = grFzeroCar::create(0x23, "StgFzeroMachine05", "grFzeroMachine05");
        break;
    case 6:
        ground = grFzeroCar::create(0x24, "StgFzeroMachine06", "grFzeroMachine06");
        break;
    case 7:
        ground = grFzeroCar::create(0x25, "StgFzeroMachine07", "grFzeroMachine07");
        break;
    case 8:
        ground = grFzeroCar::create(0x26, "StgFzeroMachine08", "grFzeroMachine08");
        break;
    case 9:
        ground = grFzeroCar::create(0x27, "StgFzeroMachine09", "grFzeroMachine09");
        break;
    case 10:
        ground = grFzeroCar::create(0x28, "StgFzeroMachine10", "grFzeroMachine10");
        break;
    case 11:
        ground = grFzeroCar::create(0x29, "StgFzeroMachine11", "grFzeroMachine11");
        break;
    case 12:
        ground = grFzeroCar::create(0x2a, "StgFzeroMachine12", "grFzeroMachine12");
        break;
    case 13:
        ground = grFzeroCar::create(0x2b, "StgFzeroMachine13", "grFzeroMachine13");
        break;
    case 14:
        ground = grFzeroCar::create(0x2c, "StgFzeroMachine14", "grFzeroMachine14");
        break;
    case 15:
        ground = grFzeroCar::create(0x2d, "StgFzeroMachine15", "grFzeroMachine15");
        break;
    case 16:
        ground = grFzeroCar::create(0x2e, "StgFzeroMachine16", "grFzeroMachine16");
        break;
    case 17:
        ground = grFzeroCar::create(0x2f, "StgFzeroMachine17", "grFzeroMachine17");
        break;
    case 18:
        ground = grFzeroCar::create(0x30, "StgFzeroMachine18", "grFzeroMachine18");
        break;
    case 19:
        ground = grFzeroCar::create(0x31, "StgFzeroMachine19", "grFzeroMachine19");
        break;
    case 20:
        ground = grFzeroCar::create(0x32, "StgFzeroMachine20", "grFzeroMachine20");
        break;
    case 21:
        ground = grFzeroCar::create(0x33, "StgFzeroMachine21", "grFzeroMachine21");
        break;
    case 22:
        ground = grFzeroCar::create(0x34, "StgFzeroMachine22", "grFzeroMachine22");
        break;
    case 23:
        ground = grFzeroCar::create(0x35, "StgFzeroMachine23", "grFzeroMachine23");
        break;
    case 24:
        ground = grFzeroCar::create(0x36, "StgFzeroMachine24", "grFzeroMachine24");
        break;
    case 25:
        ground = grFzeroCar::create(0x37, "StgFzeroMachine25", "grFzeroMachine25");
        break;
    case 26:
        ground = grFzeroCar::create(0x38, "StgFzeroMachine26", "grFzeroMachine26");
        break;
    case 27:
        ground = grFzeroCar::create(0x39, "StgFzeroMachine27", "grFzeroMachine27");
        break;
    case 28:
        ground = grFzeroCar::create(0x3a, "StgFzeroMachine28", "grFzeroMachine28");
        break;
    case 29:
        ground = grFzeroCar::create(0x3b, "StgFzeroMachine29", "grFzeroMachine29");
        break;
    case 30:
        ground = grFzeroCar::create(0x3c, "StgFzeroMachine30", "grFzeroMachine30");
        break;
    }
    if (ground != NULL) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setSceneWork(&m_scene);
        ground->setStateWork(&m_state);
        ground->setCarData(&m_carData[index - 1]);
    }
}

void stFzero::update(float deltaFrame) {
    updateLimit();
    updateCar(deltaFrame);
    updateScene(deltaFrame);
    updateFloor(deltaFrame);

    // The camera never looks below the lower of the two limit matrices (HYPOTHESIS: they mark the course's floor).
    Vec3f upper(mtx(22)->m[0][3], mtx(22)->m[1][3], mtx(22)->m[2][3]);
    Vec3f lower(mtx(23)->m[0][3], mtx(23)->m[1][3], mtx(23)->m[2][3]);
    Vec3f floorPos;
    if (upper.m_y < lower.m_y) {
        floorPos = upper;
    } else if (upper.m_y > lower.m_y) {
        floorPos = lower;
    } else {
        floorPos = upper;
    }

    CameraController* camera = CameraController::getInstance();
    Rect2D range = *reinterpret_cast<Rect2D*>((u8*)camera + 0x148);
    if (range.m_down < floorPos.m_y) {
        range.m_down = floorPos.m_y;
        cmStageParam* param = &CameraController::getInstance()->m_stageCameraParam;
        if (param != NULL) {
            float cosine = nw4r::math::CosFIdx(10.666667f);
            float sine = nw4r::math::SinFIdx(10.666667f);
            range.m_down -= 0.5f * (param->m_verticalRotationFactor * (sine / cosine));
        }
    }
    CameraController::getInstance()->setCameraRange(&range);
    *(float*)((u8*)CameraController::getInstance() + 0x18C) = 0.0f;
}

// Mirrors the camera's limits into the stage so the hazards can stay inside them.
void stFzero::updateLimit() {
    CameraController* camera = CameraController::getInstance();
    float minY = camera->unk160;
    float minX = camera->unk158;
    m_limitMin.m_x = minX;
    m_limitMin.m_y = minY;
    m_limitMin.m_z = 0.0f;
    float maxY = camera->unk164;
    float maxX = camera->unk15C;
    m_limitMax.m_x = maxX;
    m_limitMax.m_y = maxY;
    m_limitMax.m_z = 0.0f;
}

bool stFzero::isEventEnd(int param1, int* eventState, int* eventDecision) {
    if (m_eventFlag == 0) {
        return false;
    }
    if (m_scene == 0 && m_prevScene == 6) {
        *eventState = 6;
        *eventDecision = 3;
        return true;
    }
    m_prevScene = m_scene;
    return false;
}

bool stFzero::isStageDown() {
    switch (m_state) {
    case 1:
    case 2:
        return true;
    }
    return false;
}

GXColor stFzero::getFinalTechniqColor() {
    u32 packed = 0x14000496;
    return *reinterpret_cast<GXColor*>(&packed);
}

// Reloads the stage positions when the stage goes down (section 2) and again when it is back up.
void stFzero::updateScene(float deltaFrame) {
    switch (m_sceneState) {
    case 0:
        m_sceneState = 1;
        // fall through
    case 1:
        switch (m_scene) {
        case 2:
            if (isStageDown() == true) {
                nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x65, 0xFFFE));
                if (posData.ptr()) {
                    m_stagePositions->loadPositionData(&posData);
                }
                updateStagePositions();
                m_sceneState = 3;
            }
            break;
        }
        break;
    case 2:
        break;
    case 3:
        if (isStageDown() == false) {
            nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 100, 0xFFFE));
            if (posData.ptr()) {
                m_stagePositions->loadPositionData(&posData);
            }
            updateStagePositions();
            m_sceneState = 1;
        }
        break;
    }
}

// HYPOTHESIS: the floor collision is a flat quad between the two limit matrices; it is switched off while the course
// is out of the way (stage down, or the limits are below the fighters).
void stFzero::updateFloor(float deltaFrame) {
    if (m_floorCollision == NULL) {
        return;
    }

    Vec3f a(mtx(22)->m[0][3], mtx(22)->m[1][3], 0.0f);
    Vec3f b(mtx(23)->m[0][3], mtx(23)->m[1][3], 0.0f);
    Vec3f subResult;
    Vec3fSub(&subResult, &b, &a);
    Vec3f diff = subResult;
    bool same = false;
    if (fzeroIsNearZero(diff.m_x) && fzeroIsNearZero(diff.m_y) && fzeroIsNearZero(diff.m_z)) {
        same = true;
    }

    if (!same) {
        switch (m_scene) {
        case 5:
        case 6:
            if (a.m_y < b.m_y) {
                b.m_y = a.m_y;
            } else if (a.m_y > b.m_y) {
                a.m_y = b.m_y;
            }
            break;
        }
        grCollisionJoint* joint = m_floorCollision->getJoint(0);
        if (joint == NULL) {
            return;
        }
        float* vtx = reinterpret_cast<float*>(joint->m_vtxDatas);
        if (vtx == NULL) {
            return;
        }
        reinterpret_cast<fzeroJointBits*>(reinterpret_cast<u8*>(joint) + 0x48)->m_mode = 3;
        vtx[0] = a.m_x;
        vtx[1] = a.m_y;
        vtx[2] = b.m_x;
        vtx[3] = b.m_y;
    }

    switch (m_state) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if (m_floorCollision->m_isEnabled == true) {
            m_floorCollision->setDisable();
        }
        break;
    default:
        if (b.m_y < m_limitMax.m_y || a.m_y < m_limitMax.m_y) {
            if (m_floorCollision->m_isEnabled == true) {
                m_floorCollision->setDisable();
            }
        } else if (!m_floorCollision->m_isEnabled) {
            m_floorCollision->setEnable();
        }
    }
}

// Picks a random index below count (the original clamps a truncated float to the last index).
static inline u8 fzeroRandIndex(float count, u8 last) {
    u32 value = (u32)(int)(count * randf());
    u8 low = value;
    value = low ? value : 0;
    u8 index = last;
    if ((u8)value < last) {
        index = value;
    }
    return index;
}

// The cars: while the course is running (state 0/1) the timer counts down to the next wave of cars, whose length depends
// on the course section; when it runs out a wave is spawned (state 2) by assigning random cars to random matrices of the
// course and cycling their type, and once the cars have all left (state 3) the table is cleared again.
void stFzero::updateCar(float deltaFrame) {
    m_carTimer -= deltaFrame;
    if (m_carTimer < 0.0f) {
        m_carTimer = 0.0f;
    }

    switch (m_carState) {
    case 0:
        m_carState = 1;
        // fall through
    case 1:
        if (m_carTimer == 0.0f) {
            switch (m_scene) {
            case 0:
                if (isStageDown() == 0) {
                    m_carTimer = 120.0f;
                }
                break;
            case 1:
                m_carTimer = 180.0f;
                break;
            case 2:
                if (isStageDown() == 0 && randf() > 0.4f) {
                    m_carTimer = 600.0f;
                }
                break;
            case 3:
                if (isStageDown() == 0) {
                    m_carTimer = 300.0f;
                }
                break;
            case 4:
                if (isStageDown() == 0) {
                    m_carTimer = 600.0f;
                }
                break;
            case 5:
                if (isStageDown() == 0) {
                    m_carTimer = 600.0f;
                }
                break;
            case 6:
                if (isStageDown() == 0) {
                    m_carTimer = 300.0f;
                }
                break;
            default:
                m_carTimer = 600.0f;
            }
            if (m_carTimer == 0.0f) {
                m_carMode = 6;
                m_carState = 2;
            }
        }
        break;
    case 2:
        if (m_carMode != 6) {
            if (m_carMode == 8) {
                m_carState = 0;
            } else {
                u8 order[32];
                for (u8 i = 0; i < 30; i++) {
                    order[i] = i;
                }
                for (u8 i = 0; i < 30; i++) {
                    u8 j = fzeroRandIndex(30.0f, 29);
                    u8 tmp = order[i];
                    order[i] = order[j];
                    order[j] = tmp;
                }
                u8 mtxOrder[16];
                mtxOrder[0] = 0;
                mtxOrder[1] = 1;
                mtxOrder[2] = 2;
                mtxOrder[3] = 3;
                mtxOrder[4] = 4;
                mtxOrder[5] = 5;
                mtxOrder[6] = 6;
                mtxOrder[7] = 7;
                mtxOrder[8] = 8;
                mtxOrder[9] = 9;
                mtxOrder[10] = 10;
                mtxOrder[11] = 11;
                mtxOrder[12] = 12;
                mtxOrder[13] = 13;
                mtxOrder[14] = 14;
                for (u8 i = 0; i < 15; i++) {
                    u8 j = fzeroRandIndex(15.0f, 14);
                    u8 tmp = mtxOrder[i];
                    mtxOrder[i] = mtxOrder[j];
                    mtxOrder[j] = tmp;
                }
                int type = 0;
                for (u8 i = 0; i < 15; i++) {
                    stFzeroCarData* car = &m_carData[order[i]];
                    car->m_mtx = mtx(mtxOrder[i] + 24);
                    car->m_state = 7;
                    car->m_type = type;
                    switch (type) {
                    case 0:
                        type = 1;
                        break;
                    case 1:
                        type = 2;
                        break;
                    case 2:
                        type = 3;
                        break;
                    case 3:
                        type = 0;
                        break;
                    }
                }
                m_carMode = 7;
                m_carState = 3;
            }
        }
        break;
    case 3:
        if (m_carMode == 8) {
            for (u8 i = 0; i < 30; i++) {
                m_carData[i].m_mtx = NULL;
                m_carData[i].m_state = 8;
            }
            m_carState = 0;
        }
        break;
    }
}
