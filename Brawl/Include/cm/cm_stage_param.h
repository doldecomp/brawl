#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <st/st_positions.h>
#include <types.h>

struct cmStageParam {
    Rect2D m_range;
    float m_verticalRotationFactor;
    float m_horizontalRotationFactor;
    float m_minZ;
    float m_maxZ;
    Vec3f m_centerPos;
    float m_fighterBubbleBufferMultiplier;
    float m_48;
    float m_speed;
    float m_tiltThreshold;
    float m_fov;
};
static_assert(sizeof(cmStageParam) == 0x40, "Class is wrong size!");

struct cmStageParamFixed {
    Vec3f m_centerPos;
    float m_fov;
    float m_verticalAngle;
    float m_horizontalAngle;
};
static_assert(sizeof(cmStageParamFixed) == 24, "Class is wrong size!");

struct cmStageParamPausedOffsetRange {
    float m_0;
    float m_4;
    float m_8;
    float m_12;
    cmStageParamPausedOffsetRange();
};
static_assert(sizeof(cmStageParamPausedOffsetRange) == 16, "Class is wrong size!");

struct cmStageParamPaused {
    float m_angle;
    float m_zoomIn;
    float m_zoomDefault;
    float m_zoomOUt;
    float m_rotYMin;
    float m_rotYMax;
    float m_rotXMin;
    float m_rotXMax;
    Vec3f m_centerPos;
    cmStageParamPausedOffsetRange m_offsetRange;
    char _60[16];
};
static_assert(sizeof(cmStageParamPaused) == 76, "Class is wrong size!");
