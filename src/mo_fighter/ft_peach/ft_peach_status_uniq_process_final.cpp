#include <ft/peach/ft_peach.h>
#include <ft/ft_value_accesser.h>
#include <ft/ft_resource_id_accesser_impl.h>
#include <so/so_rot_utility.h>
#include <ft/peach/ft_peach_status_uniq_process_final.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_slow_manager.h>
#include <gf/gf_task_scheduler.h>
#include <gm/gm_global.h>
#include <if/if_mngr.h>
#include <it/it_manager.h>
#include <mt/mt_prng.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <so/so_external_value_accesser.h>
#include <so/so_module_accesser.h>
#include <st/stage.h>
#include <so/so_value_accesser.h>
#include <so/status/so_status_module_impl.h>
#include <snd/snd_system.h>
#include <types.h>

ftPeachStatusUniqProcessFinal g_ftPeachStatusUniqProcessFinal;

// Combo module is still opaque in the local SDK shadow. Native callsites use
// enum +0x88 and virtual slots +0xC4/+0x68 with these integer arguments.
static void peachComboSetMode(soModuleAccesser* accesser, int mode) {
    void* combo = accesser->m_enumerationStart->m_comboModule;
    void** vtable = *reinterpret_cast<void***>(combo);
    typedef void (*Call)(void*, int);
    reinterpret_cast<Call>(vtable[0xC4 / 4])(combo, mode);
}

static void peachComboClear(soModuleAccesser* accesser) {
    void* combo = accesser->m_enumerationStart->m_comboModule;
    void** vtable = *reinterpret_cast<void***>(combo);
    typedef void (*Call)(void*, int, int, int);
    reinterpret_cast<Call>(vtable[0x68 / 4])(combo, 0, 1, 1);
}

static bool peachIsWide() {
    // Native reads bit 0 of the menu record byte at +0x28.
    return (*(reinterpret_cast<u8*>(g_GameGlobal->getGlobalRecordMenuDatap()) + 0x28) & 1) != 0;
}

void ftPeachStatusUniqProcessFinal::initStatus(soModuleAccesser* accesser) {
    const float firstMinAngle = soValueAccesser::getConstantFloat(accesser, 0xFBE, 0);
    const float firstMaxAngle = soValueAccesser::getConstantFloat(accesser, 0xFBF, 0);
    const float firstRandom = randf();
    const float firstAngle = (firstMaxAngle - firstMinAngle) * firstRandom + firstMinAngle;
    accesser->getWorkManageModule().setFloat(firstAngle, 0x21000004);

    const float centerAngle = soValueAccesser::getConstantFloat(accesser, 0xFBD, 0);
    accesser->getWorkManageModule().setFloat(centerAngle, 0x21000005);

    const float secondMinAngle = soValueAccesser::getConstantFloat(accesser, 0xFBE, 0);
    const float secondMaxAngle = soValueAccesser::getConstantFloat(accesser, 0xFBF, 0);
    const float secondRandom = randf();
    const float secondAngle = (secondMaxAngle - secondMinAngle) * secondRandom + secondMinAngle;
    accesser->getWorkManageModule().setFloat(secondAngle, 0x21000006);

    const int itemCount = soValueAccesser::getConstantInt(accesser, 0x5DC3, 0);
    accesser->getWorkManageModule().setInt(itemCount, 0x20000002);

    createInfo(accesser);
    peachComboSetMode(accesser, 0);
    Vec3f offset;
    offset.m_x = offset.m_y = offset.m_z = 0.0f;
    Vec3f rotation;
    rotation.m_x = rotation.m_y = rotation.m_z = 0.0f;
    const int effectHandle = accesser->getEffectModule().req(static_cast<EfID>(0xED000A), &offset, &rotation, 1.0f, 0, -1);
    peachComboSetMode(accesser, 1);
    accesser->getWorkManageModule().setInt(effectHandle, 0x10000042);
    accesser->getVisibilityModule().setStatusDefault(0, 0xFF, true);
    ftPeach* peach = dynamic_cast<ftPeach*>(&accesser->getStageObject());
    if (peach != NULL) peach->addCallback();
}

