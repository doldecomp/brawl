#include <ft/ft_util.h>
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

float ftUtil::getAttackReactionMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDB0, 0);
}

float ftUtil::getAttackPowerMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDAE, 0);
}

float ftUtil::getDamageMul(soModuleAccesser* acc) {
    return soValueAccesser::getConstantFloat(acc, 0xDAF, 0);
}
