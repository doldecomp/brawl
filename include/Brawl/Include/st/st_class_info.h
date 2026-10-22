#pragma once

#include <StaticAssert.h>
#include <gm/gm_lib.h>
#include <types.h>

class stClassInfo {
private:
public:
    void setClassInfo(Stages::srStageKind, stClassInfo*);
    stClassInfo();
    virtual ~stClassInfo();
};

template <Stages::srStageKind I, class T>
class stClassInfoImpl : public stClassInfo {
private:
public:
    stClassInfoImpl() : stClassInfo() { setClassInfo(I, this); };
    virtual ~stClassInfoImpl();
    virtual T* create();
    virtual void preload();
};

#define ST_CLASS_INFO                              \
    template <Stages::srStageKind I, typename T>   \
    T* stClassInfoImpl<I, T>::create()             \
    {                                              \
        T* stage = new (Heaps::StageInstance) T(); \
        return stage;                              \
    };                                             \
    template <Stages::srStageKind I, typename T>   \
    stClassInfoImpl<I, T>::~stClassInfoImpl()      \
    {                                              \
        setClassInfo(I, 0);                        \
    }                                              \
    template <Stages::srStageKind I, typename T>   \
    void stClassInfoImpl<I, T>::preload()          \
    {                                              \
        return;                                    \
    }
