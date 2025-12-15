#include <gf/gf_application.h>
#include <gf/gf_keep_fb.h>
#include <gf/gf_pad_status.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <sc/sc_net_time_result.h>
#include <sr/sr_common.h>
#include <types.h>

scNetTimeResult* scNetTimeResult::create() {
    return new (Heaps::GlobalMode) scNetTimeResult("scNetTimeResult");
}

void scNetTimeResult::setModule() {
    setLoadModule("sora_menu_time_result.rel", false);
}

void scNetTimeResult::start() {
    muWifiTimeResultTaskParam param = m_taskParam;
    m_task = muWifiTimeResultTask::create(&param);
    g_gfApplication->unkD0.endKeepScreen();
}

s32 scNetTimeResult::process() {
    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus(0xF0, &status);
    if (status.m_buttonsPressedThisFrame.bits & gfPadButtons::A) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scNetTimeResult::exit() {
    if (m_task) {
        m_task->exit();
        m_task = nullptr;
    }
    g_gfApplication->unkD0.startKeepScreen();
    return 0;
}
