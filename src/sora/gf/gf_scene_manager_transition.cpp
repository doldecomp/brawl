#include <cstring>
#include <gf/gf_scene.h>

static inline gfScene* findScene(gfSceneManager* manager, const char* name) {
    const s32 count = manager->m_sceneCount;
    for (s32 i = 0; i < count; i++) {
        if (std::strcmp(manager->m_scenes[i]->m_sceneName, name) == 0) {
            return manager->m_scenes[i];
        }
    }
    return nullptr;
}

static inline gfSequence* findSequence(gfSceneManager* manager, const char* name) {
    const s32 count = manager->m_sequenceCount;
    for (s32 i = 0; i < count; i++) {
        if (std::strcmp(manager->m_sequences[i]->m_sequenceName, name) == 0) {
            return manager->m_sequences[i];
        }
    }
    return nullptr;
}

void gfSceneManager::startSequence(const char* name, int p2) {
    _spacer3[0] &= ~0x80;
    m_currentSequence = findSequence(this, name);
    unk31C = p2;
    m_currentSequence->start();
    unk28C = 1;
    changeNextScene();
}

void gfSceneManager::setNextScene(const char* name, int memoryLayout) {
    m_nextScene = findScene(this, name);
    m_memoryLayout = memoryLayout;
    processStep = 3;
}

void gfSceneManager::setNextSequence(const char* name, int p2) {
    m_nextSequence = findSequence(this, name);
    unk31C = p2;
    unk28C = 3;
}
