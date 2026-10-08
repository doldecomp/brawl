#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>
#include <gr/collision/gr_collision.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/math/math_arithmetic.h>
#include <nw4r/math/math_triangular.h>
#include <snd/snd_system.h>
#include <string.h>
#include <gm/gm_global.h>

grFzeroBg* grFzeroBg::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroBg* ground = new (Heaps::StageInstance) grFzeroBg(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

// MATCH-ONLY: the original reads the game mode of gmGlobalModeMelee's init data (bits 7..2 of byte 8) with a byte load.
struct fzeroBgModeByte {
    u8 m_mode : 6;
    u8 : 2;
};

grFzeroBg::grFzeroBg(const char* taskName) : grFzero(taskName) {
    m_phase = 0;
    m_count = 0;
    m_sceneWork = NULL;
    m_frameSceneWork = NULL;
    m_stateWork = NULL;
    m_carMotionWork = NULL;
    m_unk16C = true;
    m_unk16D = true;
    m_mtxGimmickWork = NULL;
    memset(m_nodeHaikei, 0, sizeof(m_nodeHaikei));
    memset(m_nodeAsiba, 0, sizeof(m_nodeAsiba));
    memset(m_nodeDplate, 0, sizeof(m_nodeDplate));
    memset(&m_nodeDplateRing, 0, sizeof(m_nodeDplateRing));
    memset(&m_nodeCourseStart, 0, sizeof(m_nodeCourseStart));
    memset(m_nodeCourseCol, 0, sizeof(m_nodeCourseCol));
    m_joint[0] = NULL;
    m_joint[1] = NULL;
    m_joint[2] = NULL;
    m_joint[3] = NULL;
    m_joint[4] = NULL;
    m_joint[5] = NULL;
    m_joint[6] = NULL;
    m_motionRate = 1.0f;
    m_animId = 7;
    m_unk1F8 = 0.0f;
    m_frameLimit = 0.0f;
    m_seIndex = 0;
    m_seHandle = -1;
    m_isEvent = false;
    gmGlobalModeMelee* melee = g_GameGlobal->m_modeMelee;
    if (melee == NULL) {
        return;
    }
    if (((fzeroBgModeByte*)((u8*)melee + 8))->m_mode != 7) {
        return;
    }
    if (*((u8*)melee + 0x10) == 0x1f) {
        m_isEvent = true;
    }
}

grFzeroBg::~grFzeroBg() {
}

// MATCH-ONLY: the original flips the same bits of the joint's flag byte as a chain (HYPOTHESIS: they track "enabled").
static inline void grFzeroJointEnable(grCollisionJoint* joint) {
    joint->m_0x54_4 = true;
    joint->m_0x54_6 = joint->m_0x54_4;
}

static inline void grFzeroJointDisable(grCollisionJoint* joint) {
    joint->m_0x54_7 = false;
    joint->m_0x54_4 = joint->m_0x54_7;
    joint->m_0x54_6 = joint->m_0x54_4;
}

// HYPOTHESIS: the same fsel based clamp helper the glide statuses use.
static inline float fzeroClamp(float value, float lo, float hi) {
    value = nw4r::math::FSelect(value - lo, value, lo);
    return nw4r::math::FSelect(value - hi, hi, value);
}

void grFzeroBg::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateJoint(deltaFrame);
        updateScene(deltaFrame);
        updateSceneMotion(deltaFrame);
        updateSE(deltaFrame);
        updateG3dProcCalcWorld();
        m_hasUpdatedG3dCalcWorld = false;
        if (m_mtxGimmickWork != NULL) {
            getNodeMatrix(m_mtxGimmickWork, 0, m_nodeHaikei[0]);
            getNodeMatrix(m_mtxGimmickWork + 1, 0, m_nodeHaikei[1]);
            getNodeMatrix(m_mtxGimmickWork + 2, 0, m_nodeAsiba[0]);
            getNodeMatrix(m_mtxGimmickWork + 3, 0, m_nodeAsiba[1]);
            getNodeMatrix(m_mtxGimmickWork + 4, 0, m_nodeAsiba[2]);
            getNodeMatrix(m_mtxGimmickWork + 5, 0, m_nodeAsiba[3]);
            getNodeMatrix(m_mtxGimmickWork + 6, 0, m_nodeAsiba[4]);
            getNodeMatrix(m_mtxGimmickWork + 7, 0, m_nodeAsiba[5]);
            getNodeMatrix(m_mtxGimmickWork + 8, 0, m_nodeAsiba[6]);
            getNodeMatrix(m_mtxGimmickWork + 9, 0, m_nodeDplate[0]);
            getNodeMatrix(m_mtxGimmickWork + 10, 0, m_nodeDplate[1]);
            getNodeMatrix(m_mtxGimmickWork + 11, 0, m_nodeDplate[2]);
            getNodeMatrix(m_mtxGimmickWork + 12, 0, m_nodeDplate[3]);
            getNodeMatrix(m_mtxGimmickWork + 13, 0, m_nodeDplate[4]);
            getNodeMatrix(m_mtxGimmickWork + 14, 0, m_nodeDplate[5]);
            getNodeMatrix(m_mtxGimmickWork + 15, 0, m_nodeDplate[6]);
            getNodeMatrix(m_mtxGimmickWork + 16, 0, m_nodeDplate[7]);
            getNodeMatrix(m_mtxGimmickWork + 17, 0, m_nodeDplate[8]);
            getNodeMatrix(m_mtxGimmickWork + 18, 0, m_nodeDplate[9]);
            getNodeMatrix(m_mtxGimmickWork + 19, 0, m_nodeDplate[10]);
            getNodeMatrix(m_mtxGimmickWork + 20, 0, m_nodeDplateRing);
            getNodeMatrix(m_mtxGimmickWork + 21, 0, m_nodeCourseStart);
            getNodeMatrix(m_mtxGimmickWork + 22, 0, m_nodeCourseCol[0]);
            getNodeMatrix(m_mtxGimmickWork + 23, 0, m_nodeCourseCol[1]);
        }
    }
}

