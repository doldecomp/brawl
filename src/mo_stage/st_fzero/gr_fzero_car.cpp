#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>
#include <gr/gr_calc_world_callback.h>

grFzeroCar::grFzeroCar(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_stateWork = NULL;
    m_carData = NULL;
    m_animId = 2;
    m_animFrames = 0.0f;
    m_hasYakumono = 0;
    m_attackEnabled = 0;
    m_work = NULL;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 8;
    m_seHandle = -1;
    m_seHandleNear = -1;
}

grFzeroCar* grFzeroCar::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroCar* ground = new (Heaps::StageInstance) grFzeroCar(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroCar::~grFzeroCar() {
    if (m_work != NULL) {
        delete m_work;
    }
    m_work = NULL;
}

void grFzeroCar::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateYakumono(deltaFrame);
        updateActive(deltaFrame);
        updateCallBack(deltaFrame);
    }
}

// Creates the hit (setHit) once the car exists.
void grFzeroCar::updateYakumono(float deltaFrame) {
    if (m_hasYakumono != 1) {
        setHit();
        if (m_yakumono != NULL) {
            m_hasYakumono = 1;
        }
    }
}

// The engine sound that goes with a car type (-1 for none).
static inline int grFzeroCarPassSound(u8 type) {
    int id;
    if (type == 2) {
        id = 0x1c68;
    } else if (type < 2) {
        if (type == 0) {
            id = 0x1c66;
        } else {
            id = 0x1c67;
        }
    } else if (type < 4) {
        id = 0x1c69;
    } else {
        id = -1;
    }
    return id;
}

// The sound of a car going past the fighters.
static inline int grFzeroCarNearSound(u8 type) {
    int id;
    if (type == 2) {
        id = 0x1c6c;
    } else if (type < 2) {
        if (type == 0) {
            id = 0x1c6a;
        } else {
            id = 0x1c6b;
        }
    } else if (type < 4) {
        id = 0x1c6d;
    } else {
        id = -1;
    }
    return id;
}

// Distance of the car from the origin of its matrix (HYPOTHESIS: the camera/ring centre), zero when it is there.
static inline float grFzeroCarDistance(grCalcWorldCallBack* callback) {
    Matrix* mtx = &callback->m_nodeCallbackDatas[0].m_matrix;
    float x = mtx->m[0][3];
    float z = mtx->m[2][3];
    float y = mtx->m[1][3];
    float distance;
    bool atOrigin = false;
    if (fzeroIsNearZero(x) && fzeroIsNearZero(y) && fzeroIsNearZero(z)) {
        atOrigin = true;
    }
    if (atOrigin) {
        distance = 0.0f;
    } else {
        distance = z * z + x * x + y * y;
        if ((float)fabs(distance) > 1.17549435e-38f) {
            distance = distance * rsqrtf(distance);
        } else {
            distance = 0.0f;
        }
    }
    return distance;
}

void grFzeroCar::updateActive(float deltaFrame) {
    if (m_carData == NULL) {
        return;
    }
    switch (m_state) {
    case 2:
        break;
    case 0:
        setMotionCommon(2, 0, 1, 0);
        setVisibility(0);
        disableAttack(0);
        m_attackEnabled = 0;
        m_state = 1;
        // fall through
    case 1:
        if (m_carData->m_state == 7) {
            setMotionCommon(1, 1, 1, &m_animFrames);
            int id = grFzeroCarPassSound(m_carData->m_type);
            if (id != -1) {
                m_seHandle = m_sndGen.playSE(static_cast<SndID>(id), 0, 30, -1);
            }
            m_state = 3;
        }
        break;
    case 3: {
        if (!m_isVisible) {
            setVisibility(1);
        }
        grCalcWorldCallBack* callback = &m_calcWorldCallBack;
        if (callback != NULL) {
            float distance = grFzeroCarDistance(callback);
            if (distance <= 2048.0f) {
                setAttack();
            } else {
                if (m_attackEnabled == 1) {
                    disableAttack(0);
                }
                m_attackEnabled = 0;
            }
            if (m_seHandleNear == -1) {
                u8 scene = *m_sceneWork;
                bool close = scene != 2 && scene != 1;
                if (scene == 3 && *m_stateWork == 0) {
                    close = false;
                }
                if (close) {
                    callback = &m_calcWorldCallBack;
                    if (callback == NULL) {
                        return;
                    }
                    float nearDistance = grFzeroCarDistance(callback);
                    if (nearDistance < 1000.0f) {
                        int id = grFzeroCarNearSound(m_carData->m_type);
                        if (id != -1) {
                            m_seHandleNear = m_sndGen.playSE(static_cast<SndID>(id), 0, 30, -1);
                        }
                    }
                }
            }
            if (m_carData->m_state == 8) {
                m_carData->m_mtx = NULL;
                if (m_seHandle != -1) {
                    m_sndGen.stopSE(m_seHandle, 30);
                }
                m_seHandle = -1;
                m_seHandleNear = -1;
                m_state = 0;
            }
        }
        break;
    }
    }
}

