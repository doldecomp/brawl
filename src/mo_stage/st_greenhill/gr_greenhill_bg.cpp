#include <st_greenhill/gr_greenhill.h>
#include <gr/collision/gr_collision.h>
#include <memory.h>
#include <string.h>

// MATCH-ONLY: node names of the stage backdrop, in the order the stage's constant pool keeps them:
//   +0x00 markerPosition01  +0x14 markerPosition02  +0x28 markerPosition03  +0x3C markerPosition04
//   +0x50 DanmenBrk02  +0x5C DanmenBrk03  +0x68 GHcol_collision  +0x78 flower  +0x80 himawari
extern const char g_greenhillNodeNames[];

grGreenhill::grGreenhill(const char* taskName) : grYakumono(taskName) {
    m_state = 0;
    m_timer = 0.0f;
    setupMelee();
}

grGreenhill::~grGreenhill() { }

grGreenhillBg* grGreenhillBg::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grGreenhillBg* ground = new (Heaps::StageInstance) grGreenhillBg(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

inline grGreenhillBg::grGreenhillBg(const char* taskName) : grGreenhill(taskName) {
    m_posGimmickWork = NULL;
    m_breakInfo = NULL;
    memset(m_node, 0, sizeof(m_node));
    m_joint[0] = NULL;
    m_joint[1] = NULL;
    m_joint[2] = NULL;
    m_joint[3] = NULL;
    m_joint[4] = NULL;
    m_joint[5] = NULL;
    m_joint[6] = NULL;
}

grGreenhillBg::~grGreenhillBg() { }

// The four marker positions are re-read from the model every frame.
void grGreenhillBg::processAnim() {
    const char* names = g_greenhillNodeNames;
    Ground::processAnim();
    if (m_posGimmickWork != NULL) {
        getNodePosition(&m_posGimmickWork[0], 0, names + 0x00);
        getNodePosition(&m_posGimmickWork[1], 0, names + 0x14);
        getNodePosition(&m_posGimmickWork[2], 0, names + 0x28);
        getNodePosition(&m_posGimmickWork[3], 0, names + 0x3C);
    }
}

void grGreenhillBg::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateJoint(deltaFrame);
        updateHang(deltaFrame);
    }
}

// MATCH-ONLY: the original flips three bits of the joint's flag byte as a chain (HYPOTHESIS: they track "enabled").
static inline void grGreenhillJointEnable(grCollisionJoint* joint) {
    joint->m_0x54_4 = true;
    joint->m_0x54_6 = joint->m_0x54_4;
}

static inline void grGreenhillJointDisable(grCollisionJoint* joint) {
    joint->m_0x54_7 = false;
    joint->m_0x54_4 = joint->m_0x54_7;
    joint->m_0x54_6 = joint->m_0x54_4;
}

// Collects this object's collision joints by node index the first time they exist and puts them to sleep.
void grGreenhillBg::updateJoint(float deltaFrame) {
    if (m_joint[0] == NULL && m_state != 0) {
        grCollision* collision = m_collision;
        if (collision != NULL) {
            u32 jointNum = (u16)collision->m_jointLen;
            for (u32 i = 0; i != jointNum; i++) {
                grCollisionJoint* joint = collision->getJoint(i);
                if (joint != NULL && joint->m_ground == this) {
                    u16 node = joint->m_nodeIndex;
                    if (m_node[3] == node) {
                        m_joint[0] = joint;
                    } else if (m_node[4] == node) {
                        m_joint[1] = joint;
                    } else if (m_node[5] == node) {
                        m_joint[2] = joint;
                    } else if (m_node[6] == node) {
                        m_joint[3] = joint;
                    } else if (m_node[7] == node) {
                        m_joint[4] = joint;
                    } else if (m_node[8] == node) {
                        m_joint[5] = joint;
                    } else if (m_node[2] == node) {
                        m_joint[6] = joint;
                    }
                }
            }
            for (int i = 0; i < 6; i++) {
                if (m_joint[i] != NULL) {
                    m_joint[i]->m_0x56_7 = true;
                    grGreenhillJointDisable(m_joint[i]);
                }
            }
        }
    }
}

// Keeps the two breakable hang pieces (state 1 / 2 of the shared break info) and the ledges around them in sync.
void grGreenhillBg::updateHang(float deltaFrame) {
    const char* names = g_greenhillNodeNames;
    if (m_breakInfo == NULL) {
        return;
    }
    switch (m_state) {
    case 0:
        getNodeIndex(&m_node[0], 0, names + 0x50);
        getNodeIndex(&m_node[1], 0, names + 0x5C);
        getNodeIndex(&m_node[2], 0, names + 0x68);
        getNodeIndex(&m_node[3], 0, names + 0x78);
        getNodeIndex(&m_node[4], 0, names + 0x00);
        getNodeIndex(&m_node[5], 0, names + 0x14);
        getNodeIndex(&m_node[6], 0, names + 0x28);
        getNodeIndex(&m_node[7], 0, names + 0x3C);
        getNodeIndex(&m_node[8], 0, names + 0x80);
        m_state = 1;
        // fall through
    case 1:
        if (m_joint[0] != NULL) {
            u16 ledgeFlags = 0;
            if (m_breakInfo[0] == 1) {
                if (m_breakInfo[1] != 1) {
                    grGreenhillJointEnable(m_joint[2]);
                } else {
                    grGreenhillJointDisable(m_joint[2]);
                }
                if (m_breakInfo[2] != 1) {
                    grGreenhillJointEnable(m_joint[3]);
                } else {
                    grGreenhillJointDisable(m_joint[3]);
                }
            } else {
                grGreenhillJointDisable(m_joint[2]);
                grGreenhillJointDisable(m_joint[3]);
            }
            if (m_breakInfo[1] == 1) {
                setNodeVisibility(true, 0, m_node[0], true, false);
                grGreenhillJointEnable(m_joint[0]);
                if (m_breakInfo[0] != 1) {
                    grGreenhillJointEnable(m_joint[1]);
                } else {
                    grGreenhillJointDisable(m_joint[1]);
                }
            } else {
                setNodeVisibility(false, 0, m_node[0], true, false);
                ledgeFlags |= 0x4000;
                grGreenhillJointDisable(m_joint[0]);
                grGreenhillJointDisable(m_joint[1]);
            }
            if (m_breakInfo[2] == 1) {
                setNodeVisibility(true, 0, m_node[1], true, false);
                if (m_breakInfo[0] != 1) {
                    grGreenhillJointEnable(m_joint[4]);
                } else {
                    grGreenhillJointDisable(m_joint[4]);
                }
                grGreenhillJointEnable(m_joint[5]);
            } else {
                setNodeVisibility(false, 0, m_node[1], true, false);
                ledgeFlags |= 0x2000;
                grGreenhillJointDisable(m_joint[4]);
                grGreenhillJointDisable(m_joint[5]);
            }
            m_joint[6]->m_0x52 = ledgeFlags;
        }
        break;
    }
}
