#pragma once

#include <StaticAssert.h>
#include <so/resource/so_resource_id_accesser.h>
#include <types.h>

class soModuleAccesser;

class ftResourceIdAccesserImpl : public soResourceIdAccesser {
    soModuleAccesser* m_moduleAccsr;
public:
    ftResourceIdAccesserImpl(soModuleAccesser* acc) :
        soResourceIdAccesser(false), m_moduleAccsr(acc) { }
    virtual ~ftResourceIdAccesserImpl() { }
    virtual u32 getTexResId() { return getMdlResId(); }
    virtual u32 getMdlResId();
    virtual u32 getAnmResId();
    virtual u32 getBinResId();
    virtual u32 getArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getEtcResId();
    virtual u32 getMdlArchiveId();
    virtual u32 getTexArchiveId();
    virtual u32 getAnmArchiveId();
    virtual u32 getEtcArchiveId();
    virtual u32 getBinArchiveId();
    virtual u32 getKirbyResId();

    u32 getFinalResId();
    u32 getEntryResId();
    u32 getResultResId();
};
static_assert(sizeof(ftResourceIdAccesserImpl) == 0xC, "Class is the wrong size!");

class ftKirbyResourceIdAccesserImpl : public ftResourceIdAccesserImpl {
public:
    ftKirbyResourceIdAccesserImpl(soModuleAccesser* acc) :
        ftResourceIdAccesserImpl(acc) { }
    virtual ~ftKirbyResourceIdAccesserImpl() { }
    virtual u32 getTexResId();
    virtual u32 getKirbyResId();
};
static_assert(sizeof(ftKirbyResourceIdAccesserImpl) == 0xC, "Class is the wrong size!");

class ftPopoResourceIdAccesserImpl : public ftResourceIdAccesserImpl {
    u32 m_mdlResIndex;
public:
    ftPopoResourceIdAccesserImpl(soModuleAccesser* acc) :
        ftResourceIdAccesserImpl(acc), m_mdlResIndex(0) { }
    virtual ~ftPopoResourceIdAccesserImpl() { }
    virtual void setMdlResIndex(u16 idx) { m_mdlResIndex = idx; }
    virtual void setTexResIndex(u16 idx) { }
    virtual u32 getTexResIndex() { return 0; }
    virtual u32 getMdlResIndex() { return m_mdlResIndex; }
};
static_assert(sizeof(ftPopoResourceIdAccesserImpl) == 0x10, "Class is the wrong size!");
