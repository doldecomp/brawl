#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick_catapult.h>
#include <gr/gr_gimmick_ladder.h>
#include <gr/gr_gimmick_spring.h>
#include <st/stage.h>
#include <st/st_trigger_observe.h>
#include <types.h>

class stCommonGimmick : public Stage {
public:
    gfArchive* m_fileData; // +0x1A0
    gfArchive* m_secondaryFileData;
    gfArchive* unk1A8;
    bool unk1AC;
    bool m_isPaused;
    gfArchive* m_commonFileData; // +0x1B0

    stCommonGimmick(const char* name, srStageKind stageKind);
    virtual void processBegin();
    virtual ~stCommonGimmick();

    void setupItemSheet();
    void releaseArchive();
    void releaseArchiveCommon();
    void setPause(bool pause);
    bool createGimmickFrameTrigger(grGimmickFrameTriggerData* frameTriggerData);
    void createGimmickCollision(u32 collIndex, Ground* ground, gfArchive* archive);
    bool createGimmickBeltConveyor2(grGimmickBeltConveyorData* beltConveyorAreaData);
    bool createGimmickWaterArea(grGimmickWaterData* waterAreaData);
    bool createGimmickWind2(grGimmickWindData* windAreaData);
    bool createGimmickHitPointEffectArea(grGimmickHitPointEffectData* hitPointEffectData);
    grGimmickLadder* createGimmickLadder(grGimmickLadderData* ladderData, gfArchive* archive);
    grGimmickCatapult* createGimmickCatapult(grGimmickCatapultData* catapultData, gfArchive* archive);
};
