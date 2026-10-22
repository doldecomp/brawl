#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <so/so_external_value_accesser.h>
#include <types.h>

class emExternalValueAccesser : public soExternalValueAccesser {
public:
    static Vec3f getCenterPos(Enemy* em);
    static bool isCanGetRareItem(Enemy* em);
    static s32 getHitStopFrame(Enemy* em);
    static float getHp(Enemy* em, u32 taskId);
    static float getMaxHp(Enemy* em, u32 taskId);
    static s32 getNameMsgId(Enemy* em, u32 taskId);
    static float getScore(Enemy* em);
    static bool isCanAutoRemove(Enemy* em);
    static bool isClipIn(Enemy* em);
    static bool isFigure(Enemy* em);
    static nw4r::g3d::ResFileData* getFaceTexPtr(Enemy* em, u32 taskId);
};
// TODO size assertion
