#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>
#include <types.h>

soCollisionShieldPart::soCollisionShieldPart(u32 category1, u32 category2) : m_targets(6, 0) {
    m_targets.at(0).m_0 = 1 << category2;
    m_targets.at(1).m_0 = 1 << category1;
    if (m_targets.at(0).m_0 & 8) {
        m_targets.at(5).m_4 = 2;
    } else if (m_targets.at(0).m_0 & 0x10) {
        m_targets.at(5).m_4 = 4;
    }
}

soCollisionShieldPart::~soCollisionShieldPart() { }

void soCollisionShieldPart::reset(soCollisionShieldPartUnit* unit) {
    unit->m_targetArray = &m_targets;
    m_isActive = 0;
}

void soCollisionShieldPart::setData(soCollisionShieldData* data) {
    m_data = *data;
}

bool soCollisionShieldPart::update(soModuleAccesser* moduleAccesser, soCollisionShieldPartUnit* unit, float scale) {
    if (m_isActive) {
        Vec3f start = m_data.m_startOffsetPos;
        Vec3f end = m_data.m_endOffsetPos;
        soCollisionUtil::updateCollision(moduleAccesser, unit, m_data.m_shapeType, 0, m_data.m_nodeIndex, &start, &end, 0, false,
                                         m_data.m_size, scale);
        unit->m_isUpdated = true;
        return true;
    }
    unit->m_isUpdated = false;
    return false;
}

void soCollisionShieldPart::setTargetProperty(u32 property) {
    m_targets.at(5).m_4 = 1 << property;
}

void soCollisionShieldPart::debugDisplay(int arg, soCollisionShieldPartUnit* unit) {
    if (m_isActive) {
        GXColor color0 = {0x00, 0xFF, 0xFF, 0x80};
        GXColor color1 = {0x00, 0x80, 0x80, 0x80};
        GXColor color2 = {0x00, 0xFF, 0x80, 0x80};
        GXColor color3 = {0x00, 0x80, 0x40, 0x80};
        GXColor color4 = {0x00, 0x80, 0xFF, 0x80};
        GXColor color5 = {0x00, 0x40, 0x80, 0x80};
        const GXColor* a;
        const GXColor* b;
        if (m_targets.at(0).m_0 & 4) {
            a = &color0;
            b = &color1;
        } else if (m_targets.at(0).m_0 & 8) {
            a = &color2;
            b = &color3;
        } else {
            a = &color4;
            b = &color5;
        }
        unit->m_debugVtable[9](unit, arg, a, b);
    }
}
