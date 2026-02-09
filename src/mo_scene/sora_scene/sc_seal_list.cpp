#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <sc/sc_seal_list.h>
#include <sr/sr_common.h>
#include <types.h>

scSealList* scSealList::create() {
    return new (Heaps::GlobalMode) scSealList("scSealList");
}

void scSealList::start() {
    tySealListTask* task = new (Heaps::MenuInstance) tySealListTask;
    task->init();
    m_task = task;
}

s32 scSealList::process() {
    if (m_task->unk44 == 11) {
        gfSceneManager* mgr = gfSceneManager::getInstance();
        mgr->unk1 = 0;
        mgr->processStep = 2;
    }
    return 0;
}

s32 scSealList::exit() {
    if (m_task) {
        m_task->exit();
        m_task = nullptr;
    }
    return 0;
}

void scSealList::setModule() {
    setLoadModule("sora_menu_name.rel", false);
    setLoadModule("sora_menu_rule.rel", false);
    setLoadModule("sora_menu_sel_char_access.rel", false);
    setLoadModule("sora_menu_sel_stage.rel", false);
    setLoadModule("sora_menu_main.rel", false);
}
