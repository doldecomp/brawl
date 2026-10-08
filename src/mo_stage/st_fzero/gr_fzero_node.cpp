#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>
#include <gr/gr_calc_world_callback.h>
#include <memory.h>
#include <string.h>

grFzeroNode* grFzeroNode::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroNode* ground = new (Heaps::StageInstance) grFzeroNode(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroNode::grFzeroNode(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_frameSceneWork = NULL;
    m_motionTimer = 0.0f;
    m_stateWork = NULL;
    m_motionWork = NULL;
    m_motionId = 5;
    m_mtxWork = NULL;
    m_mtxGimmickWork = NULL;
    memset(m_node, 0, sizeof(m_node));
    m_animId = 5;
    m_animFrames = 0.0f;
    memset(unk1BC, 0, sizeof(unk1BC));
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 8;
}

grFzeroNode::~grFzeroNode() {
}

void grFzeroNode::processAnim() {
}

void grFzeroNode::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateActive(deltaFrame);
        updateCallBack(deltaFrame);
        updateG3dProcCalcWorld();
        m_hasUpdatedG3dCalcWorld = false;
        if (m_mtxGimmickWork != NULL) {
            getNodeMatrix(m_mtxGimmickWork + 24, 0, m_node[0]);
            getNodeMatrix(m_mtxGimmickWork + 25, 0, m_node[1]);
            getNodeMatrix(m_mtxGimmickWork + 26, 0, m_node[2]);
            getNodeMatrix(m_mtxGimmickWork + 27, 0, m_node[3]);
            getNodeMatrix(m_mtxGimmickWork + 28, 0, m_node[4]);
            getNodeMatrix(m_mtxGimmickWork + 29, 0, m_node[5]);
            getNodeMatrix(m_mtxGimmickWork + 30, 0, m_node[6]);
            getNodeMatrix(m_mtxGimmickWork + 31, 0, m_node[7]);
            getNodeMatrix(m_mtxGimmickWork + 32, 0, m_node[8]);
            getNodeMatrix(m_mtxGimmickWork + 33, 0, m_node[9]);
            getNodeMatrix(m_mtxGimmickWork + 34, 0, m_node[10]);
            getNodeMatrix(m_mtxGimmickWork + 35, 0, m_node[11]);
            getNodeMatrix(m_mtxGimmickWork + 36, 0, m_node[12]);
            getNodeMatrix(m_mtxGimmickWork + 37, 0, m_node[13]);
            getNodeMatrix(m_mtxGimmickWork + 38, 0, m_node[14]);
        }
    }
}

// The animation that belongs to a course section (5 = the parked pose).
static inline u32 grFzeroNodeMotionOfScene(u32 scene) {
    if (scene == 0) {
        scene = 1;
    } else if (scene == 2) {
        scene = 2;
    } else if (scene == 3) {
        scene = 2;
    } else if (scene == 4) {
        scene = 3;
    } else if (scene == 5) {
        scene = 4;
    } else {
        scene = (scene == 6) ? 0 : 5;
    }
    return scene;
}

void grFzeroNode::updateActive(float deltaFrame) {
    u8 state = m_state;
    m_motionTimer += deltaFrame;
    if (state == 2) {
        if (*m_stateWork == 7) {
            u32 motion = grFzeroNodeMotionOfScene(*m_sceneWork);
            setMotion(motion, 0, 1, &m_animFrames);
            *m_motionWork = motion;
            m_motionId = motion;
            m_motionTimer = 0.0f;
            m_state = 3;
        }
    } else if (state < 2) {
        if (state == 0) {
            setMotion(5, 0, 1, 0);
            m_state = 1;
        }
        u8* stateWork = m_stateWork;
        if (*stateWork == 6) {
            u32 motion = grFzeroNodeMotionOfScene(*m_sceneWork);
            bool keep = false;
            if (motion == 5) {
                keep = true;
            } else {
                u32 current = m_motionId;
                if (motion == current) {
                    keep = true;
                } else if (motion == 0) {
                    if (m_motionTimer < 3600.0f && current == 4) {
                        keep = true;
                    }
                } else if (m_motionTimer < 3600.0f && current == (u8)(motion - 1)) {
                    keep = true;
                }
            }
            if (keep) {
                *stateWork = 8;
            } else {
                *stateWork = 7;
                m_state = 2;
            }
        }
    } else if (state < 4 && !(getMotionFrame(0) < m_animFrames)) {
        setMotion(5, 0, 1, 0);
        *m_motionWork = 5;
        *m_stateWork = 8;
        m_state = 1;
    }
}

// The model follows the stage matrix.
void grFzeroNode::updateCallBack(float deltaFrame) {
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
                calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix = *m_mtxWork;
            }
        }
    }
}

bool grFzeroNode::setNode() {
    bool result = grGimmick::setNode();
    getNodeIndex(&m_node[0], 0, "FZmachine01");
    getNodeIndex(&m_node[1], 0, "FZmachine02");
    getNodeIndex(&m_node[2], 0, "FZmachine03");
    getNodeIndex(&m_node[3], 0, "FZmachine04");
    getNodeIndex(&m_node[4], 0, "FZmachine05");
    getNodeIndex(&m_node[5], 0, "FZmachine06");
    getNodeIndex(&m_node[6], 0, "FZmachine07");
    getNodeIndex(&m_node[7], 0, "FZmachine08");
    getNodeIndex(&m_node[8], 0, "FZmachine09");
    getNodeIndex(&m_node[9], 0, "FZmachine10");
    getNodeIndex(&m_node[10], 0, "FZmachine11");
    getNodeIndex(&m_node[11], 0, "FZmachine12");
    getNodeIndex(&m_node[12], 0, "FZmachine13");
    getNodeIndex(&m_node[13], 0, "FZmachine14");
    getNodeIndex(&m_node[14], 0, "FZmachine15");
    return result;
}

// Binds the animation of the machines (five of them: the four course sections and the parked pose).
void grFzeroNode::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
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

    if (animId >= 5) {
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
