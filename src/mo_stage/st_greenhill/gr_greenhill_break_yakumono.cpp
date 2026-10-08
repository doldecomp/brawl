#include <st_greenhill/gr_greenhill.h>
#include <gr/collision/gr_collision.h>

// Finds the collision joint this object owns the first time it exists.
void grGreenhillBreak::updateJoint(float deltaFrame) {
    if (m_joint == NULL) {
        grCollision* collision = m_collision;
        if (collision != NULL) {
            u32 jointNum = (u16)collision->m_jointLen;
            u32 i;
            grCollisionJoint* joint;
            for (i = 0; i != jointNum; i++) {
                joint = collision->getJoint(i);
                if (joint != NULL && joint->m_ground == this) {
                    break;
                }
            }
            if (i != jointNum) {
                m_joint = joint;
            }
        }
    }
}

// Shows or hides the broken/whole model pieces according to the shared break info (type 0: both halves, 1 and 2: one
// piece) and tells the collision joint which ledges are gone.
void grGreenhillBreak::updateYakumono(float deltaFrame) {
    if (unk18C == 1) {
        if (m_joint != NULL) {
            u16 ledgeFlags = 0;
            switch (m_type) {
            case 0:
                if (unk168[1] == 1) {
                    setNodeVisibility(true, 0, m_nodeA, true, false);
                } else {
                    setNodeVisibility(false, 0, m_nodeA, true, false);
                    ledgeFlags |= 0x2000;
                }
                if (unk168[2] == 1) {
                    setNodeVisibility(true, 0, m_nodeB, true, false);
                } else {
                    setNodeVisibility(false, 0, m_nodeB, true, false);
                    ledgeFlags |= 0x4000;
                }
                break;
            case 1:
                if (unk168[0] == 1) {
                    setNodeVisibility(true, 0, m_nodeA, true, false);
                } else {
                    setNodeVisibility(false, 0, m_nodeA, true, false);
                    ledgeFlags |= 0x4000;
                }
                break;
            case 2:
                if (unk168[0] == 1) {
                    setNodeVisibility(true, 0, m_nodeA, true, false);
                } else {
                    setNodeVisibility(false, 0, m_nodeA, true, false);
                    ledgeFlags |= 0x2000;
                }
                break;
            }
            m_joint->m_0x52 = ledgeFlags;
        }
    } else {
        setHit();
        if (m_yakumono != NULL) {
            unk18C = 1;
        }
    }
}
