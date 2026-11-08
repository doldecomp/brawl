#include <cstring>
#include <gf/gf_3d_scene.h>
#include <gf/gf_camera.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_memory_pool.h>
#include <gf/gf_module.h>
#include <gf/gf_scene.h>
#include <gm/gm_global.h>
#include <revolution/OS.h>
#include <sr/sr_common.h>
#include <types.h>

gfSceneManager* g_gfSceneManager;

static inline bool isReleasePending(gfSceneManager* manager, const char* moduleName) {
    for (int i = 0; i < 11; i++) {
        if (manager->m_loadModules[i].m_moduleName && manager->m_loadModules[i].m_status == 3 &&
            !strcmp(manager->m_loadModules[i].m_moduleName, moduleName))
            return true;
    }
    return false;
}

bool gfScene::setLoadModule(const char* moduleName, bool p2) {
    if (!g_gfModuleManager->isLoaded(moduleName) ||
        isReleasePending(g_gfSceneManager, moduleName) == true) {
        g_gfSceneManager->setLoadModuleName(moduleName, m_sceneName, p2, true);
        return true;
    }
    return false;
}

gfSceneManager::gfSceneManager() :
    m_prevScene(nullptr),
    m_currentScene(nullptr),
    m_nextScene(nullptr),
    m_prevSequence(nullptr),
    m_currentSequence(nullptr),
    m_nextSequence(nullptr),
    m_sceneCount(0),
    m_sequenceCount(0),
    unk278_b7(true),
    unk278_b6(false),
    m_exitScene(nullptr),
    m_memoryLayout(0),
    unk1(0),
    processStep(0),
    m_sequenceStep(0),
    m_loadState(0),
    unk31c(0)
{
    for (int i = 0; i < 100; i++)
        m_scenes[i] = nullptr;
    for (int i = 0; i < 50; i++)
        m_sequences[i] = nullptr;
}

gfSceneManager* gfSceneManager::create() {
    if (!g_gfSceneManager)
        g_gfSceneManager = new (Heaps::SystemFW) gfSceneManager;
    return g_gfSceneManager;
}

gfSceneManager* gfSceneManager::getInstance() {
    return g_gfSceneManager;
}

void gfSceneManager::changeNextScene() {
    m_prevScene = m_currentScene;
    m_currentScene = nullptr;
    while (true) {
        m_currentSequence->setNext();
        if (m_sequenceStep != 3)
            break;
        const char* nextName = m_nextSequence->m_sequenceName;
        OSReport("%s -> %s\n", m_currentSequence ? m_currentSequence->m_sequenceName : "start",
                 nextName);
        m_currentSequence->exit();
        m_prevSequence = m_currentSequence;
        m_currentSequence = m_nextSequence;
        m_nextSequence = nullptr;
        m_sequenceStep = 0;
        m_currentSequence->start();
        m_sequenceStep = 1;
    }
    const char* nextName = m_nextScene->m_sceneName;
    OSReport("%s -> %s\n", m_prevScene ? m_prevScene->m_sceneName : "start", nextName);
    processStep = 0;
    m_currentScene = m_nextScene;
    m_nextScene = nullptr;
    m_currentScene->setModule();
}

int gfSceneManager::registScene(gfScene* scene) {
    int index = m_sceneCount++;
    m_scenes[index] = scene;
    return index;
}

int gfSceneManager::registSequence(gfSequence* sequence) {
    int index = m_sequenceCount++;
    m_sequences[index] = sequence;
    return index;
}

static inline void resetCameras() {
    gfCameraManager* cameraManager = gfCameraManager::getManager();
    if (cameraManager) {
        cameraManager->m_cameras[0].reset();
        cameraManager->m_cameras[1].reset();
    }
}

static inline void setReleaseModules(gfSceneManager* manager, const char* sceneName) {
    for (int i = 0; i < 11; i++) {
        if (manager->m_loadModules[i].m_moduleName && manager->m_loadModules[i].m_status == 2 &&
            sceneName && !strcmp(manager->m_loadModules[i].m_sceneName, sceneName))
            manager->m_loadModules[i].m_status = 3;
    }
}

int gfSceneManager::process() {
    if (unk278_b7 == true && !m_currentScene)
        return 0;
    if (processStep == 0) {
        if (g_GameGlobal->m_appData->unk28_b5)
            return 0;
        if (loadModule() == true)
            return 0;
        if (g_gfSceneRoot)
            g_gfSceneRoot->resetLight();
        resetCameras();
        m_currentScene->start();
        gfHeapManager::dumpList();
        processStep = 1;
    }
    m_currentScene->process();
    if (processStep == 2) {
        m_currentScene->exit();
        unk278_b6 = true;
        m_exitScene = m_currentScene;
        setReleaseModules(this, m_currentScene->m_sceneName);
        changeNextScene();
    }
    return 0;
}

