#pragma once

#include <StaticAssert.h>
#include <if/if_stgedit.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <sr/sr_common.h>
#include <types.h>

class IfStgedit {
    nw4r::g3d::ScnGroup* m_scnGroup;
    MuObject* m_modelNodes[1];
    bool m_visible;
    u32 m_helpPadNun;

    static const u8 Frames[4];
public:
    IfStgedit();
    virtual ~IfStgedit();

    void createModel(nw4r::g3d::ResFile* mdlSrc);
    void createObjResFile(const void* nodeInfo, s32 nodeCount,
                          nw4r::g3d::ResFile* mdlSrc, s32 prio);
    void startMelee(nw4r::g3d::ScnGroup* grp);
    void main();
    void setVisible(bool vis);
    void setHelpControllerNo(u32 num);
    void setVisibleZoomHelp(bool p1);
};
static_assert(sizeof(IfStgedit) == 0x14, "Class is the wrong size!");
