#pragma once

#include <StaticAssert.h>
#include <so/so_info.h>
#include <types.h>

class ftInfo : public soInfo {
public:
    enum AttackComboType {
        Attack_Combo_None = 0x0,
        Attack_Combo_Hit = 0x1,
        Attack_Combo_Succeed = 0x2,
    };

    enum Attack100Type {
        Attack_100_None = 0x0,
        Attack_100_Normal = 0x1,
    };

    enum JumpAerialType {
        Jump_Aerial_None = 0x0,
        Jump_Aerial_Normal = 0x1,
        Jump_Aerial_Fly = 0x2
    };

    enum GlideType {
        Glide_None = 0x0,
        Glide_Normal = 0x1,
    };

    enum SquatWalkType {
        Squat_Walk_None = 0x0,
        Squat_Walk_Normal = 0x1
    };

    enum AttackDashType {
        Attack_Dash_Wait = 0x0,
        Attack_Dash_Squat_Wait = 0x1,
    };

    enum WallJumpType {
        Wall_Jump_None = 0x0,
        Wall_Jump_Normal = 0x1,
    };

    enum AttachWallType {
        Attach_Wall_None = 0x0,
        Attach_Wall_Normal = 0x1,
    };

    enum AirLassoType {
        Air_Lasso_None = 0x0,
        Air_Lasso_Normal = 0x1,
    };

    enum MotionShareType {
        Motion_Share_Normal = 0x0,
        Motion_Share_Taro = 0x1,
        Motion_Share_Big = 0x2,
        Motion_Share_Girl = 0x3,
    };

    enum CaptureMotionHeight {
        Capture_Motion_High = 0x0,
        Capture_Motion_Low = 0x1
    };

public:
    virtual ~ftInfo() { }
    virtual bool isInvalidKind(int kind);
    virtual int getInvalidKind();
    virtual const char* getNamePtr(int kind);
    virtual u32 getMotionNum(int kind);
    virtual u32 getStatusNum(int kind);

    static ftInfo* getInstance();

};
