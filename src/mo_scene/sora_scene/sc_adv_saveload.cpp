#include <ad/ad_autosave.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <gm/gm_global.h>
#include <mu/adv/mu_adv_saveload.h>
#include <sc/sc_adv_saveload.h>
#include <sr/sr_common.h>
#include <types.h>

scAdvSave* scAdvSave::create() {
    return new (Heaps::GlobalMode) scAdvSave("scAdvSave");
}

void scAdvSave::setModule() { }

struct UnkParam {
    union {
        bool asBool;
        u32 asInt;
    } unk0;
    u32 unk4;
};

void scAdvSave::start() {
    UnkParam stack20;
    UnkParam stack18;
    UnkParam stack10;
    if (g_GameGlobal->m_advData) {
        stack18.unk0.asInt = g_GameGlobal->m_advData->m_record.unk4928;
        stack18.unk4 = g_GameGlobal->m_advData->m_record.unk492C;
    } else {
        stack20.unk0.asBool = false;
        stack20.unk4 = -1;
        stack18 = stack20;
    }
    stack10 = stack18;
    muAdvSaveTaskParam param;
    param.unk0 = stack10.unk4;
    s32 layout = gfSceneManager::getInstance()->m_memoryLayout;
    if (layout == 0) {
        muAdvSaveTask* task = muAdvSaveTask::create(&param, Heaps::MenuInstance, 43);
        if (m_task) {
            m_task->exit();
        }
        m_task = task;
    } else if (layout == 1) {
        m_autosave = adAutoSave::create(false);
    } else {
        m_autosave = adAutoSave::create(true);
    }
}

s32 scAdvSave::process() {
    if (gfSceneManager::getInstance()->m_memoryLayout == 0) {
        if (m_task->unk1B8 == 1) {
            gfSceneManager* mgr = gfSceneManager::getInstance();
            mgr->unk1 = 0;
            mgr->processStep = 2;
        }
    } else if (!adAutoSave::isAlive()) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scAdvSave::exit() {
    if (m_task) {
        m_task->exit();
    }
    m_task = nullptr;
    return 0;
}

scAdvLoad* scAdvLoad::create() {
    return new (Heaps::GlobalMode) scAdvLoad("scAdvLoad");
}

void scAdvLoad::setModule() { }

void scAdvLoad::start() {
    UnkParam stack20;
    UnkParam stack18;
    UnkParam stack10;
    if (g_GameGlobal->m_advData) {
        stack18.unk0.asInt = g_GameGlobal->m_advData->m_record.unk4928;
        stack18.unk4 = g_GameGlobal->m_advData->m_record.unk492C;
    } else {
        stack20.unk0.asBool = false;
        stack20.unk4 = -1;
        stack18 = stack20;
    }
    stack10 = stack18;
    muAdvLoadTaskParam param;
    param.unk0 = stack10.unk4;
    muAdvLoadTask* task = muAdvLoadTask::create(&param);
    if (m_task) {
        m_task->exit();
    }
    m_task = task;
}

s32 scAdvLoad::process() {
    if (m_task->unk1B8 == 1) {
        bool isLoaded = m_task->isLoaded();
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = isLoaded;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scAdvLoad::exit() {
    if (m_task) {
        m_task->exit();
    }
    m_task = nullptr;
    return 0;
}
