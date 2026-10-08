#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_special_gyro.h>
#include <ft/robot/ft_robot_link_event.h>
#include <ft/robot/ft_robot_unk8.h>
#include <ft/ft_common_data_accesser.h>
#include <it/it_manager.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

// Work variables (HYPOTHESIS names, from how the statuses use them):
//   float 0x11000014  gyro charge; grows by 1 per frame while charging, the gyro is ready once it reaches const 0xfcf
//   float 0x21000004  set to const 0xfcf on entry
//   int   0x20000001 / 0x20000002  motion kinds of the two hands, chosen by how many gyros are already out
//   flag  0x22000011  the gyro item still has to be created   0x22000013  the stage already holds the maximum gyros

// HYPOTHESIS: the two unused file-local tags the original constructs before the status process (see ft_robot_unk8.h).
static ftRobotUnk8 s_unkTag0(0xff, 0);
static ftRobotUnk8 s_unkTag1(0xff, 1);

static soGenerateArticleManageModule& getArticles(soModuleAccesser* acc) {
    return *static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule);
}

void ftRobotStatusUniqProcessSpecialGyro::initStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x115: {
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0), 0x21000004);
        s32 taskId = moduleAccesser->getStageObject().m_taskId;
        int gyros = itManager::getInstance()->getItemNum(static_cast<itKind>(0x57), 0, taskId, -1);
        if (gyros < soValueAccesser::getConstantInt(moduleAccesser, 0x5dc7, 0)) {
            moduleAccesser->getWorkManageModule().setInt(0x1da, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e0, 0x20000002);
        } else {
            moduleAccesser->getWorkManageModule().setInt(0x1db, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e1, 0x20000002);
            moduleAccesser->getWorkManageModule().onFlag(0x22000013);
        }
        break;
    }
    case 0x11b: {
        ftRobotGyroLinkEvent event(0x839);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        break;
    }
    case 0x11c: {
        ftRobotGyroLinkEvent event(0x83a);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        break;
    }
    case 0x11d: {
        ftRobotGyroLinkEvent event(0x83b);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
            moduleAccesser->getWorkManageModule().setInt(0x1df, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e5, 0x20000002);
        } else {
            moduleAccesser->getWorkManageModule().setInt(0x1de, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e4, 0x20000002);
        }
        moduleAccesser->getEffectModule().removeCommon(0x1a);
        break;
    }
    }
}

// The gyro charge grows while the move is charged.
void ftRobotStatusUniqProcessSpecialGyro::execStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x11b:
        if (moduleAccesser->getWorkManageModule().getFloat(0x11000014) < soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0)) {
            moduleAccesser->getWorkManageModule().addFloat(1.0f, 0x11000014);
            moduleAccesser->getWorkManageModule().getFloat(0x11000014);
        }
        break;
    }
}

// BaseItem controls the gyro throw uses that the item header does not declare yet (the original calls them directly
// through relocations / the item's secondary vtable at +0x3c; HYPOTHESIS: the last one launches the item with a speed
// scaled by lr).
extern "C" void fn_27_28E108(BaseItem* item, float lr, Vec3f* speed, float scale);

// MATCH-ONLY: the original scales the launch speed in place with paired singles (inline asm in the shared vector code).
static inline void ftRobotScaleVec3f(register Vec3f* v, register float c) {
    register float fr1, fr0;
    // clang-format off
    asm {
        psq_l    fr0, Vec3f.m_x(v), 0, 0
        psq_l    fr1, Vec3f.m_z(v), 1, 0
        ps_muls0 fr0, fr0, c
        ps_muls0 fr1, fr1, c
        psq_st   fr0, Vec3f.m_x(v), 0, 0
        psq_st   fr1, Vec3f.m_z(v), 1, 0
    }
    // clang-format on
}

static void ftRobotGyroItemSlot(BaseItem* item, u32 offset) {
    typedef void (*Fn)(BaseItem*);
    void** table = *reinterpret_cast<void***>(reinterpret_cast<u8*>(item) + 0x3c);
    reinterpret_cast<Fn>(table[offset / sizeof(void*)])(item);
}

