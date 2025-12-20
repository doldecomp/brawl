#include <gf/gf_application.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <gm/gm_global.h>
#include <mu/adv/mu_adv_result.h>
#include <sc/sc_adv_result.h>
#include <sr/sr_common.h>
#include <types.h>

scAdvResult* scAdvResult::create() {
    return new (Heaps::GlobalMode) scAdvResult("scAdvResult");
}

void scAdvResult::setModule() {
    setLoadModule("sora_adv_menu_result.rel", false);
}

struct UnkParam {
    union {
        bool asBool;
        u32 asInt;
    } unk0;
    u32 unk4;
};

void scAdvResult::start() {
    UnkParam stack18;
    UnkParam stack10;
    UnkParam stack8;
    if (g_GameGlobal->m_advData) {
        stack10.unk0.asInt = g_GameGlobal->m_advData->m_record.unk4928;
        stack10.unk4 = g_GameGlobal->m_advData->m_record.unk492C;
    } else {
        stack18.unk0.asBool = false;
        stack18.unk4 = -1;
        stack10 = stack18;
    }
    stack8 = stack10;
    m_mainPlayerPort = stack8.unk4;
    muAdvResultTaskParam param = { m_mainPlayerPort, m_earnedCoinsForClear,
            m_scoreInCurrentStage, m_totalScore, &unk20, &unk34, &unk48 };
    m_task = muAdvResultTask::create(&param);
    if (gfSceneManager::getInstance()->m_memoryLayout) {
        m_task->unk5A4 = true;
    }
    g_gfApplication->unkD0.endKeepScreen();
}

s32 scAdvResult::process() {
    if (m_task && m_task->unk40) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scAdvResult::exit() {
    unk20.remove();
    unk34.remove();
    unk48.remove();
    if (m_task) {
        m_task->exit();
        m_task = nullptr;
    }
    g_gfApplication->unkD0.startKeepScreen();
    return 0;
}
