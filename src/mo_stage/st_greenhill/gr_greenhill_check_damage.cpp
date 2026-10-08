#include <st_greenhill/gr_greenhill.h>

// A fighter hit the ball: remember the attacker's team and let the ball react (state work 3).
void grGreenhillCheck::onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo) {
    fn_27_26399C(m_yakumono);
    unk15C[0] = 3;
    m_sndGenerator.playSE(static_cast<SndID>(0x1d16), 0, 0, -1);
    m_sndGenerator.setPos(&unk164[m_order[0]]);
    int team = damage->m_collisionLog.m_teamNo;
    m_hitTeam = team;
    if (m_yakumono != NULL) {
        m_yakumono->setTeam(team);
    }
}
