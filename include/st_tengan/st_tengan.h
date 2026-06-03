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
//    void* m_shrineStageData;
    float unk1d8;
    float unk1dc;
    float unk1e0;
    float unk1e4;
    float unk1e8;
    float unk1ec;
    float unk1f0;
    float unk1f4;
    float unk1f8;
    float unk1fc;
    float unk200;
    s32 m_substage;
    snd3DGenerator snd_gen;
    u32 unk210;
    u32 unk214;
    u32 unk218;
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
    u8 unke54;
    u8 unke55;
    float unke58;
    float unke5c;
    u8 unke60;
    float m_rebuildTimer;
    u8 m_stateFloorL;
    u8 m_stateFloorC;
    u8 m_stateFloorR;
    u8 unke6b;
    Vec3f posAshibaWork[4];
    u32 unke9c;
    u32 unkea0;
    float unkea4;
    u8 unkea8;
    u32 unkeac;
    u32 unkeb0;
    u32 unkeb4;
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
    u32 unkedc;
    u32 unkee0;
    u32 unkee4;
    float unkee8;
    float unkeec;
    u8 unkef0;
    char m_slow;
    // TODO: float array?

  public:
    bool eventRebuildStageUpdate();
    
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
    virtual u32 getZoneLightSetIndex(Vec2f *position);
//    virtual void update(float deltaFrame);
//    virtual void initStageData();
//    virtual bool isReStartSamePoint() { return false; }
    virtual GXColor getFinalTechniqColor() { return nw4r::ut::Color(0x1400047d); }
    virtual bool isBamperVector() { return true; }
//    virtual void notifyEventInfoGo();
    static stTengan* create();
    static stClassInfoImpl<Stages::Tengan, stTengan> bss_loc_14;
};
