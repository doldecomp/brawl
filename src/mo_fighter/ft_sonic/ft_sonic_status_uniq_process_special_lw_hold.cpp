// MATCH-ONLY: retain the original instruction order in this status process.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/sonic/ft_sonic_status_uniq_process_special_lw_hold.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/controller/so_controller_impl.h>

// Float 0x21000004 is rotation speed; integer 0x20000003 gates repeated button charges.
// Parameter IDs are retained because their original names are unavailable.
void ftSonicStatusUniqProcessSpecialLwHold::initStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getSituationModule().getKind() == 0) {
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfd6, 0), 0x21000004);
    } else {
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfd7, 0), 0x21000004);
    }
    limitRotSpeed(moduleAccesser);
}

void ftSonicStatusUniqProcessSpecialLwHold::execStatus(soModuleAccesser* moduleAccesser) {
    float rotSpeed = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
    rotSpeed -= soValueAccesser::getConstantFloat(moduleAccesser, 0xfd9, 0);
    if (moduleAccesser->getWorkManageModule().getInt(0x20000003) > 0) {
        moduleAccesser->getWorkManageModule().decInt(0x20000003);
    } else {
        soControllerModule& controller = moduleAccesser->getControllerModule();
        unsigned int chargeButtons = soController::getButtonMask(soController::Pad_Button_Special) |
                                     soController::getButtonMask(soController::Pad_Button_Attack);
        int trigger = controller.getTrigger();
        if (trigger & chargeButtons) {
            rotSpeed += soValueAccesser::getConstantFloat(moduleAccesser, 0xfdd, 0);
            moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dca, 0), 0x20000003);
        }
    }
    moduleAccesser->getWorkManageModule().setFloat(rotSpeed, 0x21000004);
    limitRotSpeed(moduleAccesser);
    syncMotionRate(moduleAccesser);
}

void ftSonicStatusUniqProcessSpecialLwHold::limitRotSpeed(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    float maxRotSpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xfd8, 0);
    if (work.getFloat(0x21000004) > maxRotSpeed) {
        moduleAccesser->getWorkManageModule().setFloat(soValueAccesser::getConstantFloat(moduleAccesser, 0xfd8, 0), 0x21000004);
    }
}

void ftSonicStatusUniqProcessSpecialLwHold::syncMotionRate(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    float maxRotSpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xfd8, 0);
    float chargeRatio = work.getFloat(0x21000004) / maxRotSpeed;
    if (chargeRatio < 0.0f) {
        chargeRatio = 0.0f;
    } else if (chargeRatio > 1.0f) {
        chargeRatio = 1.0f;
    }
    // MATCH-ONLY: reuse the limit temporary for the rate offset to retain FP register allocation.
    maxRotSpeed = chargeRatio * (soValueAccesser::getConstantFloat(moduleAccesser, 0xfda, 0) - soValueAccesser::getConstantFloat(moduleAccesser, 0xfdb, 0));
    float baseRate = soValueAccesser::getConstantFloat(moduleAccesser, 0xfdb, 0);
    float rate = baseRate + maxRotSpeed;
    moduleAccesser->getMotionModule().setRate(rate);
}

void ftSonicStatusUniqProcessSpecialLwHold::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    // HYPOTHESIS: 0x11e is the release status; its process consumes integer 0x20000002.
    if (nextStatus == 0x11e) {
        soWorkManageModule& work = moduleAccesser->getWorkManageModule();
        float maxRotSpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xfd8, 0);
        float chargeRatio = work.getFloat(0x21000004) / maxRotSpeed;
        if (chargeRatio < 0.0f) {
            chargeRatio = 0.0f;
        } else if (chargeRatio > 1.0f) {
            chargeRatio = 1.0f;
        }
        float duration = chargeRatio * soValueAccesser::getConstantFloat(moduleAccesser, 0xfdf, 0) *
                         soValueAccesser::getConstantInt(moduleAccesser, 0x5dc7, 0);
        if (duration < (float)soValueAccesser::getConstantInt(moduleAccesser, 0x5dc6, 0)) {
            duration = soValueAccesser::getConstantInt(moduleAccesser, 0x5dc6, 0);
        }
        moduleAccesser->getWorkManageModule().setInt((int)duration, 0x20000002);
    }
}

ftSonicStatusUniqProcessSpecialLwHold g_ftSonicStatusUniqProcessSpecialLwHold;
