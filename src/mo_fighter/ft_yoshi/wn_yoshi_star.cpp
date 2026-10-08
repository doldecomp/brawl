// MATCH-ONLY: preserve native article instruction scheduling.
#pragma scheduling off
#define MT_VEC2F_ASSIGN_NOINLINE
#include <wn/yoshi/wn_yoshi_star.h>
#include <wn/wn_activate_desc.h>
#include <wn/wn_kinetic_energy_normal.h>
#include <so/so_module_accesser.h>
#include <ac/ac_anim_cmd_impl.h>

void wnYoshiStar::activate(int founderTaskId, int team, Vec3f* pos, float lr) {
    wnActivateDesc desc;
    desc.founderTaskId = founderTaskId;
    desc.resourceId = desc.unk8 = desc.unkC = 0xFFFF;
    desc.unk10 = desc.unk14 = -1;
    desc.unk18 = desc.unk1C = 0;
    desc.pos = *pos;
    desc.lr = lr;
    desc.team = team;
    desc.life = 0;
    desc.unk38 = 2;
    desc.unk3C = 0x80;
    desc.unk40 = 0;
    desc.unk44 = 0x35F;
    desc.unk48 = 0;
    desc.flags = 0x88;
    // The consumer reads only the upper two bits of the second flag byte.
    desc.unk4D = 0;
    Weapon::activate(&desc);
    m_moduleAccesser->getStatusModule().changeStatusForce(0, m_moduleAccesser);
    wnKineticEnergyNormal& normal = dynamic_cast<wnKineticEnergyNormal&>(
        *m_moduleAccesser->getKineticModule().getEnergy(0));
    Vec2f limit;
    Vec2f::copy(limit, normal.m_speedLimit);
    Vec2f speed(m_param->unk0 * lr, m_param->unk8);
    Vec2f accel(m_param->unk4 * lr, -m_param->unk10);
    limit.m_y = m_param->unkC;
    normal.m_speed = speed;
    normal.m_accel = accel;
    normal.m_speedTarget = limit;
    normal.m_speedLimit = limit;
}

bool wnYoshiStar::notifyEventCollisionAttackCheck(u32 flags) {
    if (flags & 0x13) return true;
    if (flags & 4) {
        if (unkA4 & 0x80) return hop();
        return true;
    }
    if ((flags & 8) && m_moduleAccesser->getReflectModule().isReflect() == true) {
        m_moduleAccesser->getPostureModule().reverseLr();
        m_moduleAccesser->getPostureModule().updateRotYLr();
        int team = m_moduleAccesser->getReflectModule().getTeam();
        m_moduleAccesser->getTeamModule().setTeam(team, true);
        m_moduleAccesser->getTeamModule().setHitTeam(team);
        soTeamModule& teamModule = m_moduleAccesser->getTeamModule();
        teamModule.setTeamOwnerId(m_moduleAccesser->getReflectModule().getTaskId());
        return reflect();
    }
    return false;
}

bool wnYoshiStar::notifyEventAnimCmd(acAnimCmd* cmd, soModuleAccesser* a, int index) {
    if (Weapon::notifyEventAnimCmd(cmd, a, index)) return true;
    if (!isObserv(cmd->getGroup())) return false;
    if (cmd->getType() > -1) cmd->getType();
    return false;
}
