#include <gf/gf_archive.h>
#include <gf/gf_error_manager.h>
#include <gm/gm_global.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <st_battles/gr_battles.h>
#include <types.h>

#include <st_battles/st_battles.h>

stClassInfoImpl<Stages::BattleFieldS, stBattleFieldS> stBattleFieldS::bss_loc_14;

stBattleFieldS::stBattleFieldS() : stMelee("stBattleFieldS", Stages::Battle) { }

stBattleFieldS* stBattleFieldS::create() {
    return new (Heaps::StageInstance) stBattleFieldS;
}

stBattleFieldS::~stBattleFieldS() {
    releaseArchive();
}

bool stBattleFieldS::loading() {
    return true;
}

void stBattleFieldS::createObj() {
    testStageParamInit(m_fileData, 10);
    testStageDataInit(m_fileData, 20, 1);
    grBattleFieldS* ground = grBattleFieldS::create(1, "", "grBattleFieldMainBg");
    if (ground) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        createCollision(m_fileData, 2, nullptr);
        initCameraParam();
        void* posData = m_fileData->getData(Data_Type_Model, 100, 0xFFFE);
        if (posData) {
            nw4r::g3d::ResFile posFile(posData);
            createStagePositions(&posFile);
        } else {
            createStagePositions();
        }
        createWind2ndOnly();
        loadStageAttrParam(m_fileData, 30);
        registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
        initPosPokeTrainer(1, 0);
        createObjPokeTrainer(m_fileData, 101, "PokeTrainer00", m_pokeTrainerPos, nullptr);
    }
}

void stBattleFieldS::update(float deltaFrame) { }

void stBattleFieldS::notifyDebugError() {
    gmGlobalModeMelee* modeMelee = g_GameGlobal->m_modeMelee;
    if (modeMelee) {
        u32 errorCode = 0;
        u32 reasonCode = 0;
        switch (modeMelee->m_meleeInitData.m_0x81) {
            case 201:
                errorCode = 1;
                break;
            case 202:
                errorCode = 2;
                break;
            case 203:
                errorCode = 3;
                break;
            case 204:
                errorCode = 4;
                break;
            case 205:
                errorCode = 5;
                break;
            case 206:
                errorCode = 6;
                break;
            case 207:
                errorCode = 7;
                break;
            case 208:
                errorCode = 8;
                break;
            case 209:
                errorCode = 9;
                reasonCode = 29000;
                break;
            case 210:
                errorCode = 10;
                reasonCode = 29001;
                break;
            case 211:
                errorCode = 11;
                reasonCode = 12345;
                break;
        }
        if (errorCode != 0) {
            gfErrorManager::getInstance()->notifyError(errorCode, reasonCode);
        }
    }
}
