#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>
#include <gr/gr_calc_world_callback.h>
#include <snd/snd_system.h>

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
        case 1:
            m_sePlayer.playFrame(0, getMotionFrame(0));
            if (m_timer == 0.0f) {
                m_warned = 1;
            }
            if (m_lastFrame <= getMotionFrame(0)) {
                m_lastFrame = getMotionFrame(0);
            } else if (m_warned == 1) {
                setMotion(2, false, true, &m_animFrames);
                g_sndSystem->playSE(static_cast<SndID>(0x1c72), 0, 0, 0, -1);
            } else {
                m_lastFrame = getMotionFrame(0);
            }
            break;
        case 0:
            if (m_animFrames <= getMotionFrame(0)) {
                setMotion(1, true, true, &m_animFrames);
                m_lastFrame = 0.0f;
                m_sePlayer.playFrame(0, getMotionFrame(0), 0.0f);
            }
            break;
        case 2:
            if (m_animFrames <= getMotionFrame(0)) {
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
