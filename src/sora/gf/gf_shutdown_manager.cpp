#include <gf/gf_application.h>
#include <gf/gf_callback.h>
#include <gf/gf_error_manager.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_shutdown_manager.h>
#include <gm/gm_syssave_task.h>
#include <gf/gf_system_callback.h>
#include <revolution/OS/OSReset.h>
#include <revolution/OS/OSStateTM.h>
#include <sr/sr_common.h>
#include <types.h>

gfShutdownManager g_gfShutdownManager;

void gfShutdownManager::initilize() {
    OSSetResetCallback(&ResetCallback);
    OSSetPowerCallback(&PowerOffCallback);
}

void gfShutdownManager::ResetCallback() {
    g_gfShutdownManager.m_reset = true;
}

void gfShutdownManager::PowerOffCallback() {
    g_gfShutdownManager.m_powerOff = true;
}

void gfShutdownManager::enterRestartProcess() {
    m_reset = true;
}

void gfShutdownManager::enterReturnToWiiMenuProcess() {
    m_returnToWiiMenu = true;
}

void gfShutdownManager::update() {
    if (m_reset || m_powerOff || m_returnToWiiMenu) {
        if (unkC && unkD) {
            if (!unk0_b3 &&
                (gfErrorManager::getInstance()->unk0_b6 != true ||
                gfErrorManager::getInstance()->unk0_b7)) {
                unk8.add(gmSysSave::create(Heaps::GlobalMode));
                unk0_b3 = true;
            }
            switch (unk0) {
                case 0:
                    unk4.process();
                    unk0 = 1;
                    // FALL-THROUGH
                case 1:
                    if (unk8.process()) {
                        g_gfPadSystem->stopMotorAllForce();
                        if (m_powerOff == true) {
                            g_gfApplication->reset();
                            OSShutdownSystem();
                        } else if (m_returnToWiiMenu == true) {
                            g_gfApplication->reset();
                            OSReturnToMenu();
                        } else {
                            unkC = false;
                            g_gfApplication->restart();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
