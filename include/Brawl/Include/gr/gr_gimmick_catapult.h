#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>

struct grGimmickCatapultData {
    grGimmickMotionPathData m_motionPathData;
    stGimmickAreaData m_areaData;
    float m_startMoveFrame;
    float m_52;
    float m_56;
    float m_vector;
    char _64[16];
    u8 m_mdlIndex;
    bool m_isFaceLeft;
    bool m_useNoHelperWarp;
    char _82[1];

    inline grGimmickCatapultData() {

    };

    inline grGimmickCatapultData(float startMoveFrame, float unk1, float unk2, float vector, u8 mdlIndex, bool isFaceLeft, bool useNoHelperWarp,
                               float motionRatio, u8 motionPathIndex, u8 motionPathMdlIndex, u8 motionPathUnk,
                               Vec2f* areaPos, Vec2f* areaRange) {
        initialize(startMoveFrame, unk1, unk2, vector, mdlIndex, isFaceLeft, useNoHelperWarp,
                   motionRatio, motionPathIndex, motionPathMdlIndex, motionPathUnk,
                   areaPos, areaRange);
    };

    inline void initialize(float startMoveFrame, float unk1, float unk2, float vector, u8 mdlIndex, bool isFaceLeft, bool useNoHelperWarp,
                           float motionRatio, u8 motionPathIndex, u8 motionPathMdlIndex, u8 motionPathUnk,
                           Vec2f* areaPos, Vec2f* areaRange) {
        MEMINIT(this);
        m_startMoveFrame = startMoveFrame;
        m_52 = unk1;
        m_56 = unk2;
        m_vector = vector;
        m_mdlIndex = mdlIndex;
        m_isFaceLeft = isFaceLeft;
        m_useNoHelperWarp = useNoHelperWarp;
        m_motionPathData.set(motionRatio, motionPathIndex, motionPathMdlIndex, motionPathUnk);
        m_areaData.set(areaPos, areaRange);
    };
};
static_assert(sizeof(grGimmickCatapultData) == 84, "Class is wrong size!");

class grGimmickCatapult : public grYakumono {

protected:
    grGimmickCatapultData* m_catapultData;
    grGimmickMotionPath* m_motionPath;
    u8 m_state;
    char m_345[3];
    float m_frameCount;
    char m_352[8];
    int m_360;
    int m_364;
    soAreaData m_areaData;
    soSet<soAreaData> m_areaDataSet;
    ykAreaData m_ykData;

public:
    inline grGimmickCatapult(const char* taskName) : grYakumono(taskName)
    {
        m_motionPath = NULL;
        m_state = 0;
        m_frameCount = 0.0;
        m_360 = -1;
        m_364 = -1;
    };
    virtual void processFixPosition();
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual ~grGimmickCatapult();

    void presentFighterPosEvent();

    static grGimmickCatapult* create(s16 mdlIndex, const char* taskName);
};
static_assert(sizeof(grGimmickCatapult) == 420, "Class is wrong size!");
