#pragma once

#include <gm/gm_lib.h>
#include <gr/gr_tengan_event.h>
#include <gm/gm_global.h>
#include <memory.h>
#include <nw4r/ut/ut_Color.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::Tengan, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::Tengan, this);
    };

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::Tengan, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stTengan : public stMelee {
    float unk1d8;
    float unk1dc;
    float m_rollTargetDegrees;
    float m_rollDegrees;
    float m_rollDirection;
    float m_rollSpeed;
    float m_reverseTargetDegrees;
    float m_reverseDegrees;
    float m_reverseDirection;
    float m_reverseSpeed;
    float unk200;
    s32 m_substage;
    snd3DGenerator snd_gen;
    u32 unk210;
    u32 unk214;
    s32 m_lastCresseliaEvent;
    grTenganEvent event1;
    grTenganEvent event2;
    grTenganEvent eventLegendDisappear;
    grTenganEvent eventLaser;
    grTenganEvent eventQuake;
    grTenganEvent eventCameraRoll;
    grTenganEvent eventSlow;
    grTenganEvent eventDropStage;
    grTenganEvent eventRebuildStage;
    grTenganEvent eventAura;
    grTenganEvent eventUpDownReverse;
    grTenganEvent eventLeftRightReverse;
    grTenganEvent eventGravityHalf;
    grTenganEvent event14;
    grTenganEvent event15;
    grTenganEvent eventBoomerang;
    grTenganEvent eventRandomCall;
    grTenganEvent eventSonicWaveCall;
    Vec3f posDialga;
    float unke40;
    float unke44;
    float unke48;
    u32 unke4c;
    u32 unke50;
    u8 m_legendEventActive;
    u8 unke55;
    float unke58;
    float unke5c;
    u8 unke60;
    float m_rebuildTimer;
    u8 m_stateFloor[3]; // Left, center, right; shared with grTenganFloor.
    u8 unke6b;
    Vec3f posAshibaWork[4];
    u32 unke9c;
    u32 m_dropSoundHandle;
    float unkea4;
    u8 unkea8;
    u32 unkeac;
    u32 unkeb0;
    u32 m_randomCallEffectHandle;
    u8 unkeb8;
    u8 unkeb9;
    u8 unkeba;
    float unkebc;
    float unkec0;
    float unkec4;
    u8 unkec8;
    float unkecc;
    float unked0;
    float unked4;
    float unked8;
    u32 m_boomerangEffectHandle;
    s32 m_auraSoundHandle;
    s32 m_boomerangSoundHandle;
    SndID m_pendingLegendSound;
    float m_legendSoundDelayFrames;
    u8 m_boomerangMotion;
    char m_slow;

  public:
    bool eventRebuildStageUpdate();
    bool eventGravityHalfUpdate();
    bool eventDropStageUpdate();
    bool eventBoomerangUpdate();
    bool eventAuraUpdate();
    bool eventRandomCallUpdate();
    bool eventUpDownReversUpdate(float deltaFrame);
    bool eventCameraRollUpdate(float deltaFrame);
    void setEventCrecelia();
    
    stTengan();
    virtual ~stTengan();
    virtual void createObj();
    virtual void createObjEnkei(int index);
    virtual void createObjBg(int index);
    virtual void createObjDialga(int index);
    virtual void createObjAshiba(int index);
    virtual void createObjFloor(int index);
    virtual void createObjSkyLaser(int index);
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual void updateEvent(float deltaFrame);
    virtual u32 getZoneLightSetIndex(Vec3f *position);
    virtual GXColor getFinalTechniqColor() { return nw4r::ut::Color(0x1400047d); }
    virtual bool isBamperVector() { return true; }
    static stTengan* create();
    static stClassInfoImpl<Stages::Tengan, stTengan> bss_loc_14;
};
