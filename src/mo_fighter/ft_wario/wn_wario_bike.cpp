#include <wn/wario/wn_wario_bike_kinetic_transactor.h>
#include <wn/wario/wn_wario_bike.h>
#include <so/stop/so_stop_module_impl.h>
#include <wn/wn_kinetic_transactor.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

void wnWarioBikeKineticTransactor::changeKinetic(
    int kineticType, wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    if (kineticType <= 31) {
        wnKineticTransactor::changeKinetic(kineticType, pools, accesser);
        return;
    }
    if (kineticType > 40) return;

    wnWarioBikeKineticTransactor self = {};
    switch (kineticType) {
    case 32: self.changeKineticSub(pools, accesser); break;
    case 33: self.changeKineticSub1(pools, accesser); break;
    case 34: self.changeKineticSub2(pools, accesser); break;
    case 35: self.changeKineticSub3(pools, accesser); break;
    case 36: self.changeKineticSub4(pools, accesser); break;
    case 37: self.changeKineticSub5(pools, accesser); break;
    case 38: self.changeKineticSub6(pools, accesser); break;
    case 39: self.changeKineticSub7(pools, accesser); break;
    case 40: self.changeKineticSub8(pools, accesser); break;
    }
}

void wnWarioBikeKineticTransactor::changeKineticSub(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* energy =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    float brake = soValueAccesser::getConstantFloat(accesser, 4004, 0);
    float target = soValueAccesser::getConstantFloat(accesser, 4003, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f targetVector(target, 0.0f);
    Vec2f::copy(energy->m_accel, zero);
    Vec2f::copy(energy->m_brake, brakeVector);
    Vec2f::copy(energy->m_speedTarget, targetVector);
    Vec2f::copy(energy->m_speedLimit, targetVector);
    energy->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub1(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* normal =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    wnKineticEnergyGravity* gravity =
        static_cast<wnWarioBikeGravityPool&>(*pools).getSub().getInstanceAt(0);
    Vec2f speed = accesser->getKineticModule().getSumSpeed(
        soKineticEnergy::AttributeFlag(1));
    float brake = soValueAccesser::getConstantFloat(accesser, 4007, 0);
    float gravityAcceleration = soValueAccesser::getConstantFloat(accesser, 4009, 0);
    float target = soValueAccesser::getConstantFloat(accesser, 4006, 0);
    float gravitySpeedLimit = soValueAccesser::getConstantFloat(accesser, 4010, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f targetVector(target, 0.0f);
    Vec2f::copy(normal->m_speed, speed);
    Vec2f::copy(normal->m_accel, zero);
    Vec2f::copy(normal->m_brake, brakeVector);
    Vec2f::copy(normal->m_speedTarget, targetVector);
    Vec2f::copy(normal->m_speedLimit, targetVector);
    normal->enable();
    gravity->m_speedY = speed.m_x;
    gravity->m_gravity = -gravityAcceleration;
    gravity->m_speedLimit = gravitySpeedLimit;
    gravity->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub2(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* energy =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    float value = soValueAccesser::getConstantFloat(accesser, 4003, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f paired(value, value);
    Vec2f::copy(energy->m_accel, zero);
    Vec2f::copy(energy->m_brake, zero);
    Vec2f::copy(energy->m_speedTarget, paired);
    Vec2f::copy(energy->m_speedLimit, paired);
    energy->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub3(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* energy =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    float value = soValueAccesser::getConstantFloat(accesser, 4027, 0);
    float limit = soValueAccesser::getConstantFloat(accesser, 4003, 0);
    Vec2f acceleration(-value, 0.0f);
    Vec2f brake(value, 0.0f);
    Vec2f zero(0.0f, 0.0f);
    Vec2f speedLimit(limit, 0.0f);
    Vec2f::copy(energy->m_accel, acceleration);
    Vec2f::copy(energy->m_brake, brake);
    Vec2f::copy(energy->m_speedTarget, zero);
    Vec2f::copy(energy->m_speedLimit, speedLimit);
    energy->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub4(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* energy =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    float brake = soValueAccesser::getConstantFloat(accesser, 4028, 0);
    float limit = soValueAccesser::getConstantFloat(accesser, 4003, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f limitVector(limit, 0.0f);
    Vec2f::copy(energy->m_accel, zero);
    Vec2f::copy(energy->m_brake, brakeVector);
    Vec2f::copy(energy->m_speedTarget, zero);
    Vec2f::copy(energy->m_speedLimit, limitVector);
    energy->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub5(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* normal =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    wnKineticEnergyGravity* gravity =
        static_cast<wnWarioBikeGravityPool&>(*pools).getSub().getInstanceAt(0);
    Vec2f speed = accesser->getKineticModule().getSumSpeed(
        soKineticEnergy::AttributeFlag(1));
    float brake = soValueAccesser::getConstantFloat(accesser, 4029, 0);
    float gravityAcceleration = soValueAccesser::getConstantFloat(accesser, 4009, 0);
    // MATCH-ONLY: the native queries constant 4008 and discards its result.
    soValueAccesser::getConstantFloat(accesser, 4008, 0);
    float limit = soValueAccesser::getConstantFloat(accesser, 4006, 0);
    float gravitySpeedLimit = soValueAccesser::getConstantFloat(accesser, 4010, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f limitVector(limit, 0.0f);
    Vec2f::copy(normal->m_speed, speed);
    Vec2f::copy(normal->m_accel, zero);
    Vec2f::copy(normal->m_brake, brakeVector);
    Vec2f::copy(normal->m_speedTarget, zero);
    Vec2f::copy(normal->m_speedLimit, limitVector);
    normal->enable();
    gravity->m_speedY = speed.m_x;
    gravity->m_gravity = -gravityAcceleration;
    gravity->m_speedLimit = gravitySpeedLimit;
    gravity->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub6(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* normal =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    Vec2f speed = accesser->getKineticModule().getSumSpeed(
        soKineticEnergy::AttributeFlag(1));
    float brake = soValueAccesser::getConstantFloat(accesser, 4028, 0);
    float target = soValueAccesser::getConstantFloat(accesser, 4003, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f targetVector(target, 0.0f);
    Vec2f::copy(normal->m_speed, speed);
    Vec2f::copy(normal->m_accel, zero);
    Vec2f::copy(normal->m_brake, brakeVector);
    Vec2f::copy(normal->m_speedTarget, targetVector);
    Vec2f::copy(normal->m_speedLimit, targetVector);
    normal->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub7(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* normal =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    wnKineticEnergyGravity* gravity =
        static_cast<wnWarioBikeGravityPool&>(*pools).getSub().getInstanceAt(0);
    Vec2f speed = accesser->getKineticModule().getSumSpeed(
        soKineticEnergy::AttributeFlag(1));
    float brake = soValueAccesser::getConstantFloat(accesser, 4029, 0);
    float gravityAcceleration = soValueAccesser::getConstantFloat(accesser, 4009, 0);
    float limit = soValueAccesser::getConstantFloat(accesser, 4006, 0);
    float gravitySpeedLimit = soValueAccesser::getConstantFloat(accesser, 4010, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f limitVector(limit, 0.0f);
    Vec2f::copy(normal->m_speed, speed);
    Vec2f::copy(normal->m_accel, zero);
    Vec2f::copy(normal->m_brake, brakeVector);
    Vec2f::copy(normal->m_speedTarget, zero);
    Vec2f::copy(normal->m_speedLimit, limitVector);
    normal->enable();
    gravity->m_speedY = speed.m_x;
    gravity->m_gravity = -gravityAcceleration;
    gravity->m_speedLimit = gravitySpeedLimit;
    gravity->enable();
}

void wnWarioBikeKineticTransactor::changeKineticSub8(
    wnWarioBikeKineticPools* pools, soModuleAccesser* accesser) {
    soKineticEnergyNormal* normal =
        static_cast<wnWarioBikeNormal0Pool&>(*pools).getSub().getInstanceAt(0);
    wnKineticEnergyGravity* gravity =
        static_cast<wnWarioBikeGravityPool&>(*pools).getSub().getInstanceAt(0);
    Vec2f speed = accesser->getKineticModule().getSumSpeed(
        soKineticEnergy::AttributeFlag(1));
    float brake = soValueAccesser::getConstantFloat(accesser, 4029, 0);
    float gravityAcceleration = soValueAccesser::getConstantFloat(accesser, 4009, 0);
    float limit = soValueAccesser::getConstantFloat(accesser, 4006, 0);
    float gravitySpeedLimit = soValueAccesser::getConstantFloat(accesser, 4010, 0);
    Vec2f zero(0.0f, 0.0f);
    Vec2f brakeVector(brake, 0.0f);
    Vec2f limitVector(limit, 0.0f);
    Vec2f::copy(normal->m_speed, speed);
    Vec2f::copy(normal->m_accel, zero);
    Vec2f::copy(normal->m_brake, brakeVector);
    Vec2f::copy(normal->m_speedTarget, zero);
    Vec2f::copy(normal->m_speedLimit, limitVector);
    normal->enable();
    gravity->m_speedY = speed.m_x;
    gravity->m_gravity = -gravityAcceleration;
    gravity->m_speedLimit = gravitySpeedLimit;
    gravity->enable();
}

void wnWarioBikeKineticTransactor::updateEnergy1(
    wnKineticEnergyGravity* energy, soModuleAccesser* accesser) {
    if (energy->isEnable() == true && energy->isSuspend() == false)
        energy->updateEnergy(accesser);
}


void wnWarioBike::processUpdate() {
    if (m_moduleAccesser->getWorkManageModule().isFlag(0x2200000B)) {
        m_moduleAccesser->getWorkManageModule().offFlag(0x2200000B);
        deactivate(false);
        return;
    }

    Weapon::processUpdate();
    m_moduleAccesser->getWorkManageModule().setFloat(
        m_moduleAccesser->getPostureModule().getLr(), 0x21000008);
}

bool wnWarioBike::notifyEventCollisionAttackCheck(u32 flags) {
    (void)flags;
    int count = m_moduleAccesser->getWorkManageModule().getInt(0x10000007);
    if (count > 0) {
        struct CollisionAttackEvent : soLinkEventArgs {
            int m_count;
            u8 m_unk0C;

            explicit CollisionAttackEvent(int value)
                : soLinkEventArgs(2115), m_count(value), m_unk0C(0) {}
        } event(count);

        m_moduleAccesser->getLinkModule().sendEventParents(3, event);
        m_moduleAccesser->getStopModule().setHitStopFrame(count, false);
        m_moduleAccesser->getWorkManageModule().setInt(0, 0x10000007);
    }
    return false;
}
