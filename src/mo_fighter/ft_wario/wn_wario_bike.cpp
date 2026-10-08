#include <wn/wario/wn_wario_bike_kinetic_transactor.h>
#include <wn/wario/wn_wario_bike.h>
#include <so/stop/so_stop_module_impl.h>
#include <ft/ft_entry.h>
#include <gf/gf_task_scheduler.h>
#include <so/damage/so_damage_util_actor.h>
#include <so/so_external_value_accesser.h>
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

void wnWarioBike::notifyEventLink(soLinkEventArgs* eventInfo,
                                  soModuleAccesser* accesser,
                                  StageObject* other, int unk4) {
    soLinkModule& link = accesser->getLinkModule();
    bool bikeParent = false;
    if (other->getCategory() == gfTask::Category_Fighter) {
        int kind = other->soGetSubKind();
        if (kind == Fighter_Wario || kind == Fighter_WarioMan) {
            bikeParent = link.isLink(3) && link.getParentTaskId(3) == other->getId();
            if (bikeParent) {
                switch (eventInfo->m_eventKind) {
                case 0:
                    accesser->getWorkManageModule().onFlag(0x2200000B);
                    break;
                case 60:
                    link.setModelConstraintAttribute(3, false);
                    if (link.isModelConstraint()) {
                        link.removeModelConstraint(true);
                        accesser->getStatusModule().changeStatusRequest(13, accesser);
                    }
                    break;
                case 1109: {
                    soKineticEnergyNormal* normal =
                        dynamic_cast<soKineticEnergyNormal*>(
                            accesser->getKineticModule().getEnergy(0));
                    wnKineticEnergyGravity* gravity =
                        dynamic_cast<wnKineticEnergyGravity*>(
                            accesser->getKineticModule().getEnergy(1));
                    u8* eventBytes = reinterpret_cast<u8*>(eventInfo);
                    Vec2f normalSpeed(
                        *reinterpret_cast<float*>(eventBytes + 8), 0.0f);
                    Vec2f::copy(normal->m_speed, normalSpeed);
                    gravity->m_speedY = *reinterpret_cast<float*>(eventBytes + 0xC);

                    Vec3f parentPosition =
                        link.getParentModelNodeGlobalPosition(3, static_cast<u32>(0), false);
                    accesser->getPostureModule().setPos(&parentPosition);
                    accesser->getPostureModule().setLr(link.getParentLr(3));
                    accesser->getPostureModule().updateRotYLr();
                    link.removeModelConstraint(true);
                    link.setModelConstraintAttribute(3, true);
                    link.setAttribute(
                        3, static_cast<soLinkConnection::Attribute>(3), false);

                    gfTaskScheduler::getInstance()->changeTaskPriorityRequest(
                        m_taskId, 5);
                    accesser->getWorkManageModule().onFlag(0x12000002);
                    accesser->getWorkManageModule().onFlag(0x22000000);
                    accesser->getStatusModule().changeStatusRequest(2, accesser);
                    break;
                }
                case 1110:
                    accesser->getStatusModule().changeStatusRequest(9, accesser);
                    break;
                case 1111: {
                    Vec2f speed = accesser->getKineticModule().getSumSpeed(
                        soKineticEnergy::AttributeFlag(1));
                    Vec2f::copy(*reinterpret_cast<Vec2f*>(reinterpret_cast<u8*>(eventInfo) + 8), speed);
                    if (accesser->getSituationModule().isSituationChanged())
                        accesser->getStatusModule().changeStatusRequest(13, accesser);
                    else
                        accesser->getStatusModule().changeStatusRequest(10, accesser);
                    break;
                }
                case 1112: {
                    Vec2f speed = accesser->getKineticModule().getSumSpeed(
                        soKineticEnergy::AttributeFlag(1));
                    Vec2f::copy(*reinterpret_cast<Vec2f*>(reinterpret_cast<u8*>(eventInfo) + 8), speed);
                    break;
                }
                case 1113:
                    accesser->getStatusModule().changeStatusRequest(11, accesser);
                    break;
                case 1114: {
                    if (link.isModelConstraint())
                        link.removeModelConstraint(true);

                    soKineticEnergyNormal* normal =
                        dynamic_cast<soKineticEnergyNormal*>(
                            accesser->getKineticModule().getEnergy(0));
                    float scale = m_param->unk90;
                    Vec2f speed;
                    speed.m_x = *reinterpret_cast<float*>(
                        reinterpret_cast<u8*>(eventInfo) + 8) * scale;
                    speed.m_y = *reinterpret_cast<float*>(
                        reinterpret_cast<u8*>(eventInfo) + 0xC) * scale;
                    Vec2f::copy(normal->m_speed, speed);
                    // HYPOTHESIS: native sets the high bit of energy byte +5;
                    // the corresponding base-class state has no named field.
                    reinterpret_cast<u8*>(normal)[5] |= 0x80;
                    accesser->getKineticModule().getEnergy(1);
                    accesser->getStatusModule().changeStatusRequest(13, accesser);
                    break;
                }
                case 1115:
                    accesser->getStatusModule().changeStatusRequest(14, accesser);
                    break;
                default:
                    break;
                }
            }
        }
    }

    // The secondary path handles events attached through link index 5.
    if (!bikeParent && link.isLink(5) && link.getParentTaskId(5) == other->getId()) {
        if (eventInfo->m_eventKind == 0) {
            accesser->getWorkManageModule().onFlag(0x2200000B);
        } else if (eventInfo->m_eventKind == StageObject::Link::Event_Touch_Item &&
                   link.isLinked(6)) {
            StageObject* linked = *reinterpret_cast<StageObject**>(
                reinterpret_cast<u8*>(eventInfo) + 8);
            int linkedKind = linked->soGetSubKind();
            if (linkedKind == 5 || linkedKind == 15)
                link.sendEventParents(3, *eventInfo);
        }
    }

    Weapon::notifyEventLink(eventInfo, accesser, other, unk4);
}

void wnWarioBike::notifyEventCollisionAttack(float power, soCollisionLog* log,
                                             soModuleAccesser* accesser) {
    gfTask* task = gfTaskScheduler::getInstance()->getTaskById(
        log->m_taskCategory, log->m_taskId);
    soCollisionAttackData* attackData = accesser->getCollisionAttackModule().getData(
        log->m_damageIndex, log->m_isAbsolute);
    int frames = soDamageUtilActor::calcHitStopFrame(
        power, 1.0, 1.0, accesser, attackData, 0);

    // Native only substitutes the target reaction frame for the log's
    // reaction-frame case; the task is looked up from the collision log.
    if (*(u8*)((u8*)log + 0x21) == 1 && task != nullptr) {
        StageObject* target = dynamic_cast<StageObject*>(task);
        soCollisionHitModule* hit =
            soExternalValueAccesser::getCollisionHitModule(target);
        if (hit->isReactionFrame()) frames = hit->getReactionFrame();
    }

    soWorkManageModule& work = accesser->getWorkManageModule();
    int pending = work.getInt(0x10000007);
    if (pending < frames) pending = frames;
    work.setInt(pending, 0x10000007);
}
