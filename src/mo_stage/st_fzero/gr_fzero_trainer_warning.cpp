#include <st_fzero/gr_fzero.h>
#include <gr/gr_calc_world_callback.h>
#include <snd/snd_system.h>
#include <st_fzero/gr_fzero_anim.h>
#include <mt/mt_prng.h>

// The base class is defined first in this unit, so the Trainer and Warning constructors expand it; the other gimmick
// units call these two out of line.
grFzero::grFzero(const char* taskName) : grYakumono(taskName) {
    m_state = 0;
    m_timer = 0.0f;
    setupMelee();
}

grFzero::~grFzero() {
}

// MATCH-ONLY: the stage's node name strings ("PTposition01" .. "PTposition04", 16 bytes apart).
extern const char g_fzeroTrainerNodeNames[][16];

grFzeroTrainer* grFzeroTrainer::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroTrainer* ground = new (Heaps::StageInstance) grFzeroTrainer(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroTrainer::grFzeroTrainer(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_frameSceneWork = NULL;
    m_mtxWork = NULL;
    m_mtxIndex = 0;
    m_posTrainerWork = NULL;
    m_node[0] = 0;
    m_node[1] = 0;
    m_node[2] = 0;
    m_node[3] = 0;
    m_animId = 7;
    m_animFrames = 0.0f;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 1;
}

grFzeroTrainer::~grFzeroTrainer() {
}

void grFzeroTrainer::processAnim() {
    Ground::processAnim();
}

// Unlike the other gimmicks the trainer does not run grGimmick::update; it only refreshes its model matrices and then
// publishes the four trainer node positions.
void grFzeroTrainer::update(float deltaFrame) {
    if (m_isUpdate) {
        updatePos(deltaFrame);
        updateCallBack(deltaFrame);
        updateG3dProcCalcWorld();
        m_hasUpdatedG3dCalcWorld = false;
        if (m_posTrainerWork != NULL) {
            getNodePosition(&m_posTrainerWork[0], 0, m_node[0]);
            getNodePosition(&m_posTrainerWork[1], 0, m_node[1]);
            getNodePosition(&m_posTrainerWork[2], 0, m_node[2]);
            getNodePosition(&m_posTrainerWork[3], 0, m_node[3]);
        }
    }
}

// Picks the trainer animation for the course section the stage is in: it moves on to the next section's animation once
// the scene frame is past 120 (HYPOTHESIS: the trainer rides the camera along the course).
void grFzeroTrainer::updatePos(float deltaFrame) {
    const char (*names)[16] = g_fzeroTrainerNodeNames;
    switch (m_state) {
    case 0:
        getNodeIndex(&m_node[0], 0, names[0]);
        getNodeIndex(&m_node[1], 0, names[1]);
        getNodeIndex(&m_node[2], 0, names[2]);
        getNodeIndex(&m_node[3], 0, names[3]);
        m_state = 1;
        break;
    case 1:
        break;
    }

    bool inSection = !(*m_frameSceneWork > 120.0f);
    u8 section;
    switch (*m_sceneWork) {
    case 0:
        if (!inSection) {
            section = 1;
        } else {
            section = 0;
        }
        break;
    case 1:
        if (!inSection) {
            section = 2;
        } else {
            section = 1;
        }
        break;
    case 2:
        if (!inSection) {
            section = 3;
        } else {
            section = 2;
        }
        break;
    case 3:
        if (!inSection) {
            section = 4;
        } else {
            section = 3;
        }
        break;
    case 4:
        if (!inSection) {
            section = 5;
        } else {
            section = 4;
        }
        break;
    case 5:
        if (!inSection) {
            section = 6;
        } else {
            section = 5;
        }
        break;
    case 6:
        if (!inSection) {
            section = 0;
        } else {
            section = 6;
        }
        break;
    default:
        return;
    }

    switch (section) {
    case 0:
        m_mtxIndex = 2;
        break;
    case 1:
        m_mtxIndex = 3;
        break;
    case 2:
        m_mtxIndex = 4;
        break;
    case 3:
        m_mtxIndex = 5;
        break;
    case 4:
        m_mtxIndex = 6;
        break;
    case 5:
        m_mtxIndex = 7;
        break;
    case 6:
        m_mtxIndex = 8;
        break;
    }

    if (m_animId != section) {
        setMotion(section, false, true, &m_animFrames);
    }
}

// The model follows the stage matrix the current section selected.
void grFzeroTrainer::updateCallBack(float deltaFrame) {
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
            if (m_mtxWork != NULL) {
                Matrix* matrix = &m_mtxWork[m_mtxIndex];
                float z = matrix->m[2][3];
                float y = matrix->m[1][3];
                float x = matrix->m[0][3];
                Vec3f pos(x, y, z);
                calcWorldCallBack->m_nodeCallbackDatas[0].m_pos = pos;
            }
        }
    }
}

