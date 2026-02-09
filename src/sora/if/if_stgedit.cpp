#include <StaticAssert.h>
#include <cstring>
#include <gf/gf_pad_system.h>
#include <if/if_stgedit.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <sr/sr_common.h>
#include <types.h>

struct UnkModelNodeInfo {
    const char* m_name;
    u8 unk4;
    u8 unk5;
    u8 unk6;
};
static_assert(sizeof(UnkModelNodeInfo) == 0x8, "Class is the wrong size!");

static const UnkModelNodeInfo g_ModelNodeInfo = { "MenStgedit0100_TopN", 0, 0, 1 };

IfStgedit::IfStgedit() {
    m_scnGroup = nullptr;
    for (u32 i = 0; i < 1; i++) {
        m_modelNodes[i] = nullptr;
    }
    m_visible = false;
    m_helpPadNun = 0;
}

IfStgedit::~IfStgedit() {
    for (u32 i = 0; i < 1; i++) {
        if (m_modelNodes[i]) {
            delete m_modelNodes[i];
            m_modelNodes[i] = nullptr;
        }
    }
}

void IfStgedit::createModel(nw4r::g3d::ResFile* mdlSrc) {
    createObjResFile(&g_ModelNodeInfo, 1, mdlSrc, 0);
}

void IfStgedit::createObjResFile(const void* nodeInfo, s32 nodeCount,
                                 nw4r::g3d::ResFile* mdlSrc, s32 prio) {
    s32 i;
    s32 j;
    const UnkModelNodeInfo* p = static_cast<const UnkModelNodeInfo*>(nodeInfo);
    char nameBuf[0x40];
    for (i = 0; i < nodeCount; i++, p++) {
        s32 nCopies = (p->unk4 < p->unk5) ? p->unk5 - p->unk4 : 1;
        for (j = 0; j < nCopies; j++) {
            MuObject* obj = MuObject::create(mdlSrc, p->m_name, p->unk6 + prio + j,
                                             0, Heaps::InfoInstance);
            m_modelNodes[p->unk4 + j] = obj;
            strcpy(nameBuf, p->m_name);
            strcat(nameBuf, "__0");
            obj->changeAnimN(nameBuf);
            if (obj->m_modelAnim) {
                obj->m_modelAnim->setUpdateRate(0);
            }
        }
    }
}

void IfStgedit::startMelee(nw4r::g3d::ScnGroup* grp) {
    m_scnGroup = grp;
}

void IfStgedit::main() {
    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus(m_helpPadNun, &status);
    if (status.m_error == gfPadError::NONE) {
        m_modelNodes[0]->setFrameVisible(Frames[status.m_controllerType]);
    }
}

const u8 IfStgedit::Frames[] = { 0, 3, 2, 1 };

void IfStgedit::setVisible(bool vis) {
    m_visible = vis;
    m_scnGroup->Remove(m_modelNodes[0]->m_sceneModel);
    if (vis) {
        m_scnGroup->Insert(m_scnGroup->sceneItemsCount, m_modelNodes[0]->m_sceneModel);
    }
}

void IfStgedit::setHelpControllerNo(u32 num) {
    m_helpPadNun = num;
    main();
}

void IfStgedit::setVisibleZoomHelp(bool p1) {
    float frame = p1 ? 0.0f : 1.0f;
    m_modelNodes[0]->setFrameNode(frame);
}
