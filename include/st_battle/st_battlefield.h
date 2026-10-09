#pragma once

#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_vector.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::BattleField, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::BattleField, this);
    }

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::BattleField, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stBattleField : public stMelee {
    // Spawn points of the 100-Man Brawl (read from the "hyakunin_*_start%d" nodes of the stage model in createObj).
    Vec3f m_enemyStartPos[5];
    Vec3f m_bossStartPos[4];
    Vec3f m_fighterStartPos[2];

public:
    stBattleField();
    static stBattleField* create();

    virtual ~stBattleField();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual void getFighterStartPos(Vec3f* startPos, int fighterIndex);
    virtual bool isBamperVector() { return true; }

    static stClassInfoImpl<Stages::BattleField, stBattleField> bss_loc_14;
};
static_assert(sizeof(stBattleField) == 0x25C, "Class is wrong size!");
