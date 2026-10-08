#include <st_greenhill/gr_greenhill.h>

// MATCH-ONLY: the stage's float constant pool.
extern const float g_greenhillBreakConstants[]; // [19] = 0.0f

// One of the three hitboxes of the piece: its offset along the piece depends on the index and on which way the piece
// is mounted (m_type), the box is centred on the node in unk184.
void grGreenhillBreak::setAttack(int index) {
    const float* constants = g_greenhillBreakConstants;
    soCollisionAttackData attack(constants[19]);
    Vec3f offset;
    getNodePosition(&offset, 0, unk184);

    switch (index) {
    case 0:
        offset.m_x = constants[10];
        offset.m_y = constants[11];
        offset.m_z = -offset.m_z;
        break;
    case 1:
        offset.m_x = constants[0];
        offset.m_y = constants[11];
        offset.m_z = -offset.m_z;
        break;
    case 2:
        offset.m_x = constants[12];
        offset.m_y = constants[11];
        offset.m_z = -offset.m_z;
        break;
    }

    switch (m_type) {
    case 0:
        if (index == 0) {
            offset.m_y = constants[13];
        } else if (index == 1) {
            offset.m_y = constants[14];
        } else if (index == 2) {
            offset.m_y = constants[13];
        }
        break;
    case 1:
        if (index == 0) {
            offset.m_y = constants[15];
        } else if (index == 1) {
            offset.m_y = constants[16];
        } else if (index == 2) {
            offset.m_y = constants[17];
        }
        break;
    case 2:
        if (index == 0) {
            offset.m_y = constants[17];
        } else if (index == 1) {
            offset.m_y = constants[16];
        } else if (index == 2) {
            offset.m_y = constants[15];
        }
        break;
    }

    float zero = constants[19];
    setAttackGimmickDetails(&attack, constants[12], zero, zero, zero,
        0, &offset, 90, 50, 100, 80, unk184,
        0x3FF, 7, false, 15,
        soCollisionAttackData::Attribute_Normal, soCollisionAttackData::Sound_Level_Medium,
        soCollisionAttackData::Sound_Attribute_None,
        false, false, false, false, false, false, 0, 60,
        false, false, false, soCollisionAttackData::Lr_Check_Pos,
        false, false, false, false, false, soCollisionAttackData::Region_None, true);
    m_yakumono->setAttack(index, 0, &attack);
}
