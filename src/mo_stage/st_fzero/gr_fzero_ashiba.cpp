#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>
#include <gr/gr_calc_world_callback.h>
#include <gr/collision/gr_collision.h>

// HYPOTHESIS: translates a matrix by (x, y, z) (an unnamed function of the main binary).
extern "C" void fn_8003F074(Matrix* mtx, float x, float y, float z);

grFzeroAshiba* grFzeroAshiba::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroAshiba* ground = new (Heaps::StageInstance) grFzeroAshiba(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroAshiba::grFzeroAshiba(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_stateWork = NULL;
    m_stateNodeWork = NULL;
    m_mtxWork = NULL;
    m_offsetX = 0.0f;
    m_offsetY = 0.0f;
    m_offsetZ = 0.0f;
    m_joint = NULL;
    m_animId = 2;
    m_timer2 = 0.0f;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 8;
}

grFzeroAshiba::~grFzeroAshiba() {
}

void grFzeroAshiba::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        if (m_scene == 7) {
            if (m_joint == NULL && m_collision != NULL) {
                m_joint = m_collision->getJoint(0);
            }
            updateActiveIdou(deltaFrame);
        } else {
            updateActive(deltaFrame);
        }
        updateCallBack(deltaFrame);
    }
}

// A fixed platform: it shows up (and becomes solid) once the stage has handed its section the "go" state and hides
// again after the section's animation is over.
void grFzeroAshiba::updateActive(float deltaFrame) {
    m_timer -= deltaFrame;
    if (m_timer < 0.0f) {
        m_timer = 0.0f;
    }
    m_timer2 -= deltaFrame;
    if (m_timer2 < 0.0f) {
        m_timer2 = 0.0f;
    }

    switch (m_state) {
    case 0:
        setMotion(2, false, true, NULL);
        setVisibility(false);
        setEnableCollisionStatus(false);
        m_state = 1;
        break;
    case 1:
        if (m_scene == *m_sceneWork && *m_stateWork == 1) {
            setMotion(1, false, true, &m_timer2);
            m_state = 6;
        }
        break;
    case 6:
        if (!m_isVisible) {
            setVisibility(true);
            setEnableCollisionStatus(true);
        }
        if (m_timer2 == 0.0f) {
            m_state = 7;
        }
        break;
    case 7:
        if (*m_stateWork < 5 && *m_stateWork > 2) {
            setMotion(0, false, true, &m_timer2);
            m_state = 8;
        }
        break;
    case 8:
        if (m_timer2 == 0.0f) {
            m_state = 0;
        }
        break;
    }
}

// The moving platform rises out of the course (6) and sinks back into it (8) on the stage's state byte; while it is
// out its collision joint is flagged.
void grFzeroAshiba::updateActiveIdou(float deltaFrame) {
    m_timer -= deltaFrame;
    if (m_timer < 0.0f) {
        m_timer = 0.0f;
    }

    switch (m_state) {
    case 0:
        setVisibility(true);
        setEnableCollisionStatus(true);
        m_state = 1;
        break;
    case 1:
        if (*m_stateWork == 1) {
            grCollisionJoint* joint = m_joint;
            m_offsetX = 0.0f;
            m_timer = 120.0f;
            m_offsetY = 0.0f;
            m_offsetZ = 0.0f;
            if (joint != NULL) {
                joint->m_0x55_3 = true;
            }
            m_state = 8;
        }
        break;
    case 8: {
        float t = 1.0f - m_timer / 120.0f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        if (t > 1.0f) {
            t = 1.0f;
        }
        m_offsetY = t * -100.0f;
        if (t == 1.0f) {
            setVisibility(false);
            setEnableCollisionStatus(false);
            grCollisionJoint* joint = m_joint;
            if (joint != NULL) {
                joint->m_0x55_3 = false;
            }
            m_state = 7;
        }
        break;
    }
    case 7:
        if (*m_stateWork == 3) {
            setVisibility(true);
            setEnableCollisionStatus(true);
            m_timer = 180.0f;
            *m_stateWork = 4;
            m_state = 6;
        }
        break;
    case 6: {
        float t = 1.0f - m_timer / 180.0f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        if (t > 1.0f) {
            t = 1.0f;
        }
        m_offsetY = t * 100.0f + -100.0f;
        if (t == 1.0f) {
            *m_stateWork = 5;
            m_state = 1;
        }
        break;
    }
    }
}

// The platform follows the stage matrix (or the origin for the moving one), shifted by its current offset.
void grFzeroAshiba::updateCallBack(float deltaFrame) {
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
            Matrix matrix(true);
            if (m_scene == 7) {
                matrix.setIdentity();
            } else {
                matrix = *m_mtxWork;
            }
            fn_8003F074(&matrix, m_offsetX, m_offsetY, m_offsetZ);
            calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix = matrix;
        }
    }
}

// Two animations exist (0 retreat, 1 appear - HYPOTHESIS).
void grFzeroAshiba::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
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
