#include <st_fzero/gr_fzero.h>
#include <gr/gr_calc_world_callback.h>
#include <gf/gf_model.h>
#include <mt/mt_prng.h>

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

    if (animId >= 7) {
        return;
    }

    bool result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if (result) {
        setChrAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if (result) {
        setVisibilityAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if (result) {
        setTexPatAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if (result) {
        setTexSortAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if (result) {
        setColorAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoop(shouldLoop);

    if (frameCount != NULL) {
        *frameCount = modelAnim->getFrameCount();
    }
}
