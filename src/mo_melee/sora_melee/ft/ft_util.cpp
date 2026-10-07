#include <ft/ft_util.h>
#include <ft/ft_manager.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

bool ftUtil::isItemShootStatus(soModuleAccesser*, int status) {
    switch (status) {
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
    case 0xA8:
    case 0xA9:
    case 0xAA:
    case 0xAB:
    case 0xAC:
    case 0xAD:
    case 0xAE:
        return true;
    default:
        return false;
    }
}

bool ftUtil::isHammerStatus(soModuleAccesser*, int status) {
    switch (status) {
    case 0xDF:
    case 0xE0:
    case 0xE1:
    case 0xE2:
    case 0xE3:
    case 0xE4:
    case 0xE5:
        return true;
    default:
        return false;
    }
}

bool ftUtil::isHammerMotion(soModuleAccesser*, int motion) {
    switch (motion) {
    case 0x141:
    case 0x142:
    case 0x143:
        return true;
    default:
        return false;
    }
}

bool ftUtil::isSleepStatus(soModuleAccesser*, int status) {
    switch (status) {
    case 0x5C:
    case 0x5D:
    case 0x5E:
        return true;
    default:
        return false;
    }
}

bool ftUtil::isBindStatus(soModuleAccesser*, int status) {
    switch (status) {
    case 0x5F:
        return true;
    default:
        return false;
    }
}

bool ftUtil::isBuryStatus(soModuleAccesser*, int status) {
    switch (status) {
    case 0xC7:
    case 0xC8:
        return true;
    default:
        return false;
    }
}

// HYPOTHESIS: ftManager byte 0x68 is the adventure-mode (Subspace Emissary) flag.
float ftUtil::getWalkSpeedMul(soModuleAccesser* acc) {
    float mul = acc->getParamCustomizeModule().getWalkSpeedMul();
    if ((u8)g_ftManager->_104[0] == 1) {
        mul *= calcAdventureMulValue(acc, 0xD25, 0xD27, 0xD26);
    }
    return mul;
}

float ftUtil::getRunSpeedMul(soModuleAccesser* acc) {
    float mul = 1.0f;
    if ((u8)g_ftManager->_104[0] == 1) {
        mul *= calcAdventureMulValue(acc, 0xD25, 0xD27, 0xD26);
    }
    return mul;
}

float ftUtil::getJumpSpeedMul(soModuleAccesser* acc) {
    float mul = 1.0f;
    if ((u8)g_ftManager->_104[0] == 1) {
        mul *= calcAdventureMulValue(acc, 0xD28, 0xD2A, 0xD29);
    }
    return mul;
}

float ftUtil::getWeightReactionMul(soModuleAccesser* acc) {
    float weight = soValueAccesser::getConstantFloat(acc, 0xBE1, 0) * 0.01f;
    return 2.0f - (weight * 2.0f) / (weight + 1.0f);
}

float ftUtil::getAttackReactionMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDB0, 0);
}

float ftUtil::getAttackPowerMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDAE, 0);
}

float ftUtil::getDamageMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDAF, 0);
}

// Statuses a Zako (Subspace Emissary enemy fighter) cannot enter: it has no tech, for example (HYPOTHESIS: the
// individual statuses are the ones the common status table marks as unused by Zako).
bool ftUtil::isValidStatusKindZako(soModuleAccesser*, int status) {
    switch (status) {
    case 0x1A:
    case 0x1B:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x4F:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x67:
    case 0x73:
    case 0x74:
    case 0x96:
    case 0x97:
    case 0x10C:
    case 0x10F:
    case 0x110:
    case 0x112:
    case 0x113:
    case 0x114:
    case 0x115:
        return false;
    default:
        return true;
    }
}

// HYPOTHESIS: work flag 0x12000039 lifts the limit on operated speed.
bool ftUtil::isEnableSpeedOperation(soModuleAccesser* acc) {
    if (acc->getWorkManageModule().isFlag(0x12000039) == false) {
        float limit = soValueAccesser::getConstantFloat(acc, 0xCE2, 0);
        float speedSq = acc->getKineticModule().getEnergy(4)->getSpeed().lengthSq();
        float limitSq = limit * limit;
        if (speedSq > limitSq)
            return false;
    }
    return true;
}
