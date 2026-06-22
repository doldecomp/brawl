#include <ec/ec_mgr.h>
#include <gf/gf_3d_scene.h>
#include <gf/gf_archive.h>
#include <gf/gf_callback.h>
#include <gr/collision/gr_collision.h>
#include <gr/collision/gr_collision_data.h>
#include <gr/gr_gimmick_ladder.h>
#include <sr/sr_common.h>
#include <st/st_common_gimmick.h>
#include <st/st_trigger_observe.h>
#include <types.h>

stCommonGimmick::stCommonGimmick(const char* name, srStageKind stageKind)
        : Stage(name, stageKind), unk1AC(false) {
    m_fileData = nullptr;
    m_secondaryFileData = nullptr;
    unk1A8 = nullptr;
    m_commonFileData = nullptr;
    m_isPaused = false;
}

stCommonGimmick::~stCommonGimmick() { }

void stCommonGimmick::setupItemSheet() {
    if (m_fileData) {
        int nodeSize;
        void* data = m_fileData->getData(Data_Type_Misc, 10000, &nodeSize, 0xFFFE);
        if (data)
            m_itemSheetArchive.setFileImage(data, nodeSize, Heaps::StageInstance);
    }
}

grGimmickLadder* stCommonGimmick::createGimmickLadder(grGimmickLadderData* ladderData, gfArchive* archive) {
    grGimmickLadder* ladder =
        grGimmickLadder::create(ladderData->m_mdlIndex, "grGimmickLadder");
    if (ladder) {
        addGround(ladder);
        ladder->setGimmickData(ladderData);
        ladder->startup(archive, 0, gfSceneRoot::Layer_Ground);
    }
    return ladder;
}

bool stCommonGimmick::createGimmickWind2(grGimmickWindData* windAreaData) {
    g_stTriggerMng->createTrigger(Gimmick::Area_Wind, -1)
                  ->setWindTrigger(windAreaData);
    return false;
}

bool stCommonGimmick::createGimmickBeltConveyor2(grGimmickBeltConveyorData* beltConveyorAreaData) {
    g_stTriggerMng->createTrigger(Gimmick::Area_BeltConveyor, -1)
                  ->setBeltConveyorTrigger(beltConveyorAreaData);
    return false;
}

bool stCommonGimmick::createGimmickWaterArea(grGimmickWaterData* waterAreaData) {
    g_stTriggerMng->createTrigger(Gimmick::Area_Water, -1)
                  ->setWaterTrigger(waterAreaData);
    return false;
}

bool stCommonGimmick::createGimmickHitPointEffectArea(grGimmickHitPointEffectData* hitPointEffectData) {
    g_stTriggerMng->createTrigger(Gimmick::Area_HitPoint_Effect, -1)
                  ->setHitPointEffectTrigger(hitPointEffectData);
    return false;
}

grGimmickCatapult* stCommonGimmick::createGimmickCatapult(grGimmickCatapultData* catapultData, gfArchive* archive) {
    grGimmickCatapult* catapult =
        grGimmickCatapult::create(catapultData->m_mdlIndex, "FighterPos_01");
    if (catapult) {
        addGround(catapult);
        catapult->setGimmickData(catapultData);
        catapult->startup(archive, 0, gfSceneRoot::Layer_Ground);
    }
    return catapult;
}

bool stCommonGimmick::createGimmickFrameTrigger(grGimmickFrameTriggerData* frameTriggerData) {
    stTrigger* trigger = g_stTriggerMng->createTrigger(Gimmick::Area_None, &frameTriggerData->unkC);
    stActTriggerFrameExcelCB* cb = new (Heaps::StageInstance) stActTriggerFrameExcelCB(frameTriggerData);
    trigger->setValidCallback(cb);
    return false;
}

void stCommonGimmick::createGimmickCollision(u32 collIndex, Ground* ground, gfArchive* archive) {
    if (collIndex != 0xFF) {
        grCollData* collData = new (Heaps::StageInstance) grCollData;
        if (collData) {
            testCollDataInit(archive, collData, collIndex);
            setCollision(grCollision::create(this, collData, ground, 1));
        }
        delete collData;
    }
}

void stCommonGimmick::releaseArchive() {
    if (!unk1AC && m_fileData)
        delete m_fileData;
}

void stCommonGimmick::releaseArchiveCommon() {
    if (!unk1AC && m_commonFileData)
        delete m_commonFileData;
}

void stCommonGimmick::processBegin() {
    // FIXME: magic numbers
    g_ecMgr->pushsetCurrentGroup(0x2000000);
    m_shadow->clearShadowObject();
    if (!m_isPaused)
        unk194++;
    if (!unk1AC)
        Stage::processBegin();
    else
        unk40 = 4;
    g_ecMgr->popCurrentGroup();
}

void stCommonGimmick::setPause(bool pause) {
    u32 i = 0;
    u32 e = getGroundNum();
    m_isPaused = pause;
    for ( ; i != e; i++) {
        Ground* gr = getGround(i);
        if (gr)
            gr->m_isPauseAnim = m_isPaused;
    }
}
