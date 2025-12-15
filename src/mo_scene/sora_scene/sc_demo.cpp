#include <gf/gf_application.h>
#include <gf/gf_keep_fb.h>
#include <gf/gf_pad_status.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_scene.h>
#include <sc/sc_demo.h>
#include <sr/sr_common.h>
#include <types.h>

scDemo* scDemo::create() {
    return new (Heaps::GlobalMode) scDemo("scDemo");
}

void scDemo::start() {
    g_gfApplication->unkD0.endKeepScreen();
}

s32 scDemo::process() {
    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus(0xF0, &status);
    if (status.m_buttonsPressedThisFrame.bits & gfPadButtons::A) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scDemo::exit() {
    g_gfApplication->unkD0.startKeepScreen();
    return 0;
}
