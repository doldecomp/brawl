#pragma once

#include <StaticAssert.h>
#include <st/st_trigger_observe.h>
#include <types.h>

struct stAreaInfoData {
    int m_areaId;
};

struct stMovementData {
    Gimmick::AreaKind m_gimmickKind : 16;
    char _0x2[2];
    float m_speed;
    float m_vector;
    float _0xC;
    float _0x10;
    float _0x14;
    int m_taskId;
    char _0x1c[4];
};
static_assert(sizeof(stMovementData) == 0x20, "Class is wrong size!");

struct stMovementAreaInfoData : public stAreaInfoData, public stMovementData {

};
static_assert(sizeof(stMovementAreaInfoData) == 0x24, "Class is wrong size!");

struct stWaterData {
    Gimmick::AreaKind m_gimmickKind : 16;
    char _0x2[2];
    float m_swimHeight;
    float m_currentSpeed;
    u8 m_0xc;
    char _0xd[3];
};
static_assert(sizeof(stWaterData) == 0x10, "Class is wrong size!");

struct stWaterAreaInfoData : public stAreaInfoData, public stWaterData {

};
static_assert(sizeof(stWaterAreaInfoData) == 0x14, "Class is wrong size!");