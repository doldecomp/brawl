#pragma once

#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <gr/gr_norfair_player_area_check.h>
#include <memory.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::Heal, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::Heal, this);
    }

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::Heal, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

// The All-Star Mode rest area: the fighters beaten so far stand around as trophies ("corps figures") and heart
// containers are laid out for the player to pick up; walking into the warp zone starts the next round.
class stHeal : public stMelee {
    grMadein* m_mainGround;       // 0x1D8
    grMadein* m_decoGround;       // 0x1DC
    grMadein* m_effectGround;     // 0x1E0
    grPlayerAreaCheck* m_warpZone; // 0x1E4
    int m_heartNode[5];           // 0x1E8: node indices of "heartPosition01".."05"
    int m_warpNode;               // 0x1FC: "warpPosition"
    int m_heartItemId[5];         // 0x200: instance ids of the heart items placed on the hearts' nodes
    int m_itemFigureNode;         // 0x214: "ItmFigurePosition"
    int m_figureNode[36];         // 0x218: "figurePosition01".."36"
    bool m_isWarped;              // 0x2A8: a fighter has entered the warp zone
    int m_timer;                  // 0x2AC
    int m_state;                  // 0x2B0

public:
    stHeal(const char* name) : stMelee(name, Stages::Heal) {
        m_isWarped = false;
        m_timer = data_loc_0;
        m_state = 0;
    }
    static stHeal* create();

    virtual ~stHeal();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual bool isEventEnd(int param1, int* eventState, int* eventDecision);

    static s32 data_loc_0;
    static stClassInfoImpl<Stages::Heal, stHeal> bss_loc_24;
};
static_assert(sizeof(stHeal) == 0x2B4, "Class is wrong size!");
