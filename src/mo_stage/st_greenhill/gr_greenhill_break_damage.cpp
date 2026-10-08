#include <st_greenhill/gr_greenhill.h>
#include <ec/ec_mgr.h>
#include <mt/mt_prng.h>

// MATCH-ONLY: the stage's float constant pool.
extern const float g_greenhillBreakConstants[]; // [0] = 0.0f, [11] and [12] bound the effect delay

// A fighter hit the piece: the damage wears the piece down, and while it is hit the dust effect is replayed.
void grGreenhillBreak::onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo) {
    float damageAdd = damage->m_damageAdd;
    const float* constants = g_greenhillBreakConstants;
    fn_27_26399C(m_yakumono);

    unk170 -= damageAdd;
    if (unk170 < constants[0]) {
        unk170 = constants[0];
    }
    if (constants[0] == unk170 && *unk164 != 2) {
        *unk164 = 2;
    }
    if (constants[0] == unk160) {
        u32 effect = g_ecMgr->setEffect(ef_ptc_stg_greenhill_zimen_damage);
        g_ecMgr->setParent(effect, m_sceneModels[0], (u16)unk184, false);
        unk160 = constants[12] + constants[11] * randf();
    }
}
