#pragma once

#include <StaticAssert.h>
#include <ad/ad_autosave.h>
#include <mu/adv/mu_adv_saveload.h>
#include <mu/menu.h>
#include <types.h>

class scAdvSave : public muMenu {
    u8 unk350[0xC];
    muAdvSaveTask* m_task;
    adAutoSave* m_autosave;
public:
    static scAdvSave* create();
    scAdvSave(const char* name) : muMenu(name), m_task(nullptr) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvSave) == 0x364, "Class is the wrong size!");

class scAdvLoad : public muMenu {
    u8 unk350[0xC];
    muAdvLoadTask* m_task;
public:
    static scAdvLoad* create();
    scAdvLoad(const char* name) : muMenu(name), m_task(nullptr) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scAdvLoad) == 0x360, "Class is the wrong size!");