// Collects the seven collision joints of the backdrop the first time all of them exist.
void grFzeroBg::updateJoint(float deltaFrame) {
    if ((m_joint[0] == NULL || m_joint[1] == NULL || m_joint[2] == NULL || m_joint[3] == NULL || m_joint[4] == NULL ||
         m_joint[5] == NULL || m_joint[6] == NULL) &&
        m_collision != NULL) {
        grCollision* collision = m_collision;
        m_joint[0] = collision->getJoint(0);
        m_joint[1] = collision->getJoint(1);
        m_joint[2] = collision->getJoint(2);
        m_joint[3] = collision->getJoint(3);
        m_joint[4] = collision->getJoint(4);
        m_joint[5] = collision->getJoint(5);
        m_joint[6] = collision->getJoint(6);
    }
}

void grFzeroBg::updateScene(float deltaFrame) {
    switch (m_state) {
    case 2:
        break;
    case 0:
        setMotion(0, 0, 0, 0);
        m_unk1F8 = 0.0f;
        m_frameLimit = getMotionTotalFrame(0);
        *m_sceneWork = 0;
        *m_stateWork = 0;
        m_timer = 120.0f;
        m_unk16C = true;
        m_state = 1;
        break;
    case 1: {
        grCollision* collision = m_collision;
        if (collision != NULL) {
            u32 jointLen = (u16)collision->m_jointLen;
            for (u32 i = 0; i != jointLen; i++) {
                grCollisionJoint* joint = collision->getJoint(i);
                if (joint != NULL) {
                    joint->m_0x56_7 = true;
                    grFzeroJointDisable(joint);
                }
            }
            m_state = 3;
        }
        break;
    }
    }
}

