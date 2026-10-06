#include <gf/gf_scene.h>

s32 gfSceneManager::registScene(gfScene* scene) {
    const s32 index = m_sceneCount++;
    m_scenes[index] = scene;
    return index;
}

s32 gfSceneManager::registSequence(gfSequence* sequence) {
    const s32 index = m_sequenceCount++;
    m_sequences[index] = sequence;
    return index;
}
