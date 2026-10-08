// MATCH-ONLY: preserve the original instruction scheduling.
#pragma scheduling off
#include <wn/sonic/wn_sonic_super_sonic_kinetic_transactor.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/controller/so_controller_impl.h>
#include <math.h>

// The original family owns these finite-value and near-zero helpers.
// HYPOTHESIS: public spelling is map-derived; behavior is proved by both callers.
#pragma dont_inline on
bool mtIsNormal(float value) {
    union { float value; u32 bits; } data;
    data.value = value;
    bool result = true;
    if (((data.bits >> 23) & 0xff) == 0xff) result = false;
    return result;
}
bool mtIsZero(float value) {
    bool result = false;
    double magnitude = __fabs(value);
    value = magnitude;
    if (value < 0.00001f) result = true;
    return result;
}
#pragma dont_inline reset

void wnSonicSuperSonicKineticTransactor::updateEnergy(soKineticEnergyNormal* energy, soModuleAccesser* acc) {
    if (acc->getKineticModule().getKineticType() == 0x20 || acc->getKineticModule().getKineticType() == 0x21)
        updateEnergyFinalMoveCommon(energy, acc);
    else
        energy->updateEnergy(acc);
}
void wnSonicSuperSonicKineticTransactor::updateEnergyFinalMoveCommon(soKineticEnergyNormal* energy, soModuleAccesser* acc) {
    float stickX = acc->getControllerModule().getStickX();
    float stickY = acc->getControllerModule().getStickY();
    float brake = 0.0f;
    {
        Vec2f speed = energy->getSpeed();
        bool finite = false;
        if (mtIsNormal(speed.m_x)) finite = mtIsNormal(speed.m_y) == true;
        if (finite) {
            Vec2f speed = energy->getSpeed();
            bool zero = false;
            if (mtIsZero(speed.m_x) && mtIsZero(speed.m_y)) zero = true;
            if (!zero) {
                Vec2f speed = energy->getSpeed();
                float factor = soValueAccesser::getConstantFloat(acc, 0xfa5, 0);
                brake = speed.length() * factor;
            }
        }
    }
    Vec2f braking(0.0f, 0.0f);
    Vec2f target(-1.0f, -1.0f);
    Vec2f acceleration(0.0f, 0.0f);
    Vec2f retainedSpeed = energy->getSpeed();
    float priorLength = energy->getSpeed().length();
    double absoluteX = __fabs(stickX);
    float magnitudeX = absoluteX;
    if (magnitudeX < soValueAccesser::getConstantFloat(acc, 0xfa4, 0)) {
        braking.m_x = brake;
        target.m_x = 0.0f;
    } else {
        acceleration.m_x = stickX * soValueAccesser::getConstantFloat(acc, 0xfa0, 0);
    }
    if (acc->getKineticModule().getKineticType() == 0x20 && stickY < soValueAccesser::getConstantFloat(acc, 0xfa4, 0)) {
        retainedSpeed.m_y = 0.0f;
    } else {
        double absoluteY = __fabs(stickY);
        float magnitudeY = absoluteY;
        if (magnitudeY < soValueAccesser::getConstantFloat(acc, 0xfa4, 0)) {
            braking.m_y = brake;
            target.m_y = 0.0f;
        } else {
            acceleration.m_y = stickY * soValueAccesser::getConstantFloat(acc, 0xfa2, 0);
            if (acc->getKineticModule().getKineticType() == 0x20) {
                acc->getSituationModule().setKind(Situation_Air, false);
                acc->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Air, 0);
            }
        }
    }
    energy->m_accel = acceleration;
    energy->m_brake = braking;
    energy->m_speedTarget = target;
    energy->m_speed = retainedSpeed;
    if (energy->isEnable() == true && !energy->isSuspend()) energy->updateEnergy(acc);
    bool stop = false;
    if (energy->getSpeed().length() < priorLength) {
        Vec2f updated = energy->getSpeed();
        float cutoff = soValueAccesser::getConstantFloat(acc, 0xfa6, 0);
        if (updated.length() < cutoff) stop = true;
    }
    if (stop) energy->m_speed = Vec2f(0.0f, 0.0f);
}
void wnSonicSuperSonicKineticTransactor::updateEnergy(wnKineticEnergyGravity* energy, soModuleAccesser* acc) {
    if (acc->getKineticModule().getKineticType() == 0x21)
        updateEnergyFinalMoveCommon(energy, acc);
    else
        energy->updateEnergy(acc);
}
void wnSonicSuperSonicKineticTransactor::updateEnergyFinalMoveCommon(wnKineticEnergyGravity* energy, soModuleAccesser* acc) {
    double absoluteStick = __fabs(acc->getControllerModule().getStickY());
    float magnitude = absoluteStick;
    if (magnitude < soValueAccesser::getConstantFloat(acc, 0xfa4, 0))
        energy->m_speedY = soValueAccesser::getConstantFloat(acc, 0xfa7, 0);
    else
        energy->m_speedY = 0.0f;
}
// Next coherent draft: changeKinetic/changeKineticFinalMoveCommon/changeKineticSub
// once genuine pooled template parameter spelling and constructor offsets agree.
