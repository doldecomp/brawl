#include <gf/gf_pad_status.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_scene.h>
#include <sc/sc_tutorial.h>
#include <sr/sr_common.h>
#include <types.h>

scTutorial* scTutorial::create() {
    return new (Heaps::GlobalMode) scTutorial("scTutorial");
}

void scTutorial::start() { }

s32 scTutorial::process() {
    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus(0xF0, &status);
    if (status.m_buttonsPressedThisFrame.bits & gfPadButtons::A) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scTutorial::exit() {
    return 0;
}
