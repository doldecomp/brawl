#include <gr/gr_pirates_tornado.h>
#include <so/so_world.h>

// MATCH-ONLY: preserve the original shared constant pool.
extern const float g_piratesTornadoConstants[];

void grPiratesTornado::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        m_ctrlFrameAdvanced = 0;
        if (m_timer < *m_ctrlFrame) m_ctrlFrameAdvanced = 1;
        m_timer = *m_ctrlFrame;
        updateMotion(deltaFrame);
        updateSE(deltaFrame);
        updateCallBack(deltaFrame);
    }
}

void grPiratesTornado::updateMotion(float deltaFrame) {
    const float* constants = g_piratesTornadoConstants;
    if (m_stateWork == NULL) return;
    m_motionTimer -= deltaFrame;
    if (m_motionTimer < constants[0]) m_motionTimer = constants[0];
    switch (m_state) {
    case 0:
        setMotion(1, 0, true, NULL);
        setVisibility(false);
        // Reset restores both global gravity multipliers.
        g_soWorld->m_gravityUp = constants[1];
        g_soWorld->m_gravityDown = constants[1];
        m_reducedGravity = 0;
        m_state = 1;
        // Fall through: process the current ship event after resetting.
    case 1:
        if (m_ctrlFrameAdvanced == 1) {
            u32 motion = 1;
            u32 loop = 1;
            switch (m_motionId) {
            case 0:
                --m_motionPhase;
                switch (m_motionPhase) {
                case 0:
                    m_state = 0;
                    break;
                case 1:
                    if (*m_ctrlFrame > constants[2]) {
                        g_soWorld->m_gravityUp = constants[3];
                        g_soWorld->m_gravityDown = constants[3];
                        m_reducedGravity = 1;
                    } else {
                        g_soWorld->m_gravityUp = constants[1];
                        g_soWorld->m_gravityDown = constants[1];
                        m_reducedGravity = 0;
                    }
                    break;
                }
            }
            if (*m_stateWork != m_previousShipState) {
                switch (*m_stateWork) {
                case 6:
                    // Ship event 6 starts the tornado appearance sequence.
                    m_motionPhase = 3;
                    motion = 0;
                    setVisibility(true);
                    break;
                }
                if (motion != 1) loop = 0;
                m_previousShipState = *m_stateWork;
            }
            if (motion != 1) {
                setMotion(motion, loop, true, &m_motionTimer);
                setMotionFrame(constants[4] - *m_ctrlFrame, 0);
                unk184 = 0;
            }
        } else {
            switch (m_motionPhase) {
            case 1:
                if (*m_ctrlFrame > constants[2]) {
                    g_soWorld->m_gravityUp = constants[3];
                    g_soWorld->m_gravityDown = constants[3];
                    m_reducedGravity = 1;
                } else {
                    g_soWorld->m_gravityUp = constants[1];
                    g_soWorld->m_gravityDown = constants[1];
                    m_reducedGravity = 0;
                }
                break;
            }
        }
        break;
    }
}
