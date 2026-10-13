#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick_motion_path.h>
#include <gr/gr_yakumono.h>
#include <snd/snd_id.h>
#include <st/st_trigger.h>

struct grGimmickWarpData {
    grGimmickMotionPathData m_motionPathData;
    stGimmickAreaData m_areaData;
    char _48[32];
    u8 m_mdlIndex;
    char _81[3];
    Vec2f m_pos;
    SndID m_sndIDs[2];
    char _100[8];
    stTriggerData m_warpTriggerData;
    char _112[12];
    stTriggerData m_isValidTriggerData;

    inline grGimmickWarpData() {

    };

    inline grGimmickWarpData(Vec2f* pos, u8 mdlIndex, SndID sndIn, SndID sndOut,
            Vec2f* areaPos, Vec2f* areaRange) {
        initialize(pos, mdlIndex, sndIn, sndOut,
                   areaPos, areaRange);
    };

    inline void initialize(Vec2f* pos, u8 mdlIndex, SndID sndIn, SndID sndOut,
                           Vec2f* areaPos, Vec2f* areaRange) {
        MEMINIT(this);
        m_pos = *pos;
        m_mdlIndex = mdlIndex;
        m_sndIDs[0] = sndIn,
        m_sndIDs[1] = sndOut,
        m_areaData.set(areaPos, areaRange);
    };
};
static_assert(sizeof(grGimmickWarpData) == 128, "Class is wrong size!");

class grGimmickWarpZone : public grYakumono {
protected:
    grGimmickWarpData* m_warpData;
    u8 m_state;
    char _277[3];
    float m_frameCount;
    Vec3f m_warpDest;
    u8 m_warpType;
    bool m_isNotAuto;
    char m_298[2];
    soAreaData m_areaData;
    soSet<soAreaData> m_areaDataSet;
    ykAreaData m_ykData;

public:
    grGimmickWarpZone(const char* taskName);
    virtual ~grGimmickWarpZone();
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void setInitializeFlag();
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual void setWarpAttrData(Vec3f* warpDest, u8 warpType, bool isNotAuto);
};
static_assert(sizeof(grGimmickWarpZone) == 416, "Class is wrong size!");