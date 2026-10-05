#include <ft/ft_status_uniq_process_damage.h>
#include <ft/ft_audience_manager.h>
#include <ft/ft_manager.h>
#include <mt/mt_prng.h>
#include <so/damage/so_damage.h>
#include <so/damage/so_damage_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// HYPOTHESIS: the log flag byte at +0x45 is read through its bitfields below.

// Applies the stick-driven drift that is allowed while in hitlag/hitstun (ASDI/SDI).
// HYPOTHESIS: this block is an inline helper in the original (identical code appears in
// execStop, leaveStop and twice in execStatus with different parameter ids).
static inline void applyDriftInput(soModuleAccesser* moduleAccesser, soDamageLog* damageLog, u32 paramId, float stickX, float stickY) {
    float driftMul = soValueAccesser::getConstantFloat(moduleAccesser, paramId, 0);
    Vec3f pos = moduleAccesser->getPostureModule().getPos();
    float mul = driftMul * damageLog->m_hitStopDelay;
    Vec2f drift;
    drift.m_x = mul * stickX;
    drift.m_y = mul * stickY;
    if (damageLog->m_isSituationGround == true) {
        if (damageLog->m_groundTouchNormal.m_x * drift.m_x + damageLog->m_groundTouchNormal.m_y * drift.m_y < 0.0f) {
            drift.m_y = 0.0f;
        }
        float angle = atan2(-damageLog->m_groundTouchNormal.m_x, damageLog->m_groundTouchNormal.m_y);
        drift.rot(&drift, angle);
    }
    pos.m_y += drift.m_y;
    pos.m_x += drift.m_x;
    pos.m_z = pos.m_z;
    moduleAccesser->getPostureModule().setPos(&pos);
}

ftStatusUniqProcessDamage::ftStatusUniqProcessDamage() { }

ftStatusUniqProcessDamage g_ftStatusUniqProcessDamage;

void ftStatusUniqProcessDamage::initNormalDamageCommon(soModuleAccesser* moduleAccesser) {
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    int statusKind = moduleAccesser->getStatusModule().getStatusKind();
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012) == 1) {
        float v = soValueAccesser::getConstantFloat(moduleAccesser, 0xbce, 0);
        moduleAccesser->getWorkManageModule().setInt((int)v, 0x10000039);
    }
    if (statusKind != 0x47 && statusKind != 0x48) {
        if (damageLog->m_frame > 0.0f) {
            moduleAccesser->getWorkManageModule().offFlag(0x22000011);
            moduleAccesser->getWorkManageModule().setInt((int)damageLog->m_frame, 0x10000038);
        } else {
            moduleAccesser->getWorkManageModule().onFlag(0x22000011);
            moduleAccesser->getWorkManageModule().setInt(0, 0x10000038);
        }
    }
    int v5a0a = soValueAccesser::getConstantInt(moduleAccesser, 0x5a0a, 0);
    moduleAccesser->getWorkManageModule().setInt(v5a0a, 0x10000002);
    float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xc8f, 0);
    float cSq = c * c;
    if (damageLog->m_speed.m_x * damageLog->m_speed.m_x + damageLog->m_speed.m_y * damageLog->m_speed.m_y > cSq) {
        moduleAccesser->getWorkManageModule().onFlag(0x1200001b);
        int v5a15 = soValueAccesser::getConstantInt(moduleAccesser, 0x5a15, 0);
        moduleAccesser->getWorkManageModule().setInt(v5a15, 0x10000020);
    }
    int v5a30 = soValueAccesser::getConstantInt(moduleAccesser, 0x5a30, 0);
    moduleAccesser->getWorkManageModule().setInt(v5a30, 0x20000006);
    int v5a31 = soValueAccesser::getConstantInt(moduleAccesser, 0x5a31, 0);
    moduleAccesser->getWorkManageModule().setInt(v5a31, 0x20000007);
}

void ftStatusUniqProcessDamage::initNormalDamage(soModuleAccesser* moduleAccesser) {
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    // motion kinds indexed [damage level][height variation]
    int motionKinds[4][3] = {
        { 0x9E, 0x9B, 0x98 },
        { 0x9F, 0x9C, 0x99 },
        { 0xA0, 0x9D, 0x9A },
        { 0, 0, 0 },
    };
    int level = damageLog->m_level;
    int height = damageLog->m_height;
    if (level >= 3) {
        level = 2;
    }
    int* row = motionKinds[level];
    if (row[height] == moduleAccesser->getMotionModule().getKind()) {
        height = randi(2) + height + 1;
        if (height >= 3) {
            height -= 3;
        }
    }
    soMotionChangeParam param;
    param.m_kind = row[height];
    param.m_frame = 0.0f;
    param.m_rate = 1.0f;
    param._12 = 0;
    param._13 = 0;
    param._14 = 0;
    param._15 = 0;
    moduleAccesser->getMotionModule().changeMotionRequest(&param);
    initNormalDamageCommon(moduleAccesser);
}

