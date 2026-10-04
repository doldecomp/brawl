#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision.h>
#include <so/collision/so_collision_shield_group.h>
#include <so/so_array.h>
#include <so/so_module_accesser.h>
#include <types.h>

// HYPOTHESIS: per-part runtime object that the shield group hands to every
// soCollisionShieldPart (position at +0, target array at +0x1c, "updated" flag at +0x24,
// debug draw function table at +0x30). The real name is unknown.
struct soCollisionShieldPartUnit {
    Vec3f m_pos;
    u8 _c[0x10];
    soArray<clTarget>* m_targetArray;
    u8 _20[4];
    u8 m_isUpdated;
    u8 _25[0xB];
    // Address of a function table; slot 9 draws the debug shape (this, ?, &colorA, &colorB).
    void (**m_debugVtable)(soCollisionShieldPartUnit*, int, const GXColor*, const GXColor*);
};

namespace soCollisionUtil {
    void updateCollision(soModuleAccesser* moduleAccesser, soCollisionShieldPartUnit* unit, int, u32, int nodeIndex,
                         Vec3f* startPos, Vec3f* endPos, u32, bool, float size, float scale);
}

// One shield (guard bubble) collision sphere/capsule.
class soCollisionShieldPart {
public:
    soCollisionShieldData m_data;
    soArrayVector<clTarget, 6> m_targets;
    int m_isActive;

    soCollisionShieldPart(u32 category1, u32 category2);
    ~soCollisionShieldPart();
    void reset(soCollisionShieldPartUnit* unit);
    void setData(soCollisionShieldData* data);
    bool update(soModuleAccesser* moduleAccesser, soCollisionShieldPartUnit* unit, float scale);
    void setTargetProperty(u32 property);
    void debugDisplay(int, soCollisionShieldPartUnit* unit);
};
static_assert(sizeof(soCollisionShieldPart) == 0x60, "Class is wrong size!");
