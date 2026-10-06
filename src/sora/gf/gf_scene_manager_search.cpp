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
