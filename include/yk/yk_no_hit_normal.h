#pragma once

// A stage gimmick's hit object: a Yakumono that owns one attack module built by a soCollisionAttackModuleBuilder (the
// "NoHit" in the original name means it has no hit module of its own, only the attack module). The attack and hit X
// positions are read from work arrays the gimmick provides.

#include <so/collision/so_collision_attack_module_impl.h>
#include <yk/yakumono.h>

// sora_melee's null module singletons the base constructor wants (names unknown).
extern u8 lbl_27_bss_398[];
extern u8 lbl_27_bss_3DC[];
extern u8 lbl_27_bss_598[];
extern u8 lbl_27_bss_444[];
extern soEventObserverRegistrationDesc* lbl_27_data_54C60;

template <class TAttackConfig>
class ykNoHitNormal : public Yakumono {
    soCollisionAttackModuleBuilder<TAttackConfig> m_attackBuilder;
    float* m_attackPosXWork;
    float* m_hitPosXWork;
    int m_attackPosXCount;
    int m_hitPosXCount;

public:
    ykNoHitNormal(ykInitInfo* info)
        : Yakumono(info, "ykNoHitNormal", m_attackBuilder.getModule(), lbl_27_bss_398, lbl_27_bss_3DC, lbl_27_bss_598, lbl_27_bss_444),
          m_attackBuilder(&moduleAccesser, m_taskId, m_taskCategory, lbl_27_data_54C60) {
        postInitialize();
        activate(info->m_pos, -1.0f, 0.0f);
        m_attackPosXWork = NULL;
        m_hitPosXWork = NULL;
        m_attackPosXCount = 0;
        m_hitPosXCount = 0;
    }
    virtual ~ykNoHitNormal() { }
    virtual void initAttackPosXWork(int work, int count) {
        m_attackPosXWork = (float*)work;
        m_attackPosXCount = count;
    }
    virtual void initHitPosXWork(int work, int count) {
        m_hitPosXWork = (float*)work;
        m_hitPosXCount = count;
    }
    virtual float getAttackPosX(int index) { return m_attackPosXWork[index]; }
    virtual float getHitPosX(int index) { return m_hitPosXWork[index]; }
};