static inline void releaseModules(gfSceneManager* manager, const char* sceneName) {
    for (int i = 0; i < 11; i++) {
        if (manager->m_loadModules[i].m_moduleName && manager->m_loadModules[i].m_status == 3 &&
            (!sceneName || !strcmp(manager->m_loadModules[i].m_sceneName, sceneName))) {
            g_gfModuleManager->release(manager->m_loadModules[i].m_moduleName);
            manager->m_loadModules[i].m_moduleName = nullptr;
            manager->m_loadModules[i].m_sceneName = nullptr;
            manager->m_loadModules[i].m_status = 0;
        }
    }
}

int gfSceneManager::postProcess() {
    if (unk278_b6 == true) {
        releaseModules(this, m_exitScene->m_sceneName);
        m_exitScene = nullptr;
        unk278_b6 = false;
    }
    return 0;
}

gfScene* gfSceneManager::searchScene(const char* sceneName) const {
    for (int i = 0; i < m_sceneCount; i++) {
        if (!strcmp(m_scenes[i]->m_sceneName, sceneName))
            return m_scenes[i];
    }
    return nullptr;
}

gfSequence* gfSceneManager::searchSequence(const char* sequenceName) const {
    for (int i = 0; i < m_sequenceCount; i++) {
        if (!strcmp(m_sequences[i]->m_sequenceName, sequenceName))
            return m_sequences[i];
    }
    return nullptr;
}

void gfSceneManager::startSequence(const char* sequenceName, int p2) {
    unk278_b7 = false;
    m_currentSequence = searchSequence(sequenceName);
    unk31c = p2;
    m_currentSequence->start();
    m_sequenceStep = 1;
    changeNextScene();
}

void gfSceneManager::setNextScene(const char* sceneName, int memoryLayout) {
    m_nextScene = searchScene(sceneName);
    m_memoryLayout = memoryLayout;
    processStep = 3;
}

void gfSceneManager::setNextSequence(const char* sequenceName, int p2) {
    m_nextSequence = searchSequence(sequenceName);
    unk31c = p2;
    m_sequenceStep = 3;
}

int gfSceneManager::setLoadModuleName(const char* moduleName, const char* sceneName, bool p3,
                                      bool p4) {
    for (int i = 0; i < 11; i++) {
        if (!m_loadModules[i].m_moduleName) {
            m_loadModules[i].m_moduleName = moduleName;
            m_loadModules[i].m_sceneName = sceneName;
            m_loadModules[i].unk8 = p3;
            if (p4 == true)
                m_loadModules[i].m_status = 1;
            else
                m_loadModules[i].m_status = 2;
            return i;
        }
    }
    return -1;
}

bool gfSceneManager::loadModule() {
    bool result = false;
    switch (m_loadState) {
    case 0:
        for (int i = 0; i < 11; i++) {
            if (m_loadModules[i].m_moduleName && m_loadModules[i].m_status == 1) {
                m_loadIndex = i;
                if (m_loadModules[i].unk8) {
                    g_gfModuleManager->setTempolaryLoadHeap(Heaps::Network);
                    gfModuleManager::LoadRequestResult loadResult;
                    gfModuleManager::loadModuleRequest(&loadResult, g_gfModuleManager,
                                                       m_loadModules[m_loadIndex].m_moduleName,
                                                       Heaps::OverlayCommon, true, false);
                } else {
                    if (g_HeapInfos[Heaps::MenuInstance].m_name)
                        g_gfModuleManager->setTempolaryLoadHeap(Heaps::MenuInstance);
                    else
                        g_gfModuleManager->setTempolaryLoadHeap(Heaps::InfoInstance);
                    gfModuleManager::LoadRequestResult loadResult;
                    gfModuleManager::loadModuleRequest(&loadResult, g_gfModuleManager,
                                                       m_loadModules[m_loadIndex].m_moduleName,
                                                       Heaps::OverlayMenu, true, false);
                }
                m_loadState = 1;
                result = true;
                break;
            }
        }
        break;
    case 1:
        if (g_gfModuleManager->isLoaded(m_loadModules[m_loadIndex].m_moduleName) == true) {
            m_loadModules[m_loadIndex].m_status = 2;
            m_loadState = 0;
        }
        result = true;
        break;
    }
    return result;
}
