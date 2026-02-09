#pragma once

#include <gm/gm_lib.h>
#include <gr/gr_tengan_event.h>
#include <memory.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::Config, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::Config, this);
    };

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::Config, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stConfig : public stMelee {
//    void* m_shrineStageData;
    // TODO: float array?

  public:
    stConfig();
    virtual ~stConfig();
    virtual void createObj();
    virtual bool loading();
//    virtual void update(float deltaFrame);
//    virtual void initStageData();
    virtual bool isReStartSamePoint() { return false; }
    static stConfig* create();
    static stClassInfoImpl<Stages::Config, stConfig> bss_loc_14;
};
//static_assert(sizeof(stCrayon) == 0x200, "Class is wrong size!");