void ftStatusUniqProcessDamage::initStatus(soModuleAccesser* moduleAccesser) {
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    int statusKind = moduleAccesser->getStatusModule().getStatusKind();
    moduleAccesser->getControllerModule().resetFlickX();
    moduleAccesser->getControllerModule().resetFlickY();
    moduleAccesser->getWorkManageModule().setInt(0, 0x20000004);
    moduleAccesser->getWorkManageModule().setInt(0, 0x20000001);
    moduleAccesser->getWorkManageModule().setInt(0, 0x20000002);
    moduleAccesser->getWorkManageModule().offFlag(0x22000011);
    if (damageLog->m_isMeteor == 1) {
        moduleAccesser->getWorkManageModule().onFlag(0x22000012);
    }
    switch (statusKind) {
    case 0x5a: {
        float rumble;
        float base = (float)soValueAccesser::getConstantInt(moduleAccesser, 0x5a86, 0);
        rumble = soValueAccesser::getConstantFloat(moduleAccesser, 0xc80, 0) + base;
        rumble -= moduleAccesser->getDamageModule().getDamage(0);
        float c81 = soValueAccesser::getConstantFloat(moduleAccesser, 0xc81, 0);
        if (c81 < c81) {
        }
        soControllerModule* controller = &moduleAccesser->getControllerModule();
        float c83 = soValueAccesser::getConstantFloat(moduleAccesser, 0xc83, 0);
        float c82 = soValueAccesser::getConstantFloat(moduleAccesser, 0xc82, 0);
        controller->startClatter(rumble, c82, c83, 0, -1, 0, false);
        moduleAccesser->getControllerModule().setRumble(0x1a, 0, true, -1);
        moduleAccesser->getEffectModule().reqCommon(0.0f, 0x1d);
        break;
    }
    case 0x5d: {
        soDamageModule* damageModule = &moduleAccesser->getDamageModule();
        float level = (float)(3 - soValueAccesser::getConstantInt(moduleAccesser, 0x5a88, 0));
        float rumble = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf1, 0) * level;
        float tmp = soValueAccesser::getConstantFloat(moduleAccesser, 0xdb2, 0);
        tmp = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf2, 0) * tmp;
        float sum = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf0, 0) + tmp + rumble;
        rumble = damageLog->m_reaction * soValueAccesser::getConstantFloat(moduleAccesser, 0xcf3, 0) + sum;
        float damage = damageModule->getDamage(0);
        rumble = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf4, 0) * damage + rumble;
        if (damageLog->m_attribute == 10) {
            rumble *= soValueAccesser::getConstantFloat(moduleAccesser, 0xcf7, 0);
        }
        soControllerModule* controller = &moduleAccesser->getControllerModule();
        float c6 = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf6, 0);
        float c5 = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf5, 0);
        controller->startClatter(rumble, c5, c6, 0, 1, 0, false);
        moduleAccesser->getEffectModule().reqCommon(0.0f, 0x1e);
        break;
    }
    case 0x5f: {
        soDamageModule* damageModule = &moduleAccesser->getDamageModule();
        float level = (float)(3 - soValueAccesser::getConstantInt(moduleAccesser, 0x5a88, 0));
        float rumble = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf9, 0) * level;
        float tmp = soValueAccesser::getConstantFloat(moduleAccesser, 0xdb2, 0);
        tmp = soValueAccesser::getConstantFloat(moduleAccesser, 0xcfa, 0) * tmp;
        float sum = soValueAccesser::getConstantFloat(moduleAccesser, 0xcf8, 0) + tmp + rumble;
        sum = damageLog->m_reaction * soValueAccesser::getConstantFloat(moduleAccesser, 0xcfb, 0) + sum;
        float damage = damageModule->getDamage(0);
        sum = soValueAccesser::getConstantFloat(moduleAccesser, 0xcfc, 0) * damage + sum;
        soControllerModule* controller = &moduleAccesser->getControllerModule();
        float cfe = soValueAccesser::getConstantFloat(moduleAccesser, 0xcfe, 0);
        float cfd = soValueAccesser::getConstantFloat(moduleAccesser, 0xcfd, 0);
        controller->startClatter(sum, cfd, cfe, 0, 3, 0, false);
        moduleAccesser->getControllerModule().setRumble(0xd, 0, false, -1);
        break;
    }
    default:
        if (*((u8*)g_ftManager + 0x6f) >> 7 == 1) { // MATCH-ONLY: raw access to an unnamed ftManager flag
            if (*((u8*)damageLog + 0x44) != 0xb) {
                if (moduleAccesser->getStatusModule().getPrevStatusKind(0) != 0xc1) {
                    float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xd2b, 0);
                    if (damageLog->m_reaction >= c) {
                        int frames = (int)(damageLog->m_reaction * soValueAccesser::getConstantFloat(moduleAccesser, 0xd2c, 0));
                        if (frames > soValueAccesser::getConstantInt(moduleAccesser, 0x5a51, 0)) {
                            frames = soValueAccesser::getConstantInt(moduleAccesser, 0x5a51, 0);
                        }
                        moduleAccesser->getCollisionHitModule().setXluFrameGlobal(frames, 0);
                    }
                }
            }
        }
        if (damageLog->m_attribute == 3 || damageLog->m_attribute == 0x14) {
            moduleAccesser->getWorkManageModule().onFlag(0x22000013);
            moduleAccesser->getWorkManageModule().setInt(damageLog->m_hitStopFrame, 0x20000002);
            soMotionChangeParam param;
            param.m_kind = 0xa9;
            param.m_frame = 0.0f;
            param.m_rate = 1.0f;
            param._12 = 0;
            param._13 = 0;
            param._14 = 0;
            param._15 = 0;
            moduleAccesser->getMotionModule().changeMotionRequest(&param);
            moduleAccesser->getWorkManageModule().setFlag(moduleAccesser->getKineticModule().getEnergy(1)->isEnable(), 0x22000014);
            moduleAccesser->getKineticModule().getEnergy(1)->disable();
            moduleAccesser->getKineticModule().getEnergy(4)->disable();
            moduleAccesser->getSituationModule().setKeepAir(true);
        } else {
            initNormalDamage(moduleAccesser);
        }
        break;
    }
}

