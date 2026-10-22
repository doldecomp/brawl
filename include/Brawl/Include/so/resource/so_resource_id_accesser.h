#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>

class soResourceIdAccesser : public soNullable {
public:
    soResourceIdAccesser(bool isNull) : soNullable(isNull) { }
    virtual ~soResourceIdAccesser() = 0;
    virtual void setResIdPacked(u32 id) { }
    virtual void setAnmResId(u32 id) { }
    virtual void setMdlResId(u32 id) { }
    virtual void setTexResId(u32 id) { }
    virtual void setMdlResIndex(u16 idx) { }
    virtual void setTexResIndex(u16 idx) { }
    virtual u32 getTexResId() = 0;
    virtual u32 getTexResIndex() { return 0; }
    virtual u32 getMdlResId() = 0;
    virtual u32 getMdlResIndex() { return 0; }
    virtual u32 getAnmResId() = 0;
    virtual u32 getBinResId() = 0;
    virtual u32 getArchiveId() = 0;
    virtual u32 getEtcResId() = 0;
    virtual u32 getMdlArchiveId() = 0;
    virtual u32 getTexArchiveId() = 0;
    virtual u32 getAnmArchiveId() = 0;
    virtual u32 getEtcArchiveId() = 0;
    virtual u32 getBinArchiveId() = 0;
};
static_assert(sizeof(soResourceIdAccesser) == 0x8, "Class is the wrong size!");

class soResourceIdAccesserImpl : public soResourceIdAccesser {
    u32 m_mdlResId;
    u32 m_texResId;
    u32 m_anmResId;
    u16 m_mdlResIndex;
    u16 m_texResIndex;
public:
    soResourceIdAccesserImpl(u32 mdlId, u32 texId, u32 anmId) :
        soResourceIdAccesser(false),
        m_mdlResId(mdlId),
        m_texResId(texId),
        m_anmResId(anmId),
        m_mdlResIndex(0),
        m_texResIndex(0) { }
    virtual ~soResourceIdAccesserImpl() { }
    virtual void setResIdPacked(u32 id) {
        m_anmResId = id;
        m_texResId = id;
        m_mdlResId = id;
    }
    virtual void setAnmResId(u32 id) { m_anmResId = id; }
    virtual void setMdlResId(u32 id) { m_mdlResId = id; }
    virtual void setTexResId(u32 id) { m_texResId = id; }
    virtual void setMdlResIndex(u16 idx) { m_mdlResIndex = idx; }
    virtual void setTexResIndex(u16 idx) { m_texResIndex = idx; }
    virtual u32 getTexResId() { return m_texResId; }
    virtual u32 getTexResIndex() { return m_texResIndex; }
    virtual u32 getMdlResId() { return m_mdlResId; }
    virtual u32 getMdlResIndex() { return m_mdlResIndex; }
    virtual u32 getAnmResId() { return m_anmResId; }
    virtual u32 getBinResId() { return m_anmResId; }
    virtual u32 getEtcResId() { return m_anmResId; }
    virtual u32 getMdlArchiveId() { return getArchiveId(); }
    virtual u32 getTexArchiveId() { return getArchiveId(); }
    virtual u32 getAnmArchiveId() { return getArchiveId(); }
    virtual u32 getEtcArchiveId() { return getArchiveId(); }
    virtual u32 getArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getBinArchiveId() { return getArchiveId(); }
};
static_assert(sizeof(soResourceIdAccesserImpl) == 0x18, "Class is the wrong size!");

class soResourceIdAccesserNull : public soResourceIdAccesser {
public:
    soResourceIdAccesserNull() : soResourceIdAccesser(true) { }
    virtual ~soResourceIdAccesserNull() { }
    virtual u32 getTexResId() { return 0xFFFF; }
    virtual u32 getMdlResId() { return 0xFFFF; }
    virtual u32 getAnmResId() { return 0xFFFF; }
    virtual u32 getBinResId() { return 0xFFFF; }
    virtual u32 getEtcResId() { return 0xFFFF; }
    virtual u32 getArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getMdlArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getTexArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getAnmArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getEtcArchiveId() { return 0xFFFFFFFF; }
    virtual u32 getBinArchiveId() { return 0xFFFFFFFF; }
};
static_assert(sizeof(soResourceIdAccesserNull) == 0x8, "Class is the wrong size!");

extern soResourceIdAccesserNull g_soResourceIdAccesserNull;
