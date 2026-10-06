#include <cstring>
#include <gf/gf_scene.h>

gfScene* gfSceneManager::searchScene(const char* sceneName) {
    const s32 sceneCount = m_sceneCount;
    for (s32 i = 0; i < sceneCount; i++) {
        if (std::strcmp(m_scenes[i]->m_sceneName, sceneName) == 0) {
            return m_scenes[i];
        }
    }
    return nullptr;
}

gfSequence* gfSceneManager::searchSequence(const char* sequenceName) {
    const s32 sequenceCount = m_sequenceCount;
    for (s32 i = 0; i < sequenceCount; i++) {
        if (std::strcmp(m_sequences[i]->m_sequenceName, sequenceName) == 0) {
            return m_sequences[i];
        }
    }
    return nullptr;
}
