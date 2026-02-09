#include <gf/gf_resource_loader.h>
#include <gf/gf_scene.h>
#include <gf/gf_task.h>
#include <mu/adv/mu_adv_seal.h>
#include <sc/sc_seal_disp.h>
#include <sr/sr_common.h>
#include <types.h>

scSealDisp* scSealDisp::create() {
    return new (Heaps::GlobalMode) scSealDisp("scSealDisp");
}

void scSealDisp::setModule() { }

static const muAdvSealTaskParam g_TaskParam = { 0x1000000, 0 };

void scSealDisp::start() {
    const char* path;
    u32 size;

    m_archive = new (Heaps::MenuResource) gfArchive;
    m_loader = new (Heaps::MenuResource) gfResourceLoader;
    muAdvSealTask::getResourcePackData(&path, &size);
    m_loader->loadResourceMemSizeOrder(Heaps::MenuResource, path, m_archive, size);
    m_state = 0;
}

s32 scSealDisp::process() {
    switch (m_state) {
        case 0:
            if (m_loader->isLoaded()) {
                muAdvSealTaskParam param = g_TaskParam;
                m_task = muAdvSealTask::create(&param, m_archive);
                m_state = 1;
            }
            break;
        case 1:
            if (m_task && m_task->unk40) {
                gfSceneManager* mgr = gfSceneManager::getInstance();
                mgr->unk1 = 0;
                mgr->processStep = 2;
                m_state = -1;
            }
            break;
        default:
            break;
    }
    return 0;
}

s32 scSealDisp::exit() {
    if (m_task) {
        m_task->exit();
        m_task = nullptr;
    }
    if (m_archive) {
        delete m_archive;
        m_archive = nullptr;
    }
    if (m_loader) {
        delete m_loader;
        m_loader = nullptr;
    }
    m_state = -1;
    return 0;
}
