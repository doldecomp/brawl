#include <cm/cm_camera_controller.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_id.h>
#include <snd/snd_system.h>
#include <st_final/gr_final.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

#include <st_final/st_final.h>

stClassInfoImpl<Stages::Final, stFinal> stFinal::bss_loc_14;

stFinal::stFinal() : stMelee("stFinal", Stages::Final) { }

stFinal* stFinal::create() {
    return new (Heaps::StageInstance) stFinal;
}

stFinal::~stFinal() {
    releaseArchive();
}

bool stFinal::loading() {
    return true;
}

void stFinal::createObj()
{
    testStageParamInit(m_fileData, 0xA);
    testStageDataInit(m_fileData, 0x14, 1);
    grFinal* ground = grFinal::create(1, "", "grFinalMainBg");
    if (ground != nullptr) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setType(0);
        ground->setDontMoveGround();
    }
    ground = grFinal::create(2, "", "grFinalStage");
    if (ground != nullptr) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setType(1);
        ground->setDontMoveGround();
    }
    createCollision(m_fileData, 2, NULL);
    initCameraParam();
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x64, 0xfffe));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        // if no stgPos model in pac, use defaults
        createStagePositions();
    }
    createWind2ndOnly();
    loadStageAttrParam(m_fileData, 0x1E);
    nw4r::g3d::ResFileData* scnData = static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xfffe));
    registScnAnim(scnData, 0);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 0x65, "PokeTrainer00", m_pokeTrainerPos, 0x0);
}

void grFinal::setType(int type) {
    m_type = type;
}

void stFinal::update(float deltaFrame) { }
