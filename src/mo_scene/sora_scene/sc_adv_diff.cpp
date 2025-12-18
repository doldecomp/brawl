#include <gf/gf_application.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <gm/gm_global.h>
#include <sc/sc_adv_diff.h>
#include <sr/sr_common.h>
#include <types.h>

scAdvDiff* scAdvDiff::create() {
    return new (Heaps::GlobalMode) scAdvDiff("scAdvDiff");
}

void scAdvDiff::setModule() {
    setLoadModule("sora_adv_menu_difficulty.rel", false);
}

#pragma push
#pragma section ".rodata" ".rodata"
__declspec(section ".rodata") static muAdvDifficultyTaskParam g_TaskParam = { 2, 0, 1 };
#pragma pop

void scAdvDiff::start() {
    muAdvDifficultyTaskParam param = g_TaskParam;
    m_task = muAdvDifficultyTask::create(&param);
    g_gfApplication->unkD0.endKeepScreen();
}

static const char* g_DiffTable[] = {
    "Very easy",
    "Easy",
    "Normal",
    "Hard",
    "Very hard",
};

s32 scAdvDiff::process() {
    bool r5 = false;
    if (m_task) {
        switch (m_task->m_option) {
            case 0:
                break;
            case 1:
                OSReport("selected difficulty = %s\n", g_DiffTable[m_task->m_difficulty]);
                r5 = true;
                break;
            case 2:
                OSReport("difficulty select canceled\n");
                r5 = true;
                break;
            default:
                break;
        }
        if (r5) {
            gfSceneManager* mgr = gfSceneManager::getInstance();
            mgr->unk1 = 0;
            mgr->processStep = 2;
        }
    }
    return 0;
}

s32 scAdvDiff::exit() {
    if (m_task) {
        m_task->exit();
        m_task = nullptr;
    }
    g_gfApplication->unkD0.startKeepScreen();
    return 0;
}
