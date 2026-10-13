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
    char _spacer3[8];
    int m_memoryLayout; // 0x280
    int unk1;
    int processStep;
    char _spacer4[148];

    gfScene* searchScene(const char* sceneName);
    static gfSceneManager* getInstance();
};
static_assert(sizeof(gfSceneManager) == 800, "Class is wrong size!");
