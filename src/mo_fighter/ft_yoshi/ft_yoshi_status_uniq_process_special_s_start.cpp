#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftYoshiStatusUniqProcessSpecialSStart::initStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soControllerModule& controller = acc->getControllerModule();
    soSituationModule& situation = acc->getSituationModule();
    soPostureModule& posture = acc->getPostureModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soGroundModule& ground = acc->getGroundModule();
    if (situation.getKind() != Situation_Air) {
        situation.setKind(Situation_Air, false);
        ground.setCorrect(static_cast<soGroundShapeImpl::CorrectKind>(5), 0);
    }
    float lr = controller.getStickX() > 0.0f ? 1.0f : -1.0f;
    posture.setLr(lr);
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    float speed = situation.getKind() == Situation_Air ? param->startAirSpeed : param->startSpeed;
    if (static_cast<float>(controller.getFlickNoResetX()) < param->flickThreshold) speed *= param->flickSpeedMultiplier;
    work.setFloat(speed, 0x21000006);
    work.setInt(param->life, 0x20000000);
    work.setInt(-1, 0x20000001);
    work.setInt(-1, 0x20000002);
    work.setInt(0, 0x20000003);
    work.setFloat(0.0f, 0x21000005);
    work.setFloat(0.0f, 0x21000008);
    work.setInt(0, 0x20000004);
    work.setInt(0, 0x20000005);
    work.setInt(0, 0x20000006);
    Vec3f rotation;
    // MATCH-ONLY: keep native x/y/z store order in the Vec3f temporary.
    rotation.m_x = 0.0f;
    rotation.m_y = 0.0f;
    rotation.m_z = 0.0f;
    kinetic.changeKinetic(0x32, acc);
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    Vec2f velocity;
    velocity.m_x = 0.0f;
    velocity.m_y = param->startVerticalSpeed;
    gravity.resetEnergy(0, &velocity, &rotation, acc);
    gravity.m_gravity = -param->gravity;
    gravity.enable();
    velocity.m_x = speed * lr;
    velocity.m_y = 0.0f;
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
    stop.resetEnergy(6, &velocity, &rotation, acc);
    stop.suspend();
}
void ftYoshiStatusUniqProcessSpecialSStart::execStatus(soModuleAccesser* acc) {
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(acc);
}
void ftYoshiStatusUniqProcessSpecialSStart::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
    if (situation.getKind() == Situation_Air) {
        ftKineticEnergyGravity& airGravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        airGravity.m_gravity = -param->gravity;
        airGravity.unk1C = param->gravityLimit;
        airGravity.m_fallSpeedMax = param->gravityLimit;
        work.setFloat(0.0f, 0x21000008);
    } else {
        gravity.clearSpeed();
        stop.clearSpeed();
        work.setFloat(0.0f, 0x21000008);
        work.setInt(0, 0x20000006);
    }
}
void ftYoshiStatusUniqProcessSpecialSStart::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus == 0x113 || static_cast<unsigned>(nextStatus - 0x119) <= 3)
        ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(acc);
}
ftYoshiStatusUniqProcessSpecialSStart g_ftYoshiStatusUniqProcessSpecialSStart;