void ftStatusUniqProcessDamage::execNormalDamageCommon(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000011) == 0) {
        if (moduleAccesser->getWorkManageModule().getInt(0x10000038) <= 0) {
            moduleAccesser->getWorkManageModule().onFlag(0x22000011);
        }
    }
    moduleAccesser->getWorkManageModule().incInt(0x20000004);
    moduleAccesser->getWorkManageModule().countDownInt(0x20000006, 0);
    moduleAccesser->getWorkManageModule().countDownInt(0x20000007, 0);
}

void ftStatusUniqProcessDamage::execNormalDamage(soModuleAccesser* moduleAccesser) {
    execNormalDamageCommon(moduleAccesser);
}

void ftStatusUniqProcessDamage::execStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000013) == 1) {
        soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000002);
        if (count > 0) {
            count--;
            moduleAccesser->getWorkManageModule().setInt(count, 0x20000002);
        }
        if (count <= 0) {
            moduleAccesser->getWorkManageModule().offFlag(0x22000013);
            moduleAccesser->getKineticModule().getEnergy(4)->enable();
            if (moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
                moduleAccesser->getKineticModule().getEnergy(1)->enable();
            }
            if (damageLog->m_isCollisionAbsolute == 0) {
                {
                float stickX = moduleAccesser->getControllerModule().getStickX();
                float stickY = moduleAccesser->getControllerModule().getStickY();
                float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc65, 0);
                float ySq = stickY * stickY;
                    float xSq = stickX * stickX;
                    if (xSq + ySq >= threshold * threshold) {
                    applyDriftInput(moduleAccesser, damageLog, 0xc67, stickX, stickY);
                }
            }
            }
            moduleAccesser->getSituationModule().setKeepAir(false);
            initNormalDamage(moduleAccesser);
            if (moduleAccesser->getWorkManageModule().isFlag(0x22000015) == 1) {
                moduleAccesser->getWorkManageModule().offFlag(0x22000015);
                moduleAccesser->getEffectModule().remove(moduleAccesser->getWorkManageModule().getInt(0x20000003));
            }
            moduleAccesser->getWorkManageModule().offFlag(0x12000037);
        } else if (damageLog->m_isCollisionAbsolute == 0) {
            if (moduleAccesser->getWorkManageModule().isFlag(0x12000037) == 0) {
                u8 flickX = moduleAccesser->getControllerModule().getFlickX();
                u8 flickY = moduleAccesser->getControllerModule().getFlickY();
                int threshold = soValueAccesser::getConstantInt(moduleAccesser, 0x5a01, 0);
                if (flickX < threshold || flickY < threshold) {
                    float stickX = moduleAccesser->getControllerModule().getStickX();
                    float stickY = moduleAccesser->getControllerModule().getStickY();
                    float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc65, 0);
                    float ySq = stickY * stickY;
                    float xSq = stickX * stickX;
                    if (xSq + ySq >= threshold * threshold) {
                        applyDriftInput(moduleAccesser, damageLog, 0xc66, stickX, stickY);
                        moduleAccesser->getControllerModule().resetFlickX();
                        moduleAccesser->getControllerModule().resetFlickY();
                    }
                }
            }
        }
    } else {
        execNormalDamage(moduleAccesser);
    }
}

