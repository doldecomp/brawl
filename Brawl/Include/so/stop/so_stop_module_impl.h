#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/anim/so_anim_cmd_event_presenter.h>

class soModuleAccesser;

class soStopModule {
public:
    virtual void setSpecialStop(u32 duration);
    virtual ~soStopModule();
    virtual void activate();
    virtual void end(s32);
    virtual void setHitStop();
    virtual void cancelHitStop();
    virtual void setOtherStop(u32 duration);
    virtual void cancelOtherStop();
    virtual void setLinkStop(u32 duration);
    virtual bool isStop();
    virtual bool isSpecialStop();
    virtual bool isHit();
    virtual bool isDamage();
    virtual void update();
    virtual s32 getHitStopFrame();
    virtual s32 getHitStopRealFrame();
    virtual void setHitStopFrame(u32 duration, bool allowSDI);
    virtual void setHitStopFrameFix(s32);
};
static_assert(sizeof(soStopModule) == 0x4, "Class is wrong size!");

class soStopModuleImpl : public soStopModule, public soAnimCmdEventObserver {
private:
    s32 m_hitStopRealFrame;
public:
    char m_hitStopFrameFix;
private:
    char unk15[0x7];
    u8 m_isStop : 1;
    u8 m_isHit : 1;
    u8 m_isDamage : 1;
    u8 unk1C_b4 : 1;
    u8 unk1C_b3 : 1;
    u8 m_isSpecialStop : 1;
    u8 unk1C_b1 : 1;
    u8 unk1C_b0 : 1;
public:
    soModuleAccesser* m_moduleAccesser;

    soStopModuleImpl(soModuleAccesser* acc);

    virtual void setSpecialStop(u32 duration);
    virtual ~soStopModuleImpl();
    virtual void activate();
    virtual void end(s32);
    virtual void setHitStop() { }
    virtual void cancelHitStop();
    virtual void setOtherStop(u32 duration);
    virtual void cancelOtherStop();
    virtual void setLinkStop(u32 duration);
    virtual bool isStop() { return m_isStop != 0; }
    virtual bool isSpecialStop() { return m_isSpecialStop != 0; }
    virtual bool isHit() { return m_isHit != 0; }
    virtual bool isDamage() { return m_isDamage != 0; }
    virtual void update();
    virtual s32 getHitStopFrame();
    virtual s32 getHitStopRealFrame() { return m_hitStopRealFrame; }
    virtual void setHitStopFrame(u32 duration, bool allowSDI);
    virtual void setHitStopFrameFix(s32);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3);
}; 
static_assert(sizeof(soStopModuleImpl) == 0x24, "Class is wrong size!");