// Only the seven section animations exist.
void grFzeroTrainer::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    grFzeroSetMotion(this, m_animId, 7, animId, shouldLoop, force, frameCount);
}

grFzeroWarning* grFzeroWarning::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroWarning* ground = new (Heaps::StageInstance) grFzeroWarning(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroWarning::grFzeroWarning(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_frameSceneWork = NULL;
    m_stateWork = NULL;
    m_mtxGimmickWork = NULL;
    m_warned = 0;
    m_animId = 3;
    m_lastFrame = 0.0f;
    m_animFrames = 0.0f;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 1;
    m_seIds[0] = static_cast<SndID>(0x1c71);
    m_seData.id = static_cast<SndID>(0x1c71);
    m_seData.unk4 = 0.0f;
    m_seData.unk8 = 0.0f;
    m_seData.unkC = 0.0f;
    m_sePlayer.registId(m_seIds, 1);
    m_sePlayer.registSeq(0, &m_seData, 1, Heaps::StageInstance);
}

grFzeroWarning::~grFzeroWarning() {
}

void grFzeroWarning::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateActive(deltaFrame);
        updateCallBack(deltaFrame);
    }
}

// The warning waits for the stage to reach section 4, then loops its light animation with a sound sequence until the
// warning time is over and plays the closing animation (HYPOTHESIS: animation 1 loops, 2 is the closing one).
void grFzeroWarning::updateActive(float deltaFrame) {
    grFzeroWarningParam* data = (grFzeroWarningParam*)getStageData();
    if (data == NULL) {
        return;
    }

    m_timer -= deltaFrame;
    if (m_timer < 0.0f) {
        m_timer = 0.0f;
    }

    switch (m_state) {
    case 0:
        setMotion(3, false, true, NULL);
        setVisibility(false);
        m_state = 1;
        // fall through
    case 1:
        if (*m_sceneWork == 4) {
            setMotion(0, false, true, &m_animFrames);
            m_warned = 0;
            g_sndSystem->playSE(static_cast<SndID>(0x1c70), 0, 0, 0, -1);
            m_timer = data->m_warnFrames;
            m_state = 3;
        }
        break;
    case 2:
        break;
    case 3:
        if (!m_isVisible) {
            setVisibility(true);
        }
        switch (m_animId) {
        case 0:
            if (getMotionFrame(0) >= m_animFrames) {
                setMotion(1, true, true, &m_animFrames);
                m_lastFrame = 0.0f;
                m_sePlayer.playFrame(0, getMotionFrame(0), 0.0f);
            }
            break;
        case 1: {
            m_sePlayer.playFrame(0, getMotionFrame(0));
            if (m_timer == 0.0f) {
                m_warned = 1;
            }
            if (getMotionFrame(0) < m_lastFrame) {
                if (m_warned == 1) {
                    setMotion(2, false, true, &m_animFrames);
                    g_sndSystem->playSE(static_cast<SndID>(0x1c72), 0, 0, 0, -1);
                } else {
                    m_lastFrame = getMotionFrame(0);
                }
            } else {
                m_lastFrame = getMotionFrame(0);
            }
            break;
        }
        case 2:
            if (getMotionFrame(0) >= m_animFrames) {
                setMotion(3, false, true, NULL);
                m_state = 0;
            }
            break;
        }
        break;
    }
}

// The model sits at a fixed offset above and in front of its node.
void grFzeroWarning::updateCallBack(float deltaFrame) {
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
            grNodeCallbackData* callbackData = calcWorldCallBack->m_nodeCallbackDatas;
            callbackData->m_pos.m_x = 0.0f;
            callbackData->m_pos.m_y = 10.0f;
            callbackData->m_pos.m_z = -100.0f;
        }
    }
}

void grFzeroWarning::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    grFzeroSetMotion(this, m_animId, 3, animId, shouldLoop, force, frameCount);
}
