#pragma once

#include <ft/robot/ft_robot_article_info.h>
#include <wn/weapon.h>

// R.O.B.'s Robo Beam projectile. Weapon implementation storage is still opaque; the size follows adjacent holder
// offsets in the article builder.
class wnRobotBeam : public Weapon {
    u8 m_unreconstructed[0x2020 - sizeof(Weapon)];
public:
    wnRobotBeam(s32 articleId, const ftRobotArticleConstructionInfo& info, void* data);
    virtual ~wnRobotBeam();
    // HYPOTHESIS: argument meanings, from the transactor's call site. lowCharge selects the weak beam.
    void activate(float lr, float angle, s32 founderTaskId, u32 resourceId, s32 team, const Vec3f* position,
                  bool lowCharge, s32 variant);
};
static_assert(sizeof(wnRobotBeam) == 0x2020, "Beam layout is wrong!");
