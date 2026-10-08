#pragma once

#include <gr/gr_yakumono.h>
#include <gr/collision/gr_collision_joint.h>
#include <snd/snd_3d_generator.h>

struct GreenhillGuestData;

// HYPOTHESIS: an unnamed sora_melee function that takes a Yakumono (the original calls it right after a hit).
extern "C" void fn_27_26399C(Yakumono* yakumono);

class grGreenhill : public grYakumono {
protected:
    u8 m_state;          // 0x150 (HYPOTHESIS: same role as in the Pirate Ship gimmicks)
    float m_timer;       // 0x154

public:
    grGreenhill(const char* taskName);
    virtual ~grGreenhill();
};
static_assert(sizeof(grGreenhill) == 0x158, "Class is wrong size!");

// The stage backdrop piece: it owns the collision joints of the hanging platform pieces and publishes the four
// marker positions the Check ball and the guests use.
class grGreenhillBg : public grGreenhill {
    Vec3f* m_posGimmickWork;       // 0x158 four marker positions (filled every frame from the model nodes)
    u8* m_breakInfo;               // 0x15C state of the breakable pieces (3 bytes)
    u32 m_node[9];                 // 0x160 node indices looked up by name on the first update
    grCollisionJoint* m_joint[7];  // 0x184

public:
    grGreenhillBg(const char* taskName);
    virtual ~grGreenhillBg();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    static grGreenhillBg* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateJoint(float deltaFrame);
    virtual void updateHang(float deltaFrame);
    virtual void setPosGimmickWork(Vec3f* positions) { m_posGimmickWork = positions; }
    virtual void setBreakInfo(u8* state) { m_breakInfo = state; }
};
static_assert(sizeof(grGreenhillBg) == 0x1A0, "grGreenhillBg layout");

// The breakable ground pieces of the stage (HYPOTHESIS name meaning, from the "Break" in the class name and the effect
// ef_ptc_stg_greenhill_zimen_damage).
// Per-stage parameters the Break object reads through getStageData(). Only the fields that are used are named.
struct grGreenhillBreakParam {
    u8 unk00[0x10];
    float unk10;        // copied to grGreenhillBreak::unk170
    u8 unk14[0x10];
    float m_waitMin;    // 0x24 range for the first countdown
    float m_waitMax;    // 0x28
    float unk2C;        // 0x2C countdown while the piece is gone
    float unk30;        // 0x30 respawn threshold
};

class grGreenhillBreak : public grGreenhill {
    float unk158;               // 0x158 blink timer
    float unk15C;               // 0x15C
    float unk160;               // 0x160
    u8* unk164;                 // 0x164 state work
    u8* unk168;                 // 0x168 break info shared with the Bg and Check objects
    u8 m_type;                  // 0x16C
    u8 unk16D[3];
    float unk170;               // 0x170
    u8 m_animId;                // 0x174 current animation
    u8 unk175[3];
    float unk178;               // 0x178
    u32 m_nodeA;                // 0x17C node indices of the two visible pieces
    u32 m_nodeB;                // 0x180
    u32 unk184;                 // 0x184
    grCollisionJoint* m_joint;  // 0x188 collision joint owned by this object
    u8 unk18C;                  // 0x18C
    u8 unk18D;                  // 0x18D
    u8 unk18E[2];
    void* unk190[5];            // 0x190
    snd3DGenerator m_sndGenerator; // 0x1A4

public:
    grGreenhillBreak(const char* taskName);
    virtual ~grGreenhillBreak();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    virtual void onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo);
    static grGreenhillBreak* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateJoint(float deltaFrame);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateBreak(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setAttack(int index);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setStateWork(u8* state) { unk164 = state; }
    virtual void setType(u8 type) { m_type = type; }
    virtual void setBreakInfo(u8* state) { unk168 = state; }
};
static_assert(sizeof(grGreenhillBreak) == 0x1AC, "grGreenhillBreak layout");

// The checkered ball hazard (HYPOTHESIS name: "Check" after the marker nodes it rolls between). The ball picks a random
// order for the four marker positions, drops onto them in turn and hurts fighters it hits.
class grGreenhillCheck : public grGreenhill {
    float m_timer2;             // 0x158
    u8* unk15C;                 // 0x15C state work shared with the stage
    u8* unk160;                 // 0x160 state of the breakable pieces
    Vec3f* unk164;              // 0x164 the four marker positions
    u8 m_order[4];              // 0x168 random permutation of the marker positions
    u8 m_orderDone;             // 0x16C
    u8 unk16D[3];
    s32 m_hitTeam;              // 0x170
    u32 m_effectId;             // 0x174
    u8 m_animId;                // 0x178 current animation (5 = none yet)
    u8 unk179[3];
    float unk17C;               // 0x17C
    float m_motionEndFrame;     // 0x180
    u8 unk184;                  // 0x184
    u8 m_attackEnabled;         // 0x185
    u8 unk186[2];
    void* unk188[5];            // 0x188
    snd3DGenerator m_sndGenerator; // 0x19C
    s32 m_dangerZoneId;         // 0x1A4

public:
    grGreenhillCheck(const char* taskName);
    virtual ~grGreenhillCheck();
    virtual void update(float deltaFrame);
    virtual void onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo);
    static grGreenhillCheck* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void changeColor(int state);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setPosWork(Vec3f* positions) { unk164 = positions; }
    virtual void setStateWork(u8* state) { unk15C = state; }
    virtual void setStateBreakWork(u8* states) { unk160 = states; }
};
static_assert(sizeof(grGreenhillCheck) == 0x1A8, "grGreenhillCheck layout");

// Per-stage parameters the Guest object reads through getStageData(). Only the fields that are used are named.
struct grGreenhillGuestParam {
    u8 unk00[0x40];
    float unk40;  // added to the guest's progress every frame
    float unk44;  // upper limit of the progress
};

class grGreenhillGuest : public grGreenhill {
    GreenhillGuestData* unk158;
    snd3DGenerator m_sndGenerator; // 0x15C
    u8 unk164;                     // 0x164 sound already played

public:
    grGreenhillGuest(const char* taskName);
    virtual ~grGreenhillGuest();
    virtual void update(float deltaFrame);
    static grGreenhillGuest* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; }
};
static_assert(sizeof(grGreenhillGuest) == 0x168, "grGreenhillGuest layout");

class grGreenhillGuestLine : public grGreenhill {
    GreenhillGuestData* unk158;
    u32 m_nodeIndex;       // 0x15C node of the guests' run line
    u8 m_animId;           // 0x160 current animation
    u8 unk161[3];
    float m_motionEndFrame; // 0x164

public:
    grGreenhillGuestLine(const char* taskName);
    virtual ~grGreenhillGuestLine();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    static grGreenhillGuestLine* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; }
};
static_assert(sizeof(grGreenhillGuestLine) == 0x168, "grGreenhillGuestLine layout");
