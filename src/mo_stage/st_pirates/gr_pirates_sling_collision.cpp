#include <gr/gr_pirates_sling.h>

void grPiratesSling::updateCollision(float deltaFrame) {
    grCollisionJoint* joint = m_collisionJoint;
    if (joint == NULL) {
        return;
    }

    switch (m_state) {
    case 4:
    case 10:
        joint->m_0x54_7 = false;
        joint->m_0x54_4 = joint->m_0x54_7;
        joint->m_0x54_6 = joint->m_0x54_4;
        break;
    default:
        joint->m_0x54_4 = true;
        joint->m_0x54_6 = joint->m_0x54_4;
        break;
    }
}
