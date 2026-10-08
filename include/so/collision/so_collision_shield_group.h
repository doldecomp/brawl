#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/so_array.h>
#include <types.h>

// NOTE: shadows the BrawlHeaders copy to model the layout of soCollisionShieldData.
struct soCollisionShieldData {
    // MATCH-ONLY: stored as plain words (a struct copy uses lwz/stw); read as two Vec3f.
    u32 m_offset0, m_offset1, m_offset2, m_offset3, m_offset4, m_offset5;
    // (struct copy tested with various member layouts)
    float m_size;
    u32 m_nodeIndex : 9;
    u32 m_shapeType : 1; // HYPOTHESIS: same meaning as the bit after the node index in soCollisionHitData
    u32 _1c_rest : 22;

    float offset(int i) { return ((float*)&m_offset0)[i]; }
};
static_assert(sizeof(soCollisionShieldData) == 0x20, "Class is wrong size!");

struct soCollisionReflectorData {
    char _0[0x4];
    float m_speedMul;
    float m_attackLimit;
    float m_lifeMul;
    char _16[0x4];
};
static_assert(sizeof(soCollisionReflectorData) == 0x14, "Class is wrong size!");

struct soCollisionShieldGroupData {
    soSet<soCollisionShieldData> m_shieldDataSet;
    // Four high flag bits are copied by soCollisionShieldGroup::add.
    u32 _8;
};

static_assert(sizeof(soCollisionShieldGroupData) == 0xC, "Shield group descriptor layout");

struct soCollisionReflectorGroupData {
    soSet<soCollisionShieldData> m_shieldDataSet;
    soCollisionReflectorData* m_reflectorData;
};

class soCollisionShieldGroup {
public:
	u8 _00[0x90];
	float m_posX;
	u32 _94;
	float m_Lr;
	float m_hopAngle;
	float m_attackMul;
	float m_speedMul;
	float m_attackLimit;
	float m_lifeMul;
	u8 m_isFront;
	u8 m_isHop;
	u8 m_isTurn;
	u8 m_isNoMBall;
	u8 m_isNoHop;
	u8 _b5[0x3];
};
static_assert(sizeof(soCollisionShieldGroup) == 0xB8, "Class is wrong size!");
