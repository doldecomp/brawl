#define FT_MARTH_RUNTIME_HELPERS
#define FT_MARTH_PHOTO_CALLBACK_NOINLINE
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
#include <ft/marth/ft_marth_status_uniq_process.h>


// The shared shield declarations are opaque. These adapters describe the fields
// populated by Marth before passing the data to the collision shield module.
struct MarthCounterShieldData {
    Vec3f unk0;
    Vec3f unkC;
    float radius;
    u32 nodeId : 9;
    u32 unk22 : 1;
    u32 unk0_22 : 22;
};
struct MarthCounterShieldGroupData {
    MarthCounterShieldData* shields;
    u32 count;
    u32 unk8_28 : 4;
    u32 unk8_0 : 28;
    u32 unkC[3];
};
static_assert(sizeof(MarthCounterShieldData) == sizeof(soCollisionShieldData), "Shield layout");
static_assert(sizeof(MarthCounterShieldGroupData) == sizeof(soCollisionShieldGroupData), "Shield group layout");



#define FT_BC ftMarthBuildConfig
#include <ft/builder/ft_builder_noinline.h>

// Status teardown destroys its owned change-request queue before observers.
#pragma dont_inline on
soResourceIdAccesser::~soResourceIdAccesser() { }
template soArrayVector<s32, 8>::~soArrayVector();
#pragma dont_inline off
soStatusModuleImpl::~soStatusModuleImpl() { }

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
                                         nwMotionInstHeap),
    m_data(g_ftCommonDataAccesser.getData(Fighter_Marth)) {
    // Register the fifteen character-specific status processes in action order.
    soStatusUniqProcess* processes[15] = {0};
    processes[0] = &g_ftMarthStatusUniqProcessSpecialNStart;
    processes[1] = &g_ftMarthStatusUniqProcessSpecialS;
    processes[2] = &g_ftMarthStatusUniqProcessSpecialHi;
    processes[3] = &g_ftMarthStatusUniqProcessSpecialLw;
    processes[4] = &g_ftMarthStatusUniqProcessFinal;
    processes[5] = &g_ftMarthStatusUniqProcessSpecialNLoop;
    processes[6] = &g_ftMarthStatusUniqProcessSpecialNEnd;
    processes[8] = &g_ftMarthStatusUniqProcessSpecialS;
    processes[9] = &g_ftMarthStatusUniqProcessSpecialS;
    processes[10] = &g_ftMarthStatusUniqProcessSpecialS;
    processes[11] = &g_ftMarthStatusUniqProcessSpecialLw;
    processes[12] = &g_ftMarthStatusUniqProcessFinal;
    processes[13] = &g_ftMarthStatusUniqProcessFinal;
    processes[14] = &g_ftMarthStatusUniqProcessFinal;
    m_moduleAccesser->getStatusModule().addRangeUniqProc(processes, 15);

    const ftMarthExtendParamClass5* param =
        static_cast<const ftMarthExtendParamClass5*>(m_data->extendParam[4]);
    MarthCounterShieldData shield;
    shield.unk0.m_x = param->unk4;
    shield.unk0.m_y = param->unk8;
    shield.unk0.m_z = param->unkC;
    shield.unkC.m_x = param->unk4;
    shield.unkC.m_y = param->unk8;
    shield.unkC.m_z = param->unkC;
    shield.radius = param->unk10;
    shield.nodeId = param->unk0;
    shield.unk22 = 1;
    MarthCounterShieldGroupData group;
    group.unk8_28 = 0;
    group.shields = &shield;
    group.count = 1;
    m_moduleAccesser->getCollisionShieldModule().add(
        reinterpret_cast<soCollisionShieldGroupData*>(&group), 1);
}

ftMarth::~ftMarth() { }

void ftMarth::processUpdate() { Fighter::processUpdate(); }

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