static void ftRobotGyroItemSlotCharge(BaseItem* item, u32 offset, int arg, float charge) {
    typedef void (*Fn)(BaseItem*, int, float);
    void** table = *reinterpret_cast<void***>(reinterpret_cast<u8*>(item) + 0x3c);
    reinterpret_cast<Fn>(table[offset / sizeof(void*)])(item, arg, charge);
}

// Throwing the gyro: creates the gyro item at the hand node, scaled with the fighter, and launches it with a speed
// that grows with the charge.
void ftRobotStatusUniqProcessSpecialGyro::execFixPos(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x11d:
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
            float lr = moduleAccesser->getPostureModule().getLr();
            Vec3f offset(lr * soValueAccesser::getConstantFloat(moduleAccesser, 0xfd2, 0), soValueAccesser::getConstantFloat(moduleAccesser, 0xfd3, 0), 0.0f);
            Vec3f handPos = moduleAccesser->getModelModule().getNodeGlobalPosition(0xa2, &offset, false, false);
            soGroundModule* ground = &moduleAccesser->getGroundModule();
            Vec3f safePos(moduleAccesser->getGroundModule().getCenterPos(0).m_x, ground->getCenterPos(0).m_y, ground->getZ());
            soResourceModule* resource = &moduleAccesser->getResourceModule();
            s32 taskId = moduleAccesser->getStageObject().m_taskId;
            int brresId = resource->getResourceIdAccesser()->getMdlResId();
            BaseItem* gyro = itManager::getInstance()->createBaseItem(&safePos, &handPos, lr, static_cast<itKind>(0x57), 0, taskId, taskId,
                                                                        resource, 1, brresId, 0, 0xffff, 0x14);
            if (gyro != NULL) {
                Vec3f speed(0.0f, 0.0f, 0.0f);
                float charge = moduleAccesser->getWorkManageModule().getFloat(0x11000014);
                speed.m_x = soValueAccesser::getConstantFloat(moduleAccesser, 0xfd0, 0) + charge * soValueAccesser::getConstantFloat(moduleAccesser, 0xfd1, 0);
                ftRobotScaleVec3f(&speed, lr);
                gyro->setOwnerScale(moduleAccesser->getPostureModule().getScale());
                ftRobotGyroItemSlot(gyro, 0xb4);
                ftRobotGyroItemSlotCharge(gyro, 0x260, 0, charge);
                fn_27_28E108(gyro, lr, &speed, 1.0f);
            }
            moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000014);
            moduleAccesser->getWorkManageModule().offFlag(0x22000011);
        }
        break;
    }
}

void ftRobotStatusUniqProcessSpecialGyro::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    switch (nextStatus) {
    case 0x0:
    case 0xe:
    case 0x1f:
    case 0x20:
        // Leaving for a plain ground/air status keeps the ready glow while the gyro is fully charged.
        if (moduleAccesser->getWorkManageModule().getFloat(0x11000014) >= soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0)) {
            moduleAccesser->getEffectModule().reqCommon(0.0f, 0x1a);
        }
        break;
    case 0x11b:
    case 0x11c:
    case 0x11d:
        return;
    default:
        moduleAccesser->getEffectModule().removeCommon(0x1a);
        moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000014);
        break;
    }
    // The articles tied to the gyro move are removed from the data record's article ids.
    u8* data = reinterpret_cast<u8*>(g_ftCommonDataAccesser.getData(Fighter_Robot));
    getArticles(moduleAccesser).removeExist(*reinterpret_cast<int*>(data + 0x90), 0);
    data = reinterpret_cast<u8*>(g_ftCommonDataAccesser.getData(Fighter_Robot));
    getArticles(moduleAccesser).removeExist(*reinterpret_cast<int*>(data + 0xa0), 0);
}

ftRobotStatusUniqProcessSpecialGyro g_ftRobotStatusUniqProcessSpecialGyro;
