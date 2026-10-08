#include <st_greenhill/gr_greenhill.h>
#include <mt/mt_prng.h>

// MATCH-ONLY: the stage's float constant pool and node name strings.
extern const float g_greenhillBreakConstants[]; // [0] = 0.0f, [1] .. [4] timers
extern const char g_greenhillBreakNodeNames[][12]; // "DanmenBrk02", "DanmenBrk03", "DanmenBrk01"

// Drives the breakable piece: it waits a random time, breaks (hit boxes off, collision gone), stays away for a while,
// comes back blinking and then goes idle again.
void grGreenhillBreak::updateBreak(float deltaFrame) {
    const char (*names)[12] = g_greenhillBreakNodeNames;
    const float* constants = g_greenhillBreakConstants;
    grGreenhillBreakParam* data = (grGreenhillBreakParam*)getStageData();
    if (data == NULL) {
        return;
    }

    m_timer -= deltaFrame;
    if (m_timer < constants[0]) {
        m_timer = constants[0];
    }
    unk15C -= deltaFrame;
    if (unk15C < constants[0]) {
        unk15C = constants[0];
    }
    unk160 -= deltaFrame;
    if (unk160 < constants[0]) {
        unk160 = constants[0];
    }

    switch (m_state) {
    case 0:
        setMotion(1, false, true, NULL);
        setVisibility(true);
        setEnableCollisionStatus(true);
        enableHit(0, 0);
        enableHit(1, 0);
        enableHit(2, 0);
        switch (m_type) {
        case 0:
            getNodeIndex(&m_nodeA, 0, names[0]);
            getNodeIndex(&m_nodeB, 0, names[1]);
            break;
        case 1:
            getNodeIndex(&m_nodeA, 0, names[2]);
            break;
        case 2:
            getNodeIndex(&m_nodeA, 0, names[2]);
            break;
        }
        switch (m_type) {
        case 0:
            unk168[0] = 0;
            break;
        case 1:
            unk168[1] = 0;
            break;
        case 2:
            unk168[2] = 0;
            break;
        }
        *unk164 = 5;
        unk170 = data->unk10;
        m_timer = data->m_waitMin + (data->m_waitMax - data->m_waitMin) * randf();
        m_state = 1;
        break;
    case 1:
        if (constants[0] == unk15C && unk18D == 1) {
            disableAttack(0);
            disableAttack(1);
            disableAttack(2);
            unk18D = 0;
        }
        if (*unk164 == 2 || constants[0] == m_timer) {
            *unk164 = 2;
            setMotion(0, false, true, &unk178);
            disableHit(0, 0);
            disableHit(1, 0);
            disableHit(2, 0);
            switch (m_type) {
            case 0:
                unk168[0] = 1;
                break;
            case 1:
                unk168[1] = 1;
                break;
            case 2:
                unk168[2] = 1;
                break;
            }
            m_timer = constants[1];
            startGimmickSE(0);
            m_state = 2;
        }
        break;
    case 2:
        if (constants[0] == m_timer) {
            setEnableCollisionStatus(false);
            m_timer = data->unk2C;
            m_state = 3;
        }
        break;
    case 3:
        if (m_timer <= data->unk30) {
            setMotion(1, false, true, NULL);
            setEnableCollisionStatus(true);
            setAttack();
            m_state = 4;
            unk158 = constants[2];
        }
        break;
    case 4:
        if (constants[0] == m_timer) {
            m_state = 0;
            unk15C = constants[3];
        } else {
            unk158 -= deltaFrame;
            if (unk158 < constants[0]) {
                unk158 = constants[0];
            }
            if (unk158 > constants[4]) {
                setVisibility(true);
            } else {
                setVisibility(false);
            }
            if (constants[0] == unk158) {
                unk158 = constants[2];
            }
        }
        break;
    }
}
