#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>
#include <cstring>

struct grGimmickLadderData {
    grGimmickMotionPathData m_motionPathData;
    stGimmickAreaData m_areaData;
    u8 m_mdlIndex;
    char m_49;
    bool m_restrictUpExit;
    bool m_51;
    char m_nodeName[32]; // unused
    stTriggerData m_isValidTriggerData;
    stTriggerData m_motionPathTriggerData;

    inline grGimmickLadderData() {

    };

    inline grGimmickLadderData(u8 mdlIndex, int unk1, bool restrictUpExit, int unk2, const char* nodeName,
                                 Vec2f* areaPos, Vec2f* areaRange) {
        initialize(mdlIndex, unk1, restrictUpExit, unk2, nodeName,
                   areaPos, areaRange);
    };

    inline void initialize(u8 mdlIndex, int unk1, bool restrictUpExit, int unk2, const char* nodeName,
                           Vec2f* areaPos, Vec2f* areaRange) {
        MEMINIT(this);
        m_mdlIndex = mdlIndex;
        m_49 = unk1;
        m_restrictUpExit = restrictUpExit;
        m_51 = unk2;
        strcpy(m_nodeName, nodeName);
        m_areaData.set(areaPos, areaRange);
    };
};
static_assert(sizeof(grGimmickLadderData) == 92, "Class is wrong size!");

class grGimmickLadder : public grYakumono {
protected:
    grGimmickLadderData* m_ladderData;
    soAreaData m_areaData;
    soSet<soAreaData> m_areaDataSet;
    ykAreaData m_ykData;
    Vec3f m_upperOffsetPos;
    Vec3f m_underOffsetPos;

public:
    grGimmickLadder(const char* taskName);
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual bool disableArea();
    virtual bool setSleepArea(bool);
    virtual void setInitializeFlag();
    virtual ~grGimmickLadder();
    virtual void getUpperNode(Vec3f* pos);
    virtual void getUnderNode(Vec3f* pos);

    static grGimmickLadder* create(s16 mdlIndex, const char* taskName);
};
static_assert(sizeof(grGimmickLadder) == 416, "Class is wrong size!");
