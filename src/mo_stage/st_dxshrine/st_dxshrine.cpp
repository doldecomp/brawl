#include <cm/cm_camera_controller.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_id.h>
#include <snd/snd_system.h>
#include <st_dxshrine/gr_dxshrine.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

#include <st_dxshrine/st_dxshrine.h>

stClassInfoImpl<Stages::DxShrine, stDxShrine> stDxShrine::bss_loc_14;

stDxShrine::stDxShrine() : stMelee("stDxShrine", Stages::DxShrine) {
	initStageData();
}

stDxShrine* stDxShrine::create() {
    return new (Heaps::StageInstance) stDxShrine;
}

stDxShrine::~stDxShrine() {
    releaseArchive();
}

bool stDxShrine::loading() {
    return true;
}

void stDxShrine::createObj() {
	grDxShrine *ground = grDxShrine::create(0,"", "grDxShrineMainBg");
	if (ground) {
		addGround(ground);
		ground->startup(this->m_fileData,0,0);
		ground->setStageData(&this->m_shrineStageData);
	}
    createCollision(m_fileData, 2, 0);
    testStageParamInit(m_fileData, 0xA);
    initCameraParam();
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x64, 0xFFFE));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        createStagePositions();
    }
    createWind2ndOnly();
    loadStageAttrParam(m_fileData, 0x1E);
    registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 0x65, "PokeTrainer00", m_pokeTrainerPos, 0);
}

void stDxShrine::update(float deltaFrame) {
}

void stDxShrine::initStageData() {
	memset(&this->m_shrineStageData,0,1);
}
