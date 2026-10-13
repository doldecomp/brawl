#pragma once

#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gf/gf_resource_loader.h>
#include <gf/gf_scene.h>
#include <mu/adv/mu_adv_seal.h>
#include <types.h>

class scSealDisp : public gfScene {
    muAdvSealTask* m_task;
    s32 m_state;
    gfArchive* m_archive;
    gfResourceLoader* m_loader;
public:
    static scSealDisp* create();
    scSealDisp(const char* name) : gfScene(name), m_task(nullptr), m_state(-1),
            m_archive(nullptr), m_loader(nullptr) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
};
static_assert(sizeof(scSealDisp) == 0x18, "Class is the wrong size!");
