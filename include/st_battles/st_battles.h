#pragma once

#include <gm/gm_lib.h>
#include <memory.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::BattleFieldS, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::BattleFieldS, this);
    }

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::BattleFieldS, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stBattleFieldS : public stMelee {
public:
    stBattleFieldS();
    static stBattleFieldS* create();

    virtual ~stBattleFieldS();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual bool isBamperVector() { return true; }

    // Name unknown. Raises the error screen selected by a debug value in
    // the melee init data; nothing in this module calls it.
    virtual void notifyDebugError();

    static stClassInfoImpl<Stages::BattleFieldS, stBattleFieldS> bss_loc_14;
};
static_assert(sizeof(stBattleFieldS) == 0x1D8, "Class is wrong size!");
