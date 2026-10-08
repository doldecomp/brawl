// MATCH-ONLY: retain native fighter-module scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wn_kinetic_energy_gravity.h>
#include <so/so_kinetic_energy_normal.h>
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

void wnWarioBikeStatusUniqProcessStart::execFixPos(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soModelModule& model = a->getModelModule();
    Vec3f rot = model.getNodeGlobalRotation(8, false);
    float angle = -rot.m_x;
    work.setFloat(angle, 0x21000000);
    work.setFloat(angle, 0x21000001);
    work.setFloat(angle, 0x21000002);
    work.setFloat(angle, 0x21000003);
}
void wnWarioBikeStatusUniqProcessStart::exitStatus(soModuleAccesser* a, int nextStatus) {
    if (nextStatus == 2) {
        soWorkManageModule& work = a->getWorkManageModule();
        soKineticModule& kinetic = a->getKineticModule();
        soPostureModule& posture = a->getPostureModule();
        soLinkModule& link = a->getLinkModule();
        soParamAccesser* params = static_cast<soParamAccesser*>(work.getParamAccesser());
        soKineticEnergyNormal& normal = dynamic_cast<soKineticEnergyNormal&>(*kinetic.getEnergy(0));
        wnKineticEnergyGravity& gravity = dynamic_cast<wnKineticEnergyGravity&>(*kinetic.getEnergy(1));
        float angle = work.getFloat(0x21000000);
        float lr = posture.getLr();
        if (!link.isLink(3)) {
            float speed = params->getParamFloat(a, 0xfa0, 0);
            Vec2f direction(1.0f, 0.0f);
            direction.rot(&direction, 0.017453292f * angle);
            direction.m_x *= lr;
            Vec2f velocity(direction.m_x * speed, direction.m_y * speed);
            normal.setSpeed(&velocity);
            gravity.m_speedY = 0.0f;
            work.onFlag(0x22000006);
            work.onFlag(0x22000004);
            work.onFlag(0x22000005);
        } else {
            Vec2f previous = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(1));
            float speedX = params->getParamFloat(a, 0xfa1, 0);
            float speedY = params->getParamFloat(a, 0xfa2, 0);
            Vec2f velocity(speedX * lr, 0.0f);
            normal.setSpeed(&velocity);
            gravity.m_speedY = previous.m_y + speedY;
            work.offFlag(0x22000006);
            work.offFlag(0x22000004);
            work.offFlag(0x22000005);
        }
        Vec3f rot(-angle, 0.0f, 0.0f);
        posture.setRot(&rot, 0);
        normal.enable();
        gravity.enable();
    }
}
// MATCH-ONLY: this real module-local copy is called by the original Start exit.
#pragma dont_inline on
void soKineticEnergyNormal::setSpeed(Vec2f* speed) {
    m_speed.m_x = speed->m_x;
    m_speed.m_y = speed->m_y;
}
#pragma dont_inline reset
wnWarioBikeStatusUniqProcessStart g_wnWarioBikeStatusUniqProcessStart;