void ftPeachStatusUniqProcessFinal::execStatus(soModuleAccesser* accesser) {
    soWorkManageModule& work = accesser->getWorkManageModule();
    Vec3f rotation = accesser->getPostureModule().getRot(1);
    rotation.m_x += work.getFloat(0x21000004);
    rotation.m_y += work.getFloat(0x21000005);
    rotation.m_z += work.getFloat(0x21000006);
    Vec3f clamped = soRotUtility::clampDeg(rotation);
    accesser->getPostureModule().setRot(&clamped, 1);

    if (work.isFlag(0x22000010)) {
        if (work.getInt(0x20000003) > 0 || work.getInt(0x20000002) <= 0) {
            work.decInt(0x20000003);
        } else {
            Vec3f position = soExternalValueAccesser::getPos(&accesser->getStageObject());
            Stage::getInstance()->getRandItemPos(&position);
            BaseItem* item = itManager::getInstance()->createItem(&position,
                accesser->getPostureModule().getRotYLr(), Item_Food, 0x1C,
                accesser->getStageObject().m_taskId, NULL, 0, 0xFFFF, 0, 0xFFFF);
            if (item != NULL && Stage::getInstance() != NULL) {
                Vec3f appearPosition = position;
                item->appear(&appearPosition, 0, 0.0f);
                work.decInt(0x20000002);
                work.setInt(soValueAccesser::getConstantInt(accesser, 0x5DC4, 0), 0x20000003);
            }
        }
    }
}

void ftPeachStatusUniqProcessFinal::execFixPos(soModuleAccesser* accesser) {
    if (accesser->getWorkManageModule().isFlag(0x22000011) == 1) setOutAction(accesser);
}

void ftPeachStatusUniqProcessFinal::exitStatus(soModuleAccesser* accesser, int nextStatus) {
    if (nextStatus == 0 || nextStatus == 0xE) setOutAction(accesser);
    else destroyInfo(accesser);
    if (g_sndSystem != NULL) g_sndSystem->playSE(SndID(0x1B4A), -1, 0, 0, -1);
}

void ftPeachStatusUniqProcessFinal::setOutAction(soModuleAccesser* accesser) {
    soWorkManageModule& work = accesser->getWorkManageModule();
    work.onFlag(0x22000011);
    gfTask* base = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Info, work.getInt(0x10000041));
    IfPeachFinalTask* task = dynamic_cast<IfPeachFinalTask*>(base);
    if (task != NULL && !task->m_actionActive) {
        task->setAction(peachIsWide() ? 3 : 1);
        task->m_actionActive = true;
    }
}

bool ftPeachStatusUniqProcessFinal::createInfo(soModuleAccesser* accesser) {
    soWorkManageModule& work = accesser->getWorkManageModule();
    if (work.getInt(0x10000041) != 0) destroyInfo(accesser);
    ftResourceIdAccesserImpl& resourceIdAccesser =
        dynamic_cast<ftResourceIdAccesserImpl&>(*accesser->getResourceModule().getResourceIdAccesser());
    const int resourceId = resourceIdAccesser.getFinalResId();
    void* data = accesser->getResourceModule().getFile(resourceId, ARCNodeType(0), -1);
    if (data == NULL) return false;
    IfPeachFinalTask* task = IfPeachFinalTask::create(data, Heaps::HeapType(0x1F),
        accesser->getStageObject().m_taskId, true);
    if (task == NULL) return false;
    work.setInt(task->m_taskId, 0x10000041);
    task->setAction(peachIsWide() ? 2 : 0);
    return true;
}

void ftPeachStatusUniqProcessFinal::destroyInfo(soModuleAccesser* accesser) {
    soWorkManageModule& work = accesser->getWorkManageModule();
    const int taskId = work.getInt(0x10000041);
    if (taskId != 0) {
        gfTask* task = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Info, taskId);
        if (task != NULL) {
            task->exit();
            peachComboClear(accesser);
        }
        work.setInt(0, 0x10000041);
    }
    work.setInt(0, 0x10000042);
}
