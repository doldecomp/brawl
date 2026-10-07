#define FT_MARTH_COLLISION_VEC3F_NOINLINE
#include <ft/ft_class_info_impl.h>
#include <ft/marth/ft_marth.h>
#include <ft/marth/ft_marth_extend_param_accesser.h>
#include <if/if_marth_final.h>
#include <so/so_value_accesser.h>
#include <so/so_external_value_accesser.h>
#include <gf/gf_task_scheduler.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_external_value_accesser.h>
#include <mt/mt_prng.h>
#include <math.h>

#define FT_BC ftMarthBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftMarthExtendParamAccesser g_ftMarthExtendParamAccesser;

ftClassInfoImpl<Fighter_Marth, ftMarth> g_ftClassInfoMarth;

ftMarth::ftMarth(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftMarthBuildConfig>(entryId,
                                         Fighter_Marth,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftMarth is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftMarthInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
    soPostureModuleBuilder<soPostureModuleBuildConfig<1, soPostureModuleImpl> > postureBuilder(nullptr, nullptr);
    soCollisionAttackModuleBuilder<soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 5, 2, soCollisionAttackModuleImpl, 5, true, true> > attackBuilder(nullptr, 0, gfTask::Category(0), nullptr);
    soCollisionHitModuleBuilder<soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 20, 1, soCollisionHitModuleImpl, 0x3ff, true> > hitBuilder(nullptr, 0, gfTask::Category(0), nullptr);
}
soInsideEventManageModuleBuilder<ftMarthInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

#pragma dont_inline off

void ftMarth::notifyEventCollisionShield(soCollisionAttackModule* attackModule, float power, soCollisionLog* collisionLog, int groupIndex, float posX, float posY, soModuleAccesser* moduleAccesser) {
    // Counter records the first hit on its counter shield for the retaliation.
    if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x115 && groupIndex == 1) {
        if (!m_moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
            m_moduleAccesser->getWorkManageModule().onFlag(0x22000013);
            m_moduleAccesser->getWorkManageModule().setFloat(power, 0x21000004);
            soCollisionAttackData* attackData = attackModule->getData(collisionLog->m_collsionIndex, collisionLog->m_isAbsolute);
            float lr = m_moduleAccesser->getDamageModule().getDamageLr(posX, posY, attackModule, attackData, collisionLog->m_collsionIndex, collisionLog->m_isAbsolute);
            m_moduleAccesser->getWorkManageModule().setFloat(lr, 0x21000005);
        }
        StageObject& attacker = dynamic_cast<StageObject&>(*gfTaskScheduler::getInstance()->getTask(collisionLog->m_taskId));
        soStopModule* stop = soExternalValueAccesser::getStopModule(&attacker);
        stop->setHitStopFrameFix(soValueAccesser::getConstantInt(m_moduleAccesser, 0x5dc3, 0));
    }
    Fighter::notifyEventCollisionShield(attackModule, power, collisionLog, groupIndex, posX, posY, moduleAccesser);
}

bool ftMarth::notifyEventCollisionShieldCheck() {
    if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x115 &&
        m_moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
        m_moduleAccesser->getWorkManageModule().offFlag(0x22000013);
        m_moduleAccesser->getStatusModule().changeStatusRequest(0x11d, m_moduleAccesser);
        m_moduleAccesser->getPostureModule().setLr(m_moduleAccesser->getWorkManageModule().getFloat(0x21000005));
        m_moduleAccesser->getPostureModule().updateRotYLr();
        int hitStop = soValueAccesser::getConstantInt(m_moduleAccesser, 0x5dc3, 0);
        m_moduleAccesser->getStopModule().setHitStopFrame(hitStop, false);
        return true;
    }
    return Fighter::notifyEventCollisionShieldCheck();
}

void ftMarth::notifyEventCollisionAttackFighter(soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser) {
    int count;
    float sine;
    if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x11e) {
        gfTask* task = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Fighter, collisionLog->m_taskId);
        if (task != NULL) {
            Fighter& target = dynamic_cast<Fighter&>(*task);
            if (ftExternalValueAccesser::getsoCollisionHitModule(&target)->getTotalStatus(0) != 3) {
                m_moduleAccesser->getWorkManageModule().onFlag(0x22000011);
            }
        }
    } else if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x120) {
        gfTask* task = gfTaskScheduler::getInstance()->getTask(collisionLog->m_taskId);
        if (task->m_taskCategory == gfTask::Category_Fighter) {
            Fighter& target = dynamic_cast<Fighter&>(*task);
            if (ftExternalValueAccesser::getsoCollisionHitModule(&target)->getTotalStatus(0) == 0) {
                count = m_moduleAccesser->getWorkManageModule().getInt(0x20000016);
                if (count < 6) {
                    // Temporarily link the target to place its numbered HP window.
                    moduleAccesser->getLinkModule().link(6, collisionLog->m_taskId);
                    ftKind kind = ftKind(m_moduleAccesser->getStageObject().soGetSubKind());
                    u32 resId = g_ftCommonDataAccesser.getFinalResId(kind);
                    void* resourceData = m_moduleAccesser->getResourceModule().getBinFile(resId, 0, -1);
                    IfMarthFinalTask* window = IfMarthFinalTask::create(resourceData, Heaps::HeapType(0x1f), count + 1);
                    if (gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Fighter, collisionLog->m_taskId) != NULL) {
                        float angle = randi(360);
                        float radius = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbe, 0);
                        sine = sin(angle);
                        float cosine = cos(angle);
                        // The original computes this offset but places the window without it.
                        Vec3f unusedOffset(radius * cosine, radius * sine, 0.0f);
                        Vec3f pos = moduleAccesser->getLinkModule().getParentModelNodeGlobalPosition(6, u32(0), false);
                        pos.m_y += -2.0f;
                        window->setPosConv(&pos);
                    }
                    window->dispOn(0);
                    window->setAnim(0);
                    m_moduleAccesser->getWorkManageModule().setInt(window->m_taskId, 0x20000004 + count);
                    m_moduleAccesser->getWorkManageModule().offFlag(0x22000012);
                    m_moduleAccesser->getWorkManageModule().addInt(1, 0x20000016);
                    moduleAccesser->getLinkModule().unlink(6);
                }
                m_moduleAccesser->getWorkManageModule().onFlag(0x22000012);
            }
        }
    }
}

bool ftMarth::notifyEventCollisionAttackCheck(u32 flags) {
    // A confirmed Final Smash hit requests the next attack phase.
    if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x11e &&
        m_moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
        m_moduleAccesser->getStatusModule().changeStatusRequest(0x120, m_moduleAccesser);
        return true;
    }
    if (m_moduleAccesser->getStatusModule().getStatusKind() == 0x120 &&
        m_moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        m_moduleAccesser->getWorkManageModule().offFlag(0x22000012);
    }
    return Fighter::notifyEventCollisionAttackCheck(flags);
}

void ftMarth::photoMoved() {
    soModuleAccesser* moduleAccesser = m_moduleAccesser;
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x120) {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                if (window != NULL) {
                    window->setVisibilityWhole(false);
                }
            }
        }
    }
}

void ftMarth::photoExit() {
    soModuleAccesser* moduleAccesser = m_moduleAccesser;
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x120) {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                if (window != NULL) {
                    window->setVisibilityWhole(true);
                }
            }
        }
    }
}
