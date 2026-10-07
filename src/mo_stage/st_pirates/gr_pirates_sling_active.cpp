#include <gr/gr_pirates_sling.h>
#include <gr/collision/gr_collision.h>
#include <ec/ec_mgr.h>
#include <mt/mt_prng.h>

struct PiratesSlingParams {
    float unk0;
    float firstWait;
    float waitMin;
    float waitMax;
    float activationProbability;
    float activeMin;
    float activeMax;
};

// MATCH-ONLY: preserve the original stage constant pool and node string.
extern const float g_piratesSlingMotionConstants[3]; // 0.0f, 60.0f, 5.0f
extern const char g_piratesSlingEffectNode[];         // StgPirates00S

void grPiratesSling::updateActive(float deltaFrame) {
    const float* constants = g_piratesSlingMotionConstants;
    PiratesSlingParams* params = static_cast<PiratesSlingParams*>(getStageData());
    if (params == NULL) {
        return;
    }
    m_timer -= deltaFrame;
    if (m_timer < constants[0]) {
        m_timer = constants[0];
    }

    switch (m_state) {
    case State_Reset:
        setMotion(1, 0, true, &m_motionEndFrame);
        setMotionFrame(m_motionEndFrame, 0);
        setEnableCollisionStatus(false);
        if (m_collision != NULL) {
            m_collision->setEnable();
        }
        if (m_firstActivation == 1) {
            m_timer = params->firstWait;
            m_firstActivation = 0;
        } else {
            float random = randf();
            float span = params->waitMax - params->waitMin;
            m_timer = params->waitMin + span * random;
        }
        m_state = State_Wait;
        break;
    case State_Wait:
        if (constants[0] != m_timer) {
            return;
        }
        switch (*m_stateWork) {
        case 5:
        case 6:
        case 8:
        case 9:
            m_state = State_Reset;
            return;
        }
        if (randf() < params->activationProbability) {
            setMotion(0, 0, true, &m_motionEndFrame);
            setEnableCollisionStatus(true);
            float random = randf();
            float span = params->activeMax - params->activeMin;
            m_timer = params->activeMin + span * random;
            unk188 = 0;
            m_state = State_Raising;
        } else {
            m_state = State_Reset;
        }
        break;
    case State_Raising:
        if (getMotionFrame(0) > constants[1]) {
            u32 handle = g_ecMgr->setEffect(ef_ptc_stg_pirates_syutugen);
            g_ecMgr->setParent(handle, m_sceneModels[0], g_piratesSlingEffectNode, false);
            m_state = State_Active;
        }
        break;
    case State_Active:
        if (constants[0] == m_timer) {
            setMotion(1, 0, true, &m_motionEndFrame);
            unk188 = 0;
            m_state = State_Lowering;
        }
        break;
    case State_Lowering:
        if (getMotionFrame(0) >= m_motionEndFrame) {
            if (m_attackEnabled == 1) {
                disableAttack(0);
                m_attackEnabled = 0;
            }
            m_state = State_Reset;
        } else if (getMotionFrame(0) <= constants[2]) {
            setAttack();
        } else if (m_attackEnabled == 1) {
            disableAttack(0);
            m_attackEnabled = 0;
        }
        break;
    }
}
