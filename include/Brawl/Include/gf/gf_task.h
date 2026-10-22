#pragma once

#include <StaticAssert.h>
#include <gf/gf_callback.h>
#include <types.h>

class gfTask {
public:
    enum Category {
        Category_None = 0x0,
        Category_Enemy = 0x2,
        Category_Ground = 0x6,
        Category_GrCollision = 0x7,
        Category_Menu = 0x8,
        Category_Fighter = 0xA,
        Category_Item = 0xB,
        Category_Weapon = 0xC,
        Category_Effect = 0xE,
        Category_Info = 0x12,
        Category_Camera = 0x15,
        Category_Visual = 0x1F,
        Category_Stage = 0x21,
        Category_Physics = 0x23,
        Category_AI = 0x24,
        Category_CoinShooter = 0x25,
        Category_Network = 0x26,
        Category_SoCollision = 0x27,
    };

    enum Render {
        Render_Pre,
        Render_Opa,
        Render_Xlu,
    };

    enum ProcessType {
        Process_Default,
        Process_Begin,
        Process_Anim,
        Process_Update,
        Process_PreMapCorrection,
        Process_MapCorrection,
        Process_FixPosition,
        Process_PreCollision,
        Process_Collision,
        Process_Catch,
        Process_Hit,
        Process_Camera,
        Process_FixCamera,
        Process_Effect,
        Process_GameProc,
        Process_End,
    };

    const char* m_taskName;
    gfTask* m_prev;     // TODO: suspend list and priority list prev?
    gfTask* m_next;     // TODO: suspend list and priority list next?
    gfTask* m_0xC;      // TODO: category list prev?
    gfTask* m_0x10;     // TODO: category list next?
    gfTask* m_0x14;     // TODO: unk31 list prev?
    gfTask* m_0x18;     // TODO: unk31 list next?
    gfTask* m_connectedTask;
    gfTask* m_attachedTask;
    gfTask* m_nextTask;
    u32 m_taskId;
    u8 _0 : 1;
    bool m_alive : 1;
    bool unk2C_b5 : 1;
    u8 _1: 1;
    bool unk2C_b3 : 1;
    bool unk2C_b2 : 1;
    bool unk2C_b1 : 1;
    bool unk2C_b0 : 1;
    u32 _2 : 1;
    s32 m_status : 8;
    Category m_taskCategory : 8;
    u32 _4 : 7;
    u8 unk30;
    u8 unk31;
    u16 unk32;
    u16 unk34; // Note: MSBit is 'isPaused'
    gfCallBackList unk38;

    bool getFlag1() const { return unk2C_b1; }
    bool getFlag2() const { return unk2C_b2; }
    bool getFlag5() const { return unk2C_b5; }
    bool isAlive() const { return m_alive; }
    s32 getStatus() const { return m_status; }
    void setStatus(s32 st) { m_status = st; }

    gfTask(const char* name, Category category, int unk2, int unk3, bool unk4);
    virtual void processDefault();
    virtual void processBegin();
    virtual void processAnim();
    virtual void processUpdate();
    virtual void processPreMapCorrection();
    virtual void processMapCorrection();
    virtual void processFixPosition();
    virtual void processPreCollision();
    virtual void processCollision();
    virtual void processCatch();
    virtual void processHit();
    virtual void processCamera();
    virtual void processFixCamera();
    virtual void processEffect();
    virtual void processGameProc();
    virtual void processEnd();
    virtual void renderPre();
    virtual void renderOpa();
    virtual void renderXlu();
    virtual void processDebug();
    virtual void renderDebug();
    virtual void init();
    virtual ~gfTask();

    void updateId();
    void process(ProcessType taskType);
    void render(Render kind);
    void setPaused(bool paused);
    void link(bool p1);
    void unlink();
    void exit();
    int getId();
    Category getCategory();
    static gfTask* getTask(int taskId);
};
static_assert(sizeof(gfTask) == 0x40, "Class is wrong size!");
