#include <gf/gf_application.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <gm/gm_global.h>
#include <mu/adv/mu_adv_game_over.h>
#include <revolution/OS/OSError.h>
#include <sc/sc_adv_gameover.h>
#include <sr/sr_common.h>
#include <types.h>

// NONMATCHING: instruction ordering in the ctor
scAdvGameover* scAdvGameover::create() {
    return new (Heaps::GlobalMode) scAdvGameover("scAdvGameover");
}

void scAdvGameover::setModule() {
    setLoadModule("sora_adv_menu_game_over.rel", false);
}

struct UnkParam {
    union {
        bool asBool;
        u32 asInt;
    } unk0;
    u32 unk4;
};

void scAdvGameover::start() {
    UnkParam stack18;
    UnkParam stack10;
    UnkParam stack8;
    muAdvGameOverTaskParam param = { };
    param.unk0 = unkC;
    if (g_GameGlobal->m_advData) {
        stack10.unk0.asInt = g_GameGlobal->m_advData->m_record.unk4928;
        stack10.unk4 = g_GameGlobal->m_advData->m_record.unk492C;
    } else {
        stack18.unk0.asBool = false;
        stack18.unk4 = -1;
        stack10 = stack18;
    }
    stack8 = stack10;
    param.unk4 = stack8.unk4;
    param.unk8 = &unk60;
    param.unkC = &unk4C;
    param.unk10 = &unk74;
    param.unk14 = &unk10;
    param.unk18 = &unk24;
    param.unk1C = &unk38;
    m_task = muAdvGameOverTask::create(&param);
    g_gfApplication->unkD0.endKeepScreen();
}

s32 scAdvGameover::process() {
    if (m_task && m_task->unk1AC) {
        s32 r30 = 0;
        switch (m_task->getSelection()) {
            case 0:
                OSReport("Gameover retry selected.\n");
                r30 = 0;
                break;
            case 4:
                OSReport("Gameover quit with save selected.\n");
                r30 = 2;
                break;
            case 5:
                OSReport("Gameover quit with no save selected.\n");
                r30 = 3;
                break;
            case 2:
                OSReport("Gameover go to map selected.\n");
                r30 = 1;
                break;
            default:
                break;
        }
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = r30;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scAdvGameover::exit() {
    unk10.remove();
    unk24.remove();
    unk38.remove();
    unk60.remove();
    unk4C.remove();
    unk74.remove();
    m_task->exit();
    m_task = nullptr;
    return 0;
}
