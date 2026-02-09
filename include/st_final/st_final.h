#pragma once

#include <gm/gm_lib.h>
#include <gr/gr_tengan_event.h>
#include <memory.h>
#include <nw4r/ut/ut_Color.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::Final, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::Final, this);
    };

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::Final, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stFinal : public stMelee {
//    void* m_shrineStageData;
    // TODO: float array?

  public:
    stFinal();
    virtual ~stFinal();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
//    virtual void update(float deltaFrame);
//    virtual void initStageData();
//    virtual bool isReStartSamePoint() { return false; }
    virtual GXColor getFinalTechniqColor() { return nw4r::ut::Color(0x14000496); }
    virtual bool isBamperVector() { return true; }
//    virtual void notifyEventInfoGo();
    static stFinal* create();
    static stClassInfoImpl<Stages::Final, stFinal> bss_loc_14;
};