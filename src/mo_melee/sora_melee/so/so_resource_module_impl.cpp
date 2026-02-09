#include <gf/gf_archive.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <so/so_archive_db.h>
#include <so/resource/so_resource_module_impl.h>
#include <so/resource/so_resource_id_accesser.h>
#include <types.h>
#include <ut/ut_archive_manager.h>

soResourceModuleImpl::
soResourceModuleImpl(u32 mId, soResourceIdAccesserImpl* rsrcIdAcc, u32 arcGrp) {
    m_managerID = mId;
    m_resourceIdAccesser = rsrcIdAcc;
    m_archiveType1 = arcGrp;
    m_archiveType2 = arcGrp;
    m_archiveType3 = arcGrp;
    m_archiveType4 = arcGrp;
}

soResourceModuleImpl::~soResourceModuleImpl() { }

void soResourceModuleImpl::setGroupNo(u8 unk1, u16 index) {
    if (index == 0xFF) {
        m_archiveType1 = unk1;
        m_archiveType2 = unk1;
        m_archiveType3 = unk1;
        m_archiveType4 = unk1;
        return;
    }
    u8* ptr = (u8*)((u32)this + index);
    ptr[0x14] = unk1;
}

nw4r::g3d::ResFile soResourceModuleImpl::getTexFile(u16 fileIndex, u32 texResId) {
    if (texResId == 0xFFFF) {
        texResId = m_resourceIdAccesser->getTexResId();
    }
    if (texResId != 0xFFFF) {
        u32 arcId = m_resourceIdAccesser->getTexArchiveId();
        u32 grpNo = getGroupNo(2);
        utArchiveManager* arcManager = soArchiveDb::getManager(m_managerID);
        return arcManager->getResFileFromId(texResId, Data_Type_Tex, fileIndex, (u8)grpNo, arcId);
    }
    return nw4r::g3d::ResFile();
}

nw4r::g3d::ResFile soResourceModuleImpl::getMdlFile(u16 fileIndex, u32 mdlResId) {
    if (mdlResId == 0xFFFF) {
        mdlResId = m_resourceIdAccesser->getMdlResId();
    }
    if (mdlResId != 0xFFFF) {
        u32 arcId = m_resourceIdAccesser->getMdlArchiveId();
        u32 grpNo = getGroupNo(1);
        utArchiveManager* arcManager = soArchiveDb::getManager(m_managerID);
        return arcManager->getResFileFromId(mdlResId, Data_Type_Model, fileIndex, (u8)grpNo, arcId);
    }
    return nw4r::g3d::ResFile();
}

nw4r::g3d::ResFile soResourceModuleImpl::getAnmFile(u16 fileIndex, u32 anmResId, u32 p3) {
    u32 arcId = m_resourceIdAccesser->getAnmArchiveId();
    if (anmResId == 0xFFFF) {
        anmResId = m_resourceIdAccesser->getAnmResId();
    }
    if (p3 == 1) {
        arcId = -1;
    }
    if (anmResId != 0xFFFF) {
        p3 = getGroupNo(3);
        utArchiveManager* arcManager = soArchiveDb::getManager(m_managerID);
        return arcManager->getResFileFromId(anmResId, Data_Type_Anim, fileIndex, (u8)p3, arcId);
    }
    return nw4r::g3d::ResFile();
}

nw4r::g3d::ResFile soResourceModuleImpl::getBinFile(u32 binResId, u16 fileIndex, s32 archiveId) {
    u32 r31 = binResId;
    if (binResId == 0xFFFF) {
        r31 = m_resourceIdAccesser->getBinResId();
    }
    if ((s32)archiveId == -1) {
        archiveId = m_resourceIdAccesser->getBinArchiveId();
    }
    if (r31 != 0xFFFF) {
        r31 = getGroupNo(0);
        utArchiveManager* arcManager = soArchiveDb::getManager(m_managerID);
        return arcManager->getResFileFromId(binResId, Data_Type_Misc, fileIndex, (u8)r31, archiveId);
    }
    return nw4r::g3d::ResFile();
}

nw4r::g3d::ResFile soResourceModuleImpl::getFile(u32 resId, ARCNodeType nodeType, u16 fileIndex) {
    if (resId != 0xFFFF) {
        u32 arcId = m_resourceIdAccesser->getBinArchiveId();
        u32 grpNo = getGroupNo(0);
        utArchiveManager* arcManager = soArchiveDb::getManager(m_managerID);
        return arcManager->getResFileFromId(resId, nodeType, fileIndex, (u8)grpNo, arcId);
    }
    return nw4r::g3d::ResFile();
}
