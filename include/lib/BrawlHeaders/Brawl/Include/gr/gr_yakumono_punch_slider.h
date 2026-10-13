#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick_motion_path.h>
#include <gr/gr_yakumono.h>
#include <st/st_trigger.h>
#include <cstring>

struct grGimmickPunchSliderData {
    grGimmickMotionPathData m_motionPathData;
    grGimmickMotionPathData m_sliderPathData;
    grGimmick::HitData m_hitData;
    char _48[4];
    grGimmick::AttackData m_attackData;
    char _140[8];
    float m_148;
    float m_152;
    float m_156;
    float m_160;
    float m_164;
    float m_168;
    float m_difficultyMotionRatios[15];
    stTriggerData m_triggerData;
    char _232[12];
    u8 m_mdlIndex;
    char _249[3];
    char m_ballNodeName[32];
    char _284[4];

    inline grGimmickPunchSliderData() {

    };

    inline grGimmickPunchSliderData(float unk1, float unk2, float unk3, float unk4, float unk5, float unk6,
                                    grGimmick::AttackData* attackData, float hitSize, const char* nodeName,
                                    float motionRatio, u8 motionPathIndex, grGimmickMotionPathData::PathMode pathMode, u8 motionPathMdlIndex, u8 motionPathUnk,
                                    float sliderRatio, u8 sliderPathIndex, u8 sliderPathMdlIndex, u8 sliderPathUnk) {
        initialize(unk1, unk2, unk3, unk4, unk5, unk6,
                   attackData, hitSize, nodeName,
                   motionRatio, motionPathIndex, pathMode, motionPathMdlIndex, motionPathUnk,
                   sliderRatio, sliderPathIndex, sliderPathMdlIndex, sliderPathUnk);
    };

    inline void initialize(float unk1, float unk2, float unk3, float unk4, float unk5, float unk6,
                           grGimmick::AttackData* attackData, float hitSize, const char* nodeName,
                           float motionRatio, u8 motionPathIndex, grGimmickMotionPathData::PathMode pathMode, u8 motionPathMdlIndex, u8 motionPathUnk,
                           float sliderRatio, u8 sliderPathIndex, u8 sliderPathMdlIndex, u8 sliderPathUnk) {

        MEMINIT(this);
        m_148 = unk1;
        m_152 = unk2;
        m_156 = unk3;
        m_160 = unk4;
        m_164 = unk5;
        m_168 = unk6;
        m_attackData = *attackData;
        m_hitData.m_size = hitSize;
        strcpy(m_ballNodeName, nodeName);
        m_motionPathData.set(motionRatio, motionPathIndex, pathMode, motionPathMdlIndex, motionPathUnk);
        m_sliderPathData.set(sliderRatio, sliderPathIndex, grGimmickMotionPathData::Path_Return, sliderPathMdlIndex, sliderPathUnk);
    };
};
static_assert(sizeof(grGimmickPunchSliderData) == 288, "Class is wrong size!");

class grYakumonoPunchSlider : public grYakumono {
protected:
    grGimmickMotionPath* m_sliderMotionPath;
    grGimmickPunchSliderData* m_sliderData;
    u8 m_280;
    char _281[3];
    int m_ballNodeIndex;
    int m_polyGlowNodeIndex;
    int m_292;
    char _296[32];
    soCollisionHitData m_hitData;
    soSet<soCollisionHitData> m_hitDataSet;
    ykDataGroup m_ykDataGroup;
    ykData m_ykData;

public:
    grYakumonoPunchSlider(const char* taskName);
    virtual ~grYakumonoPunchSlider();
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo);
    virtual void onInflict(soCollisionLog* collisionLog, u32 unk2, float power);
    virtual void updateMove(float deltaFrame);
    virtual void createMotionPath();
    virtual void setCulcCallback(gfArchive* archive);
};
static_assert(sizeof(grYakumonoPunchSlider) == 452, "Class is wrong size!");
