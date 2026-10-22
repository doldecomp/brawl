#pragma once

#include <StaticAssert.h>
#include <so/so_array.h>
#include <types.h>

struct soCollisionShieldData {
    char _[0x20];
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
    u32 _8[4];
};

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
