// MATCH-ONLY: retain the native article status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_module_accesser.h>
#include <mt/mt_prng.h>
#include <math.h>

// HYPOTHESIS: the event's source type and field name remain unknown.
// The rider handles 0x841 by writing constant 0x5A88 into this word.
struct wnWarioBikeTurnEvent : soLinkEventArgs {
    int unk8;
    wnWarioBikeTurnEvent() : soLinkEventArgs(0x841) {}
};

void wnWarioBikeStatusUniqProcessTurnStart::initStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soLinkModule& link = a->getLinkModule();
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
    int count = work.getInt(0x20000000);
    wnWarioBikeTurnEvent query;
    link.sendEventParents(3, query);
    int random = randi(param->unk7C);
    // Repeated turns increase the chance of the alternate turn path.
    if (count + (4 - query.unk8) + 1 > random + 1 || count + 1 >= param->unk80)
        work.onFlag(0x22000009);
    work.setInt(count + 1, 0x20000000);
    ftWarioBikeLinkEvent event(0x83a);
    link.sendEventParents(3, event);
}

void wnWarioBikeStatusUniqProcessTurnStart::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soPostureModule& posture = a->getPostureModule();
    soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(
        *a->getKineticModule().getEnergy(0));
    Vec2f speed;
    Vec2f::copy(speed, normal.getSpeed());
    float lr = posture.getLr();
    if (1.0f == lr) {
        if (speed.m_x <= 0.0f) work.onFlag(0x22000003);
    } else {
        if (speed.m_x >= 0.0f) work.onFlag(0x22000003);
    }
    float angle = work.getFloat(0x21000000);
    Vec3f rotation(-angle, 0.0f, 0.0f);
    posture.setRot(&rotation, 0);
}

void wnWarioBikeStatusUniqProcessTurnStart::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soGroundModule& ground = a->getGroundModule();
    if (ground.isTouch((grCollStatus::TouchMask)8, 0)) {
        float lr = a->getPostureModule().getLr();
        Vec2f normal;
        Vec2f::copy(normal, ground.getTouchNormal((grCollStatus::TouchMask)8, 0));
        float angle = 57.29578f * (float)atan2(-(normal.m_x * lr), normal.m_y);
        work.setFloat(angle, 0x21000000);
    }
}

void wnWarioBikeStatusUniqProcessTurnStart::exitStatus(soModuleAccesser* a, int nextStatus) {
    if (nextStatus == 8) {
        soWorkManageModule& work = a->getWorkManageModule();
        soPostureModule& posture = a->getPostureModule();
        float angle = work.getFloat(0x21000000);
        work.setFloat(-angle, 0x21000000);
        work.setFloat(-work.getFloat(0x21000002), 0x21000002);
        Vec3f rotation(angle, 0.0f, 0.0f);
        posture.setRot(&rotation, 0);
        work.offFlag(0x22000002);
    }
}
wnWarioBikeStatusUniqProcessTurnStart g_wnWarioBikeStatusUniqProcessTurnStart;
