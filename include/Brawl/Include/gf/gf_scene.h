#pragma once

#include <StaticAssert.h>
#include <types.h>

class gfScene {
public:
    const char* m_sceneName;
    virtual void start() = 0;
    virtual s32 process() = 0;
    virtual s32 exit() = 0;
    virtual void setModule() { }

    bool setLoadModule(const char* name, bool p2);

    gfScene(const char* name) : m_sceneName(name) { }
};
static_assert(sizeof(gfScene) == 8, "Class is wrong size!");

class gfSequence {
public:
    const char* m_sequenceName;
    virtual void start();
    virtual void setNext();
    virtual void exit();
};
static_assert(sizeof(gfSequence) == 8, "Class is wrong size!");

class gfSceneManager {
public:
    struct LoadModuleInfo {
        const char* m_moduleName;
        const char* m_sceneName;
        bool unk8;
        u8 m_status;

        LoadModuleInfo() : m_moduleName(nullptr), m_sceneName(nullptr), unk8(false), m_status(0) { }
    };
    static_assert(sizeof(LoadModuleInfo) == 0xC, "Class is wrong size!");

    gfScene* m_prevScene;
    gfScene* m_currentScene;
    gfScene* m_nextScene;
    gfSequence* m_prevSequence;
    gfSequence* m_currentSequence;
    gfSequence* m_nextSequence;
    gfScene* m_scenes[100];
    gfSequence* m_sequences[50];
    int m_sceneCount;
    int m_sequenceCount;
    bool unk278_b7 : 1;
    bool unk278_b6 : 1;
    gfScene* m_exitScene;
    int m_memoryLayout; // 0x280
    int unk1;
    int processStep;
    int m_sequenceStep;
    LoadModuleInfo m_loadModules[11]; // 0x290
    int m_loadState;                  // 0x314
    int m_loadIndex;
    int unk31c;

    gfSceneManager();
    static gfSceneManager* create();
    void changeNextScene();
    int registScene(gfScene* scene);
    int registSequence(gfSequence* sequence);
    int process();
    int postProcess();
    gfScene* searchScene(const char* sceneName) const;
    gfSequence* searchSequence(const char* sequenceName) const;
    void startSequence(const char* sequenceName, int p2);
    void setNextScene(const char* sceneName, int memoryLayout);
    void setNextSequence(const char* sequenceName, int p2);
    int setLoadModuleName(const char* moduleName, const char* sceneName, bool p3, bool p4);
    bool loadModule();
    static gfSceneManager* getInstance();
};
static_assert(sizeof(gfSceneManager) == 800, "Class is wrong size!");

extern gfSceneManager* g_gfSceneManager;