// Drives the course section animation: it waits on the section's timer, plays the section animation forwards until its
// frame limit, then hands over to the next section (the joints of the next section's platform are enabled while it
// slides in).
void grFzeroBg::updateSceneMotion(float deltaFrame) {
    if (m_stateWork == NULL) {
        return;
    }
    grFzeroBgData* data = (grFzeroBgData*)getStageData();
    if (data == NULL) {
        return;
    }
    m_timer -= deltaFrame;
    if (m_timer < 0.0f) {
        m_timer = 0.0f;
    }
    switch (*m_stateWork) {
    case 0:
        switch (m_phase) {
        case 0:
            m_phase = 1;
            // fall through
        case 1: {
            bool replay = false;
            if (m_isEvent == true) {
                m_phase = 7;
            } else {
                if (randf() > data->m_chance || m_count == 3) {
                    replay = true;
                } else if (*m_carMotionWork == 2 && m_animId == 3) {
                    replay = true;
                }
            }
            if (replay == true) {
                m_count = 0;
                m_timer = 120.0f;
                m_motionRate = 1.0f;
                m_seHandle = -1;
                m_phase = 2;
            } else {
                m_phase = 5;
                m_count++;
            }
            break;
        }
        case 2:
            if (m_seHandle == -1 && getMotionFrame(0) >= m_frameLimit - 60.0f) {
                m_seHandle = g_sndSystem->playSE(static_cast<SndID>(0x1c6f), 0, 0, 0, -1);
            }
            if (getMotionFrame(0) >= m_frameLimit - 120.0f) {
                float hi = 1.0f;
                float lo = 0.0f;
                float clamped = fzeroClamp(hi - m_timer / 120.0f, lo, hi);
                float value = 1.0f - nw4r::math::SinIdx((u16)(int)(clamped * 16384.0f));
                m_motionRate = 1.0f;
                setMotionFrame(m_frameLimit - value * 120.0f, 0);
                if (value == 0.0f) {
                    m_phase = 3;
                }
            } else {
                m_timer = 120.0f;
                m_motionRate = 1.0f;
            }
            break;
        case 4:
            if (getMotionFrame(0) <= 120.0f) {
                float hi = 1.0f;
                float lo = 0.0f;
                float clamped = fzeroClamp(hi - m_timer / 120.0f, lo, hi);
                m_motionRate = 1.0f;
                float value = 1.0f - nw4r::math::CosFIdx(NW4R_MATH_IDX_TO_FIDX(nw4r::math::U16ToF32((u16)(int)(clamped * 16384.0f))));
                setMotionFrame(value * 120.0f, 0);
                if (value == 1.0f) {
                    m_phase = 1;
                }
            } else {
                m_timer = 120.0f;
                m_motionRate = 1.0f;
            }
            break;
        case 5:
            if (*m_sceneWork == 5 && m_joint[6] != NULL && m_joint[6]->m_0x54_6 == false) {
                grFzeroJointEnable(m_joint[6]);
                m_joint[6]->m_0x55_3 = true;
            }
            break;
        }
        break;
    case 1: {
        *m_stateWork = 2;
        m_timer = data->m_minWait + (data->m_maxWait - data->m_minWait) * randf();
        int next = *m_sceneWork + 1;
        if (next == 7) {
            next = 0;
        }
        if (m_joint[next] != NULL) {
            grFzeroJointEnable(m_joint[next]);
            m_joint[next]->m_0x55_3 = false;
        }
        break;
    }
    case 2:
        if (m_timer == 0.0f && (m_animId == 2 || *m_carMotionWork == 5)) {
            int next = *m_sceneWork + 1;
            if (next == 7) {
                next = 0;
            }
            grCollisionJoint* joint = m_joint[next];
            if (joint != NULL) {
                joint->m_0x55_3 = true;
            }
            *m_stateWork = 3;
        }
        break;
    case 5: {
        *m_stateWork = 0;
        m_timer = 120.0f;
        m_motionRate = 1.0f;
        m_phase = 4;
        g_sndSystem->playSE(static_cast<SndID>(0x1c6e), 0, 0, 0, -1);
        int next = *m_sceneWork + 1;
        if (next == 7) {
            next = 0;
        }
        if (next != 6) {
            if (m_joint[next] != NULL) {
                grFzeroJointDisable(m_joint[next]);
                m_joint[next]->m_0x55_3 = false;
            }
        }
        break;
    }
    }

    if (*m_sceneWork == 6 && m_joint[6] != NULL && m_joint[6]->m_0x54_6 == true && getMotionFrame(0) >= 60.0f) {
        grFzeroJointDisable(m_joint[6]);
        m_joint[6]->m_0x55_3 = false;
    }

    if (getMotionFrame(0) >= m_frameLimit && *m_stateWork == 0) {
        m_unk16C = false;
        switch (m_phase) {
        case 3:
            *m_stateWork = 1;
            m_motionRate = 0.0f;
            break;
        case 4:
        case 5:
        case 7:
            switch (m_animId) {
            case 0:
                *m_sceneWork = 1;
                break;
            case 1:
                *m_sceneWork = 2;
                break;
            case 2:
                *m_sceneWork = 3;
                break;
            case 3:
                *m_sceneWork = 4;
                break;
            case 4:
                *m_sceneWork = 5;
                break;
            case 5:
                *m_sceneWork = 6;
                break;
            case 6:
                *m_sceneWork = 0;
                break;
            }
            switch (*m_sceneWork) {
            case 0:
                setMotion(0, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 1:
                setMotion(1, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 2:
                setMotion(2, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 3:
                setMotion(3, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 4:
                setMotion(4, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 5:
                setMotion(5, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            case 6:
                setMotion(6, 0, 0, 0);
                m_frameLimit = getMotionTotalFrame(0);
                m_seIndex = 0;
                break;
            }
            if (m_phase != 7) {
                m_phase = 1;
                m_timer = 120.0f;
                setMotionFrame(0.0f, 0);
            }
        }
    }
    *m_frameSceneWork = getMotionFrame(0);
}

// Plays the sound effects of the current section when its animation reaches the marked frames: "course pass" effects for
// the cars rushing by, "mark pass" effects for the signs.
void grFzeroBg::updateSE(float deltaFrame) {
    switch (m_animId) {
    case 0:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 50.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 1:
            if (!(getMotionFrame(0) < 155.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 2:
            if (!(getMotionFrame(0) < 195.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 3:
            if (!(getMotionFrame(0) < 238.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 4:
            if (!(getMotionFrame(0) < 280.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 5:
            if (!(getMotionFrame(0) < 320.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 1:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 185.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 2:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 260.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 3:
        switch (m_seIndex) {
        case 1:
            if (!(getMotionFrame(0) < 504.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 0:
            if (!(getMotionFrame(0) < 415.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 4:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 64.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 1:
            if (!(getMotionFrame(0) < 82.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 2:
            if (!(getMotionFrame(0) < 270.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 3:
            if (!(getMotionFrame(0) < 285.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 4:
            if (!(getMotionFrame(0) < 300.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 5:
            if (!(getMotionFrame(0) < 315.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 6:
            if (!(getMotionFrame(0) < 330.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 7:
            if (!(getMotionFrame(0) < 350.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 5:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 3.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 1:
            if (!(getMotionFrame(0) < 22.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 2:
            if (!(getMotionFrame(0) < 43.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 3:
            if (!(getMotionFrame(0) < 65.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 4:
            if (!(getMotionFrame(0) < 90.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 5:
            if (!(getMotionFrame(0) < 330.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 6:
            if (!(getMotionFrame(0) < 360.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 7:
            if (!(getMotionFrame(0) < 440.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 8:
            if (!(getMotionFrame(0) < 510.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        case 9:
            if (!(getMotionFrame(0) < 586.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        }
        break;
    case 6:
        switch (m_seIndex) {
        case 0:
            if (!(getMotionFrame(0) < 70.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 1:
            if (!(getMotionFrame(0) < 233.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 2:
            if (!(getMotionFrame(0) < 288.0f)) {
                playSEMarkPass();
                m_seIndex++;
            }
            break;
        case 3:
            if (!(getMotionFrame(0) < 376.0f)) {
                playSECoursePass();
                m_seIndex++;
            }
            break;
        }
        break;
    }
}

bool grFzeroBg::setNode() {
    bool result = grGimmick::setNode();
    getNodeIndex(&m_nodeHaikei[0], 0, "haikei_A_rotate");
    getNodeIndex(&m_nodeHaikei[1], 0, "haikei_A_trans");
    getNodeIndex(&m_nodeAsiba[0], 0, "L_asiba01");
    getNodeIndex(&m_nodeAsiba[1], 0, "L_asiba02");
    getNodeIndex(&m_nodeAsiba[2], 0, "L_asiba03");
    getNodeIndex(&m_nodeAsiba[3], 0, "L_asiba04");
    getNodeIndex(&m_nodeAsiba[4], 0, "L_asiba05");
    getNodeIndex(&m_nodeAsiba[5], 0, "L_asiba06");
    getNodeIndex(&m_nodeAsiba[6], 0, "L_asiba07");
    getNodeIndex(&m_nodeDplate[0], 0, "L_Dplate_a");
    getNodeIndex(&m_nodeDplate[1], 0, "L_Dplate_b");
    getNodeIndex(&m_nodeDplate[2], 0, "L_Dplate_c");
    getNodeIndex(&m_nodeDplate[3], 0, "L_Dplate_d");
    getNodeIndex(&m_nodeDplate[4], 0, "L_Dplate_e");
    getNodeIndex(&m_nodeDplate[5], 0, "L_Dplate_f");
    getNodeIndex(&m_nodeDplate[6], 0, "L_Dplate_g");
    getNodeIndex(&m_nodeDplate[7], 0, "L_Dplate_h");
    getNodeIndex(&m_nodeDplate[8], 0, "L_Dplate_i");
    getNodeIndex(&m_nodeDplate[9], 0, "L_Dplate_j");
    getNodeIndex(&m_nodeDplate[10], 0, "L_Dplate_k");
    getNodeIndex(&m_nodeDplateRing, 0, "Dplate_e_ring");
    getNodeIndex(&m_nodeCourseStart, 0, "courseStart");
    getNodeIndex(&m_nodeCourseCol[0], 0, "courseColN01");
    getNodeIndex(&m_nodeCourseCol[1], 0, "courseColN02");
    return result;
}

void grFzeroBg::playSECoursePass() {
    float r = randf();
    SndID id;
    if (r < 0.25f) {
        id = static_cast<SndID>(0x1c74);
    } else if (r < 0.5f) {
        id = static_cast<SndID>(0x1c75);
    } else if (r < 0.75f) {
        id = static_cast<SndID>(0x1c76);
    } else {
        id = static_cast<SndID>(0x1c77);
    }
    g_sndSystem->playSE(id, 0, 0, 0, -1);
}

void grFzeroBg::playSEMarkPass() {
    float r = randf();
    SndID id;
    if (r < 0.25f) {
        id = static_cast<SndID>(0x1c78);
    } else if (r < 0.5f) {
        id = static_cast<SndID>(0x1c79);
    } else if (r < 0.75f) {
        id = static_cast<SndID>(0x1c7a);
    } else {
        id = static_cast<SndID>(0x1c7b);
    }
    g_sndSystem->playSE(id, 0, 0, 0, -1);
}

// Binds the character and visibility animations of the course sections (seven of them); the sections only have those
// two kinds.
void grFzeroBg::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
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
    m_animId = animId;

    if (animId >= 7) {
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

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoopNode(shouldLoop);
    modelAnim->setLoopVisible(shouldLoop);

    if (frameCount != NULL) {
        *frameCount = modelAnim->m_anmObjChrRes->m_anmChrFile->m_animLength;
    }
}

void grFzeroBg::setMotionFrame(float frame, u32 sceneModelIndex) {
    gfModelAnimation* modelAnim = m_modelAnims[sceneModelIndex];
    if (modelAnim != NULL) {
        modelAnim->m_anmObjChrRes->SetFrame(frame);
        modelAnim->m_anmObjVisRes->SetFrame(frame);
    }
}

float grFzeroBg::getMotionFrame(u32 sceneModelIndex) {
    gfModelAnimation* modelAnim = m_modelAnims[sceneModelIndex];
    if (modelAnim == NULL) {
        return 0.0f;
    }
    return modelAnim->m_anmObjChrRes->GetFrame();
}

float grFzeroBg::getMotionTotalFrame(u32 sceneModelIndex) {
    gfModelAnimation* modelAnim = m_modelAnims[sceneModelIndex];
    if (modelAnim == NULL) {
        return 0.0f;
    }
    return modelAnim->m_anmObjChrRes->m_anmChrFile->m_animLength;
}
