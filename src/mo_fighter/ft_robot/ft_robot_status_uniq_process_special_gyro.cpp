// DRAFT (not compiled yet, not in configure.py): needs splits text 0xFAA8-0x10444, ctors 0x14-0x18, rodata 0x70-0xC0,
// data 0x7248-0x72C0, bss 0x2E8-0x308 in ft_robot/splits.txt plus an Object(NonMatching, ...) line.
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/robot/ft_robot_status_uniq_process_special_gyro.h>
#include <ft/robot/ft_robot_link_event.h>
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

static soGenerateArticleManageModule& getArticles(soModuleAccesser* acc) {
    return *static_cast<soGenerateArticleManageModule*>(acc->m_enumerationStart->m_generateArticleManageModule);
}

void ftRobotStatusUniqProcessSpecialGyro::initStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x11b: {
        ftRobotGyroLinkEvent event(0x839);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        break;
    }
    case 0x115: {
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0), 0x21000004);
        int gyros = itManager::getInstance()->getItemNum(static_cast<itKind>(0x57), 0, moduleAccesser->getStageObject().m_taskId, -1);
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
    case 0x11c: {
        ftRobotGyroLinkEvent event(0x83a);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        break;
    }
    case 0x11d: {
        ftRobotGyroLinkEvent event(0x83b);
        moduleAccesser->getLinkModule().sendEventNodes(-1, event, 0);
        if (!moduleAccesser->getWorkManageModule().isFlag(0x22000013)) {
            moduleAccesser->getWorkManageModule().setInt(0x1de, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e4, 0x20000002);
        } else {
            moduleAccesser->getWorkManageModule().setInt(0x1df, 0x20000001);
            moduleAccesser->getWorkManageModule().setInt(0x1e5, 0x20000002);
        }
        moduleAccesser->getEffectModule().removeCommon(0x1a);
        break;
    }
    }
}

// The gyro charge grows while the move is charged.
void ftRobotStatusUniqProcessSpecialGyro::execStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x11b) {
        if (moduleAccesser->getWorkManageModule().getFloat(0x11000014) < soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0)) {
            moduleAccesser->getWorkManageModule().addFloat(1.0f, 0x11000014);
        }
    }
}

// Throwing the gyro: creates the gyro item at the hand node, scaled with the fighter, and hands it its speed.
void ftRobotStatusUniqProcessSpecialGyro::execFixPos(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x11d && moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
        float lr = moduleAccesser->getPostureModule().getLr();
        Vec3f offset(lr * soValueAccesser::getConstantFloat(moduleAccesser, 0xfd2, 0), soValueAccesser::getConstantFloat(moduleAccesser, 0xfd3, 0), 0.0f);
        Vec3f handPos = moduleAccesser->getModelModule().getNodeGlobalPosition(0xa2, &offset, false, false);
        soGroundModule& ground = moduleAccesser->getGroundModule();
        Vec2f center = ground.getCenterPos(0);
        Vec3f safePos(center.m_x, center.m_y, ground.getZ());
        s32 taskId = moduleAccesser->getStageObject().m_taskId;
        BaseItem* gyro = itManager::getInstance()->createBaseItem(&safePos, handPos, lr, static_cast<itKind>(0x57), 0, taskId, taskId,
                                                                    &moduleAccesser->getResourceModule(), 1, 0, 0, 0xffff, 0x14);
        (void)gyro;
        moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000014);
        moduleAccesser->getWorkManageModule().offFlag(0x22000011);
    }
}

void ftRobotStatusUniqProcessSpecialGyro::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    bool ready = false;
    if (nextStatus < 0x1f) {
        ready = nextStatus == 0xe || nextStatus == 0;
    } else if (nextStatus < 0x11b) {
        ready = nextStatus < 0x21;
    } else if (nextStatus < 0x11e) {
        return;
    }
    if (ready) {
        if (soValueAccesser::getConstantFloat(moduleAccesser, 0xfcf, 0) <= moduleAccesser->getWorkManageModule().getFloat(0x11000014)) {
            moduleAccesser->getEffectModule().reqCommon(0.0f, 0x1a);
        }
    } else {
        moduleAccesser->getEffectModule().removeCommon(0x1a);
        moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000014);
    }
    // The articles tied to the gyro move are removed from the data record's article ids.
    u8* data = reinterpret_cast<u8*>(g_ftCommonDataAccesser.getData(Fighter_Robot));
    getArticles(moduleAccesser).removeExist(*reinterpret_cast<int*>(data + 0x90), 0);
    getArticles(moduleAccesser).removeExist(*reinterpret_cast<int*>(data + 0xa0), 0);
}

ftRobotStatusUniqProcessSpecialGyro g_ftRobotStatusUniqProcessSpecialGyro;
