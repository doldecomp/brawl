#include <gr/gr_pirates_sling.h>

extern const float g_piratesSlingMotionConstants[];

void grPiratesSling::setAttack() {
    const float* constants = g_piratesSlingMotionConstants;
    if (m_attackEnabled == 1) {
        return;
    }

    soCollisionAttackData attack(constants[10]);
    Vec3f offset(constants[0], constants[20], constants[0]);

    setAttackGimmickDetails(&attack, constants[21], constants[10], constants[10], constants[10],
        0, &offset, 20, 15, 0, 150, m_nodeIndex,
        soCollision::CATEGORY_MASK_ALL, 7, false, 15,
        soCollisionAttackData::Attribute_Normal, soCollisionAttackData::Sound_Level_Medium,
        soCollisionAttackData::Sound_Attribute_None,
        false, false, false, true, false, false, 0, 60,
        false, false, false, soCollisionAttackData::Lr_Check_Forward,
        false, false, true, false, false, soCollisionAttackData::Region_None, false);
    m_yakumono->setAttack(0, 0, &attack);
    m_yakumono->setLr(constants[19]);
    m_attackEnabled = 1;
}
