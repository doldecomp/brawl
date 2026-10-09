#include <cstdio>
#include <gf/gf_3d_scene.h>
#include <gf/gf_archive.h>
#include <gm/gm_global.h>
#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <memory.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/math/math_trigonometric.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <st_battle/gr_battlefield.h>
#include <types.h>

#include <st_battle/st_battlefield.h>

stClassInfoImpl<Stages::BattleField, stBattleField> stBattleField::bss_loc_14;

stBattleField::stBattleField() : stMelee("stBattleField", Stages::Battle) { }

stBattleField* stBattleField::create() {
    return new (Heaps::StageInstance) stBattleField;
}

stBattleField::~stBattleField() {
    releaseArchive();
}

bool stBattleField::loading() {
    return true;
}

// Builds the stage out of its pieces, then reads the 100-Man Brawl spawn points off a throwaway grMadein: the
// "KumiteNode" model only exists to carry the hyakunin_*_start nodes.
void stBattleField::createObj() {
    testStageParamInit(m_fileData, 10);
    testStageDataInit(m_fileData, 20, 1);
    initCameraParam();
    addGround(grBattleField::create(2, "", "grBattleFieldSky"));
    addGround(grBattleField::create(3, "", "grBattleFieldSun"));
    addGround(grBattleField::create(4, "", "grBattleFieldMoon"));
    addGround(grBattleField::create(5, "", "grBattleFieldStar"));
    addGround(grBattleField::create(6, "", "grBattleFieldCloud"));
    addGround(grBattleField::create(1, "", "grBattleFieldMainBg"));
    addGround(grBattleField::create(7, "", "grBattleFieldCrystal"));
    addGround(grBattleField::create(9, "", "grBattleFieldClock"));
    addGround(grBattleField::create(10, "zStgBattleFieldStage", "grBattleFieldStage"));
    addGround(grBattleField::create(11, "zStgBattleFieldAshiba01", "grBattleFieldAshiba01"));
    addGround(grBattleField::create(12, "zStgBattleFieldAshiba02", "grBattleFieldAshiba02"));
    addGround(grBattleField::create(13, "zStgBattleFieldAshiba03", "grBattleFieldAshiba03"));
    addGround(grBattleField::create(8, "", "grBattleFieldFlare"));
    u32 groundNum = getGroundNum();
    for (u32 i = 0; i != groundNum; i++) {
        Ground* ground = getGround(i);
        if (ground != NULL) {
            ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
            ground->setStageData(m_stageData);
            ground->setDontMoveGround();
        }
    }
    createCollision(m_fileData, 2, NULL);
    grMadein* kumiteNode = grMadein::create(200, "", "KumiteNode", Heaps::StageInstance);
    if (kumiteNode != NULL) {
        kumiteNode->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        kumiteNode->initializeEntity();
        kumiteNode->startEntity();
        kumiteNode->updateG3dProcCalcWorld();
        char nodeName[0x40];
        for (int i = 0; i < 5; i++) {
            sprintf(nodeName, "hyakunin_enemy_start%d", i);
            kumiteNode->getNodePosition(&m_enemyStartPos[i], 0, nodeName);
        }
        for (int i = 0; i < 4; i++) {
            sprintf(nodeName, "hyakunin_boss_start%d", i);
            kumiteNode->getNodePosition(&m_bossStartPos[i], 0, nodeName);
        }
        for (int i = 0; i < 2; i++) {
            sprintf(nodeName, "hyakunin_fighter_start%d", i);
            kumiteNode->getNodePosition(&m_fighterStartPos[i], 0, nodeName);
        }
        kumiteNode->endEntity();
        delete kumiteNode;
    }
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 100, 0xFFFE));
    if (posData.ptr()) {
        createStagePositions(&posData);
    } else {
        createStagePositions();
    }
    createWind2ndOnly();
    registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    loadStageAttrParam(m_fileData, 30);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 101, "PokeTrainer00", m_pokeTrainerPos, NULL);
}

// The scene animation is a 6000-frame day/night cycle; the stage's shadow (light) direction follows it.
void stBattleField::update(float deltaFrame) {
    stParam* param = m_stageParam;
    if (param != NULL) {
        float frame = 0.0f;
        if (g_gfSceneRoot->m_anmScnRes != NULL) {
            frame = g_gfSceneRoot->m_anmScnRes->GetFrame();
        }
        if (frame >= 0.0f && frame <= 6000.0f) {
            float t = frame / 6000.0f;
            float lo = 0.0f;
            float hi = 1.0f;
            t = nw4r::math::FSelect(t - lo, t, lo);
            t = nw4r::math::FSelect(t - hi, hi, t);
            nw4r::math::SinFIdx(NW4R_MATH_IDX_TO_FIDX(nw4r::math::U16ToF32((u16)(int)(t * 32768.0f))));
            float c = frame / 6000.0f;
            c = nw4r::math::FSelect(c - lo, c, lo);
            c = nw4r::math::FSelect(c - hi, hi, c);
            param->m_shadowPitch = 40.0f;
            param->m_shadowYaw = 240.0f + -120.0f * c;
            param->_26[0] = 0; // HYPOTHESIS: third float of the shadow direction
            // HYPOTHESIS: tells the scene to pick the changed shadow parameters up
            *(u8*)((u8*)this + 0xE8) = 1;
        } else {
            param->m_shadowPitch = 90.0f;
            param->m_shadowYaw = 0.0f;
        }
    }
}

// In 100-Man Brawl the fighters and enemies start from the nodes of the "KumiteNode" model.
void stBattleField::getFighterStartPos(Vec3f* startPos, int fighterIndex) {
    u32 mode = g_GameGlobal->m_modeMelee->m_meleeInitData.m_gameMode;
    if (mode == Game_Mode_Kumite || mode == Game_Mode_Net_Kumite) {
        Vec3f* src;
        if ((u32)fighterIndex >= 20) {
            src = &m_enemyStartPos[(u32)(fighterIndex - 20) % 5];
        } else if ((u32)fighterIndex >= 10) {
            src = &m_bossStartPos[(u32)(fighterIndex - 10) % 5]; // HYPOTHESIS: the original wraps by 5 here although there are 4 boss nodes
        } else {
            src = &m_fighterStartPos[fighterIndex & 1];
        }
        startPos->m_x = src->m_x;
        startPos->m_y = src->m_y;
        startPos->m_z = src->m_z;
    } else {
        stMelee::getFighterStartPos(startPos, fighterIndex);
    }
}
