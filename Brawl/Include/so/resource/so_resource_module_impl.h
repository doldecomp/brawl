#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/resource/so_resource_id_accesser.h>
#include <gf/gf_archive.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <types.h>

class soResourceModule : private soNull, public soNullable {
public:
    soResourceModule(bool isNull) : soNullable(isNull) { }
    virtual ~soResourceModule() { }
    virtual soResourceIdAccesser* getResourceIdAccesser() = 0;
    virtual u32 getGroupNo(int unk1) = 0;
    virtual void setGroupNo(u8 unk1, u16 index) = 0;
    virtual nw4r::g3d::ResFile getTexFile(u16 fileIndex, u32 texResId) = 0;
    virtual nw4r::g3d::ResFile getMdlFile(u16 fileIndex, u32 mdlResId) = 0;
    virtual nw4r::g3d::ResFile getAnmFile(u16 fileIndex, u32 anmResId, u32 p3) = 0;
    virtual nw4r::g3d::ResFile getBinFile(u32 binResId, u16 fileIndex, s32 archiveId) = 0;
    virtual void* getFile(u32 resId, ARCNodeType nodeType, u16 fileIndex) = 0;
};
static_assert(sizeof(soResourceModule) == 0xC, "Class is the wrong size!");

class soResourceModuleImpl : public soResourceModule {
    // 0xC
    int m_managerID;
    // 0x10
    soResourceIdAccesser* m_resourceIdAccesser;
    // 0x14
    char m_archiveType1;
    // 0x15
    char m_archiveType2;
    // 0x16
    char m_archiveType3;
    // 0x17
    char m_archiveType4;
public:
    soResourceModuleImpl(u32 mId, soResourceIdAccesser* rsrcIdAcc, u8 arcGrp);

    virtual ~soResourceModuleImpl();
    virtual soResourceIdAccesser* getResourceIdAccesser() { return m_resourceIdAccesser; }
    virtual u32 getGroupNo(int unk1) {
        // TODO: UBFIX just a char array?
        u8* ptr = (u8*)((int)this + unk1);
        return ptr[0x14];
    }
    virtual void setGroupNo(u8 unk1, u16 index);
    virtual nw4r::g3d::ResFile getTexFile(u16 fileIndex, u32 texResId);
    virtual nw4r::g3d::ResFile getMdlFile(u16 fileIndex, u32 mdlResId);
    virtual nw4r::g3d::ResFile getAnmFile(u16 fileIndex, u32 anmResId, u32 p3);
    virtual nw4r::g3d::ResFile getBinFile(u32 binResId, u16 fileIndex, s32 archiveId);
    virtual void* getFile(u32 resId, ARCNodeType nodeType, u16 fileIndex);
};
static_assert(sizeof(soResourceModuleImpl) == 0x18, "Class is the wrong size!");

class soResourceModuleNull : public soResourceModule {
public:
    soResourceModuleNull(bool isNull) : soResourceModule(true) { }
    virtual ~soResourceModuleNull() { }
    virtual soResourceIdAccesser* getResourceIdAccesser() {
        return &g_soResourceIdAccesserNull;
    }
    virtual u32 getGroupNo(int unk1) { return 0; }
    virtual void setGroupNo(u8 unk1, u16 index) { }

    virtual nw4r::g3d::ResFile getTexFile(u16 fileIndex, u32 texResId) {
        return nw4r::g3d::ResFile();
    }

    virtual nw4r::g3d::ResFile getMdlFile(u16 fileIndex, u32 mdlResId) {
        return nw4r::g3d::ResFile();
    }

    virtual nw4r::g3d::ResFile getAnmFile(u16 fileIndex, u32 anmResId, u32 p3) {
        return nw4r::g3d::ResFile();
    }

    virtual nw4r::g3d::ResFile getBinFile(u32 binResId, u16 fileIndex, s32 archiveId) {
        return nw4r::g3d::ResFile();
    }

    virtual void* getFile(u32 resId, ARCNodeType nodeType, u16 fileIndex) {
        return nullptr;
    }
};
static_assert(sizeof(soResourceModuleNull) == 0xC, "Class is the wrong size!");

extern soResourceModuleNull g_soResourceModuleNull;
