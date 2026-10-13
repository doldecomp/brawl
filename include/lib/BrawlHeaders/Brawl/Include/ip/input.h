#pragma once

#include <mt/mt_vector.h>
#include <StaticAssert.h>
#include <types.h>
\
struct ipPadButton {

    typedef u32 Mask;
    static const Mask MASK_ATTACK = 1 << 0;
    static const Mask MASK_SPECIAL = 1 << 1;
    static const Mask MASK_JUMP = 1 << 2;
    static const Mask MASK_GUARD = 1 << 3;
    static const Mask MASK_STOCK_SHARE = 1 << 4;
    static const Mask MASK_SMASH = 1 << 5;
    static const Mask MASK_DIR_L = 1 << 6;
    static const Mask MASK_DIR_Hi = 1 << 7;
    static const Mask MASK_DIR_R = MASK_DIR_L | MASK_DIR_Hi;
    static const Mask MASK_CSTICK = 1 << 8;
    static const Mask MASK_APPEAL_HI = 1 << 10;
    static const Mask MASK_APPEAL_S = 1 << 11;
    static const Mask MASK_APPEAL_LW = 1 << 12;
    static const Mask MASK_APPEAL_S_L = 1 << 13;
    static const Mask MASK_APPEAL_S_R = 1 << 14;
    static const Mask MASK_FLICK_JUMP = 1 << 15;

    enum Dir {
        Dir_Lw = 0x0,
        Dir_L = 0x1,    // left dpad
        Dir_Hi = 0x2,   // up dpad or jump
        Dir_R = 0x3,    // right dpad
    };

    union {
        struct {
            Mask m_mask;
        };
        struct {
            unsigned short : 16;
            bool m_flickJump : 1;
            bool m_appealSR : 1;
            bool m_appealSL : 1;
            bool m_appealLw : 1;
            bool m_appealS : 1;
            bool m_appealHi : 1;
            bool _6 : 1;
            bool m_cStick : 1;
            Dir m_dir : 2;
            bool m_smash : 1;
            bool m_stockShare : 1;
            bool m_guard : 1;
            bool m_jump : 1;
            bool m_special : 1;
            bool m_attack : 1;
        };
    };

    inline ipPadButton() { };
    inline ipPadButton(Mask mask) : m_mask(mask) {};
};
static_assert(sizeof(ipPadButton) == 4, "Class is wrong size!");

struct ipPadTrigger {
    float m_l;
    float m_r;
};
static_assert(sizeof(ipPadTrigger) == 8, "Class is wrong size!");

class Input {
    bool unk0;
public:
    Input() : unk0(false) { }
    virtual ~Input() { }
    virtual void update();
    virtual Vec2f getStickMain() const;
    virtual Vec2f getStickSub() const;
    virtual ipPadButton getButton() const;
    virtual ipPadTrigger getTrigger() const;
    virtual s32 getContNo() const;
    virtual void setRumble(u32, u32, s32, u8);   // TODO:: Verify parameters
    virtual void stopRumble();
    virtual void removeRumble();
    virtual void removeRumbleId(s32, s32); // TODO:: Verify parameters
    virtual void removeRumbleMask(u32);
};
static_assert(sizeof(Input) == 8, "Class is wrong size!");
