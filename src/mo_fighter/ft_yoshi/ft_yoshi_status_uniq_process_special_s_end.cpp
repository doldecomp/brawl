#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftYoshiStatusUniqProcessSpecialSEnd::initStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    soPostureModule& posture = acc->getPostureModule();
    soModelModule& model = acc->getModelModule();
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    // MATCH-ONLY: retain the original aggregate word copy.
    Vec2f speed;
    Vec2f::copy(speed, kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1)));
    if (situation.getKind() == Situation_Ground) {
        kinetic.changeKinetic(6, acc);
        speed.m_x *= param->endHorizontalMultiplier;
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        stop.setSpeed(&speed);
    } else {
        kinetic.changeKinetic(10, acc);
        speed.m_x *= param->endHorizontalMultiplier;
        speed.m_y *= param->endVerticalMultiplier;
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        // MATCH-ONLY: retain the original call-temporary stack order.
        stop.setSpeed(&Vec2f(speed.m_x, 0.0f));
        stop.suspend();
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        gravity.m_speedY = speed.m_y;
    }
    Vec3f scale;
    scale.m_x = scale.m_y = scale.m_z = 1.0f;
    model.setNodeScale(2, &scale);
    float lr = work.getFloat(0x21000008);
    if (lr != 0.0f) posture.setLr(lr);
    work.setFloat(0.0f, 0x21000008);
    model.setNodeRotateY(3, 0.0f);
    model.setNodeRotateZ(2, 0.0f);
    acc->getVisibilityModule().set(1, 1);
}
void ftYoshiStatusUniqProcessSpecialSEnd::execStatus(soModuleAccesser* acc) {
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyChange(acc);
    ftYoshiStatusUniqProcessSpecialSUtility::setBodyScale(acc);
}
void ftYoshiStatusUniqProcessSpecialSEnd::execFixPosCounter(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    soSituationModule& situation = acc->getSituationModule();
    soKineticModule& kinetic = acc->getKineticModule();
    if (situation.isSituationChanged()) {
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        if (situation.getKind() == Situation_Ground) {
            kinetic.changeKinetic(6, acc);
            stop.resume();
        } else {
            kinetic.changeKinetic(10, acc);
            stop.suspend();
        }
    }
    if (situation.getKind() == Situation_Ground) work.setFloat(0.0f, 0x21000008);
    else {
        work.setFloat(0.0f, 0x21000008);
        work.setInt(0, 0x20000006);
    }
}
void ftYoshiStatusUniqProcessSpecialSEnd::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus != 0x113) {
        if (static_cast<unsigned>(nextStatus - 0x119) > 3) return;
    }
    ftYoshiStatusUniqProcessSpecialSUtility::resetYoshiSpecialS2(acc);
}
ftYoshiStatusUniqProcessSpecialSEnd g_ftYoshiStatusUniqProcessSpecialSEnd;