void ftStatusUniqProcessDamage::execStop(soModuleAccesser* moduleAccesser) {
    soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
    if (moduleAccesser->getStopModule().isDamage() == 1) {
        if (damageLog->m_isCollisionAbsolute == 0) {
            if (moduleAccesser->getWorkManageModule().isFlag(0x12000037) == 0) {
                u8 flickX = moduleAccesser->getControllerModule().getFlickX();
                u8 flickY = moduleAccesser->getControllerModule().getFlickY();
                int threshold = soValueAccesser::getConstantInt(moduleAccesser, 0x5a01, 0);
                if (flickX < threshold || flickY < threshold) {
                    float stickX = moduleAccesser->getControllerModule().getStickX();
                    float stickY = moduleAccesser->getControllerModule().getStickY();
                    float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc65, 0);
                    float ySq = stickY * stickY;
                    float xSq = stickX * stickX;
                    if (xSq + ySq >= threshold * threshold) {
                        applyDriftInput(moduleAccesser, damageLog, 0xc66, stickX, stickY);
                        moduleAccesser->getControllerModule().resetFlickX();
                        moduleAccesser->getControllerModule().resetFlickY();
                    }
                }
            }
        }
    }
}

void ftStatusUniqProcessDamage::exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind) {
    moduleAccesser->getWorkManageModule().offFlag(0x12000037);
    if (moduleAccesser->getSituationModule().getKind() != 2) {
        moduleAccesser->getWorkManageModule().offFlag(0x12000011);
    }
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012) == 1) {
        if (moduleAccesser->getWorkManageModule().getInt(0x10000039) <= 0) {
            switch (nextStatusKind) {
            case 0xc:
            case 0xd:
            case 0x114:
                moduleAccesser->getKineticModule().getEnergy(4)->clearSpeed();
                moduleAccesser->getWorkManageModule().setInt(0, 0x10000038);
                break;
            }
        }
    }
}

void ftStatusUniqProcessDamage::leaveStop(soModuleAccesser* moduleAccesser, int unk, bool isHitStopEnd) {
    if (isHitStopEnd == true) {
        soDamageLog* damageLog = moduleAccesser->getDamageModule().getDamageLog();
        if (damageLog->m_isCollisionAbsolute == 0) {
            {
                float stickX = moduleAccesser->getControllerModule().getStickX();
                float stickY = moduleAccesser->getControllerModule().getStickY();
                float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc65, 0);
                float ySq = stickY * stickY;
                    float xSq = stickX * stickX;
                    if (xSq + ySq >= threshold * threshold) {
                    applyDriftInput(moduleAccesser, damageLog, 0xc67, stickX, stickY);
                }
            }
        }
        int entryId = moduleAccesser->getWorkManageModule().getInt(0x1000003f);
        if (entryId != -1) {
            ftAudience* audience = g_ftAudienceManager->m_audience;
            audience->checkCheer(0.0f, entryId, moduleAccesser->getWorkManageModule().getInt(0x10000000));
            moduleAccesser->getWorkManageModule().setInt(-1, 0x1000003f);
        }
    }
}

bool ftStatusUniqProcessDamage::checkTransitionPrecede(soModuleAccesser* moduleAccesser, void* transitionInfo, int target) {
    int kind = *(int*)transitionInfo;
    if (kind == 0xc || (u32)(kind - 0xe) <= 1) {
        return false;
    }
    return true;
}