// The model follows the stage matrix of its car; it is hidden while it stands still.
void grFzeroCar::updateCallBack(float deltaFrame) {
    grCalcWorldCallBack* calcWorldCallBack = &m_calcWorldCallBack;
    if (calcWorldCallBack != NULL) {
        nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
        if (scnMdl != NULL) {
            if (scnMdl->m_calcWorldCallBack == NULL) {
                calcWorldCallBack->m_index = 0;
                calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex = m_nodeIndex;
                scnMdl->m_calcWorldCallBack = calcWorldCallBack;
                scnMdl->EnableScnMdlCallbackTiming(1);
                scnMdl->m_nodeIndex = calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex;
            }
            if (m_carData != NULL && m_carData->m_mtx != NULL) {
                Matrix* mtx = m_carData->m_mtx;
                bool same = false;
                calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix = *mtx;
                Matrix* node = &calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix;
                Vec3f pos;
                pos.m_z = node->m[2][3];
                pos.m_y = node->m[1][3];
                pos.m_x = node->m[0][3];
                if (fzeroIsNearZero(pos.m_x - m_carData->m_pos.m_x) && fzeroIsNearZero(pos.m_y - m_carData->m_pos.m_y) &&
                    fzeroIsNearZero(pos.m_z - m_carData->m_pos.m_z)) {
                    same = true;
                }
                if (same && deltaFrame != 0.0f) {
                    if (m_isVisible) {
                        setVisibility(0);
                    }
                } else if (!m_isVisible) {
                    setVisibility(1);
                }
                m_carData->m_pos.m_x = pos.m_x;
                m_carData->m_pos.m_y = pos.m_y;
                m_carData->m_pos.m_z = pos.m_z;
                m_sndGen.setPos(&pos);
            }
        }
    }
}

// The car hurts fighters it hits: a ball of 20 units around the car, enabled once.
void grFzeroCar::setAttack() {
    if (m_attackEnabled == 1) {
        return;
    }

    soCollisionAttackData attack(1.0f);
    Vec3f offset;
    offset.m_x = 0.0f;
    offset.m_y = 5.0f;
    offset.m_z = 0.0f;

    setAttackGimmickDetails(&attack, 20.0f, 1.0f, 0.5f, 1.0f,
        20, &offset, 90, 100, 0, 70, 0,
        0x3FF, 7, false, 15,
        soCollisionAttackData::Attribute_Normal, soCollisionAttackData::Sound_Level_Medium,
        soCollisionAttackData::Sound_Attribute_Cutup,
        false, false, false, true, false, false, 0, 60,
        false, false, false, soCollisionAttackData::Lr_Check_Pos,
        false, false, false, false, false, soCollisionAttackData::Region_None, false);
    m_yakumono->setAttack(0, 0, &attack);
    m_attackEnabled = 1;
}

// Binds the two animations of the car (0 and 1); animation 2 means "none".
void grFzeroCar::setMotionCommon(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    if (m_animId == animId && force == 0) {
        return;
    }

    nw4r::g3d::ScnMdl* sceneMdl = *m_sceneModels;
    if (sceneMdl == NULL) {
        return;
    }

    gfModelAnimation* modelAnim = *m_modelAnims;
    if (modelAnim == NULL) {
        return;
    }

    nw4r::g3d::ResMdl model = sceneMdl->m_resMdl;
    if (!model.IsValid()) {
        return;
    }

    modelAnim->unbindNodeAnim(sceneMdl);
    modelAnim->unbindVisibleAnim(sceneMdl);
    modelAnim->unbindTexAnim(sceneMdl);
    modelAnim->unbindTexSrtAnim(sceneMdl);
    modelAnim->unbindMatColAnim(sceneMdl);
    m_animId = animId;

    if (animId >= 2) {
        return;
    }

    bool result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if (result) {
        grFzeroSetChrAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if (result) {
        grFzeroSetVisibilityAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if (result) {
        grFzeroSetTexPatAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if (result) {
        grFzeroSetTexSrtAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if (result) {
        grFzeroSetColorAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoop(shouldLoop);

    if (frameCount != NULL) {
        *frameCount = modelAnim->getFrameCount();
    }
}
